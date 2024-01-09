#include <query.h>

static ecs_query_cache_kind_t cache_kind = EcsQueryCacheDefault;

void MemberTarget_setup(void) {
    const char *cache_param = test_param("cache_kind");
    if (cache_param) {
        if (!strcmp(cache_param, "default")) {
            // already set to default
        } else if (!strcmp(cache_param, "auto")) {
            cache_kind = EcsQueryCacheAuto;
        } else {
            printf("unexpected value for cache_param '%s'\n", cache_param);
        }
    }
}

typedef struct {
    ecs_entity_t value;
} Movement;

static ecs_entity_t ecs_id(Movement) = 0;
static ecs_entity_t Running = 0;
static ecs_entity_t Walking = 0;
static ecs_entity_t Sitting = 0;

static void register_types(
    ecs_world_t *world)
{
    ecs_id(Movement) = ecs_struct(world, {
        .entity = ecs_entity(world, { .name = "Movement" }),
        .members = {
            { "value", ecs_id(ecs_entity_t) }
        }
    });

    Running = ecs_entity(world, { .name = "Running" });
    Walking = ecs_entity(world, { .name = "Walking" });
    Sitting = ecs_entity(world, { .name = "Sitting" });
}

void MemberTarget_this_member_eq(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    printf("%s\n", ecs_query_plan(q));

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(2, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_wildcard(void) {
    // Implement testcase
}

void MemberTarget_this_member_var(void) {
    // Implement testcase
}

void MemberTarget_this_written_member_eq(void) {
    // Implement testcase
}

void MemberTarget_this_written_member_wildcard(void) {
    // Implement testcase
}

void MemberTarget_this_written_member_var(void) {
    // Implement testcase
}
