 /**
 * @file query/cache.h
 * @brief Internal types and functions for rules addon.
 */

/** Table match data.
 * Each table matched by the query is represented by a ecs_query_cache_table_match_t
 * instance, which are linked together in a list. A table may match a query
 * multiple times (due to wildcard queries) with different columns being matched
 * by the query. */
struct ecs_query_cache_table_match_t {
    ecs_query_cache_table_match_t *next, *prev;
    ecs_table_t *table;              /* The current table. */
    int32_t offset;                  /* Starting point in table  */
    int32_t count;                   /* Number of entities to iterate in table */
    int32_t *columns;                /* Mapping from query fields to table columns */
    int32_t *storage_columns;        /* Mapping from query fields to storage columns */
    ecs_id_t *ids;                   /* Resolved (component) ids for current table */
    ecs_entity_t *sources;           /* Subjects (sources) of ids */
    ecs_vec_t refs;                  /* Cached components for non-this terms */
    uint64_t group_id;               /* Value used to organize tables in groups */
    int32_t *monitor;                /* Used to monitor table for changes */
    ecs_entity_filter_t *entity_filter; /* Entity specific filters */

    /* Next match in cache for same table (includes empty tables) */
    ecs_query_cache_table_match_t *next_match;
};

/** Table record type for query table cache. A query only has one per table. */
typedef struct ecs_query_cache_table_t {
    ecs_table_cache_hdr_t hdr;       /* Header for ecs_table_cache_t */
    ecs_query_cache_table_match_t *first;  /* List with matches for table */
    ecs_query_cache_table_match_t *last;   /* Last discovered match for table */
    uint64_t table_id;
    int32_t rematch_count;           /* Track whether table was rematched */
} ecs_query_cache_table_t;

/** Points to the beginning & ending of a query group */
typedef struct ecs_query_cache_table_list_t {
    ecs_query_cache_table_match_t *first;
    ecs_query_cache_table_match_t *last;
    ecs_query_group_info_t info;
} ecs_query_cache_table_list_t;

/* Query event type for notifying queries of world events */
typedef enum ecs_query_cache_eventkind_t {
    EcsQueryTableMatch,
    EcsQueryTableRematch,
    EcsQueryTableUnmatch,
} ecs_query_cache_eventkind_t;

typedef struct ecs_query_cache_event_t {
    ecs_query_cache_eventkind_t kind;
    ecs_table_t *table;
} ecs_query_cache_event_t;

/* Query level block allocators have sizes that depend on query field count */
typedef struct ecs_query_cache_allocators_t {
    ecs_block_allocator_t columns;
    ecs_block_allocator_t ids;
    ecs_block_allocator_t sources;
    ecs_block_allocator_t monitors;
} ecs_query_cache_allocators_t;

/** Query that is automatically matched against tables */
typedef struct ecs_query_cache_t {
    /* Query filter */
    ecs_query_t *query;

    /* Tables matched with query */
    ecs_table_cache_t cache;

    /* Linked list with all matched non-empty tables, in iteration order */
    ecs_query_cache_table_list_t list;

    /* Contains head/tail to nodes of query groups (if group_by is used) */
    ecs_map_t groups;

    /* Table sorting */
    ecs_entity_t order_by_component;
    ecs_order_by_action_t order_by;
    ecs_sort_table_action_t sort_table;
    ecs_vec_t table_slices;
    int32_t order_by_term;

    /* Table grouping */
    ecs_entity_t group_by_id;
    ecs_group_by_action_t group_by;
    ecs_group_create_action_t on_group_create;
    ecs_group_delete_action_t on_group_delete;
    void *group_by_ctx;
    ecs_ctx_free_t group_by_ctx_free;

    /* Monitor generation */
    int32_t monitor_generation;

    int32_t cascade_by;              /* Identify cascade term */
    int32_t match_count;             /* How often have tables been (un)matched */
    int32_t prev_match_count;        /* Track if sorting is needed */
    int32_t rematch_count;           /* Track which tables were added during rematch */

    /* Mixins */
    ecs_world_t *world;
    ecs_entity_t entity;

    /* Query-level allocators */
    ecs_query_cache_allocators_t allocators;
} ecs_query_cache_t;

