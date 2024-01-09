 /**
 * @file addons/rules/api.c
 * @brief User facing API for rules.
 */

#include "../private_api.h"
#include <ctype.h>

static ecs_mixins_t ecs_query_impl_t_mixins = {
    .type_name = "ecs_query_impl_t",
    .elems = {
        [EcsMixinWorld] = offsetof(ecs_query_impl_t, pub.world),
        [EcsMixinEntity] = offsetof(ecs_query_impl_t, pub.entity),
        [EcsMixinIterable] = offsetof(ecs_query_impl_t, iterable),
        [EcsMixinDtor] = offsetof(ecs_query_impl_t, dtor)
    }
};

int32_t ecs_query_var_count(
    const ecs_query_t *q)
{
    ecs_poly_assert(q, ecs_query_impl_t);
    return flecs_query_impl(q)->var_pub_count;
}

int32_t ecs_query_find_var(
    const ecs_query_t *q,
    const char *name)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    ecs_query_impl_t *impl = flecs_query_impl(q);
    ecs_var_id_t var_id = flecs_query_find_var_id(impl, name, EcsVarEntity);
    if (var_id == EcsVarNone) {
        if (q->flags & EcsQueryMatchThis) {
            if (!ecs_os_strcmp(name, "This")) {
                name = "this";
            }
            if (!ecs_os_strcmp(name, EcsThisName)) {
                var_id = 0;
            }
        }
        if (var_id == EcsVarNone) {
            return -1;
        }
    }
    return (int32_t)var_id;
}

const char* ecs_query_var_name(
    const ecs_query_t *q,
    int32_t var_id)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    if (var_id) {
        return flecs_query_impl(q)->vars[var_id].name;
    } else {
        return EcsThisName;
    }
}

bool ecs_query_var_is_entity(
    const ecs_query_t *q,
    int32_t var_id)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    return flecs_query_impl(q)->vars[var_id].kind == EcsVarEntity;
}

/* Implementation for iterable mixin */
static
void flecs_query_iter_mixin_init(
    const ecs_world_t *world,
    const ecs_poly_t *poly,
    ecs_iter_t *iter,
    ecs_term_t *filter)
{
    ecs_poly_assert(poly, ecs_query_impl_t);

    if (filter) {
        iter[1] = ecs_query_iter(world, ECS_CONST_CAST(ecs_query_t*, poly));
        // iter[0] = ecs_term_chain_iter(&iter[1], filter); TODO
    } else {
        iter[0] = ecs_query_iter(world, ECS_CONST_CAST(ecs_query_t*, poly));
    }
}

static
int flecs_query_set_caching_policy(
    ecs_query_impl_t *impl,
    const ecs_query_desc_t *desc)
{
    ecs_query_cache_kind_t kind = desc->cache_kind;

    /* If caching policy is default, try to pick a policy that does the right
     * thing in most cases. */
    if (kind == EcsQueryCacheDefault) {
        if (desc->entity || desc->group_by_id || desc->group_by || 
            desc->order_by_component || desc->order_by)
        {
            /* If the query is created with an entity handle (typically 
             * indicating that the query is named or belongs to a system) the
             * chance is very high that the query will be reused, so enable
             * caching. 
             * Additionally, if the query uses features that require a cache
             * such as group_by/order_by, also enable caching. */
            kind = EcsQueryCacheAuto;
        } else {
            /* Be conservative in other scenario's, as caching adds significant
             * overhead to the cost of query creation which doesn't offset the
             * benefit of faster iteration if it's only used once. */
            kind = EcsQueryCacheNone;
        }
    }

    /* Don't cache query, even if it has cacheable terms */
    if (kind == EcsQueryCacheNone) {
        impl->pub.cache_kind = EcsQueryCacheNone;
        if (desc->group_by_id || desc->order_by_component) {
            ecs_err("cannot create uncached query with group_by/order_by");
            return -1;
        }
        return 0;
    }

    /* Entire query must be cached */
    if (desc->cache_kind == EcsQueryCacheAll) {
        if (impl->pub.flags & EcsQueryIsCacheable) {
            impl->pub.cache_kind = EcsQueryCacheAll;
            return 0;
        } else {
            ecs_err("cannot enforce QueryCacheAll, "
                "query contains uncacheable terms");
            return -1;
        }
    }

    /* Only cache terms that are cacheable */
    if (kind == EcsQueryCacheAuto) {
        if (impl->pub.flags & EcsQueryIsCacheable) {
            /* If all terms of the query are cacheable, just set the policy to 
             * All which simplifies work for the compiler. */
            impl->pub.cache_kind = EcsQueryCacheAll;
        } else if (!(impl->pub.flags & EcsQueryHasCacheable)) {
            /* Same for when the query has no cacheable terms */
            impl->pub.cache_kind = EcsQueryCacheNone;
        } else {
            /* Part of the query is cacheable */
            impl->pub.cache_kind = EcsQueryCacheAuto;
        }
    }

    return 0;
}

static
int flecs_query_create_cache(
    ecs_query_impl_t *impl,
    ecs_query_desc_t *desc)
{
    ecs_query_t *q = &impl->pub;
    if (flecs_query_set_caching_policy(impl, desc)) {
        return -1;
    }

    if ((q->cache_kind != EcsQueryCacheNone) && !q->entity) {
        /* Cached queries need an entity handle for observer components */
        q->entity = ecs_new_id(q->world);
        desc->entity = q->entity;
    }

    if (q->cache_kind == EcsQueryCacheAll) {
        /* Create query cache for all terms */
        impl->cache = flecs_query_cache_init(impl, desc);
    } else if (q->cache_kind == EcsQueryCacheAuto) {
        /* Query is partially cached */
        ecs_query_desc_t cache_desc = *desc;
        ecs_os_memset_n(&cache_desc.terms, 0, ecs_term_t, FLECS_TERM_COUNT_MAX);
        cache_desc.expr = NULL;

        /* Maps field indices from cache to query */
        int8_t field_map[FLECS_TERM_COUNT_MAX];

        int32_t i, count = q->term_count, dst_count = 0, dst_field = 0;
        ecs_term_t *terms = q->terms;
        for (i = 0; i < count; i ++) {
            ecs_term_t *term = &terms[i];
            if (term->flags & EcsTermIsCacheable) {
                cache_desc.terms[dst_count] = *term;
                field_map[dst_field] = flecs_ito(int8_t, term->field_index);
                dst_count ++;
                if (i) {
                    dst_field += term->field_index != term[-1].field_index;
                } else {
                    dst_field ++;
                }
            }
        }

        if (dst_count) {
            impl->cache = flecs_query_cache_init(impl, &cache_desc);
            impl->field_map = ecs_os_memdup_n(field_map, int8_t, dst_count);
        }
    }

    return 0;
}

static
void flecs_query_fini(
    ecs_query_impl_t *impl)
{
    if (impl->ctx_free) {
        impl->ctx_free(impl->pub.ctx);
    }

    if (impl->binding_ctx_free) {
        impl->binding_ctx_free(impl->pub.binding_ctx);
    }

    if (impl->vars != &impl->vars_cache.var) {
        ecs_os_free(impl->vars);
    }

    ecs_os_free(impl->ops);
    ecs_os_free(impl->src_vars);
    ecs_os_free(impl->monitor);
    flecs_name_index_fini(&impl->tvar_index);
    flecs_name_index_fini(&impl->evar_index);

    ecs_query_t *q = &impl->pub;
    int i, count = q->term_count;
    for (i = 0; i < count; i ++) {
        ecs_term_t *term = &q->terms[i];
        if (term->idr) {
            if (!(q->world->flags & EcsWorldQuit)) {
                if (ecs_os_has_threading()) {
                    ecs_os_adec(&term->idr->keep_alive);
                } else {
                    term->idr->keep_alive --;
                }
            }
        }
    }

    if (impl->tokens) {
        flecs_free(&q->stage->allocator, impl->tokens_len, impl->tokens);
    }

    if (impl->cache) {
        flecs_query_cache_fini(impl);
    }

    ecs_poly_free(impl, ecs_query_impl_t);
}

static
char* flecs_query_append_token(
    char *dst,
    const char *src)
{
    int32_t len = ecs_os_strlen(src);
    ecs_os_strncpy(dst, src, len + 1);
    return dst + len + 1;
}

static
void flecs_query_populate_tokens(
    ecs_query_impl_t *impl)
{
    ecs_query_t *q = &impl->pub;
    int32_t i, term_count = q->term_count;
    
    /* Step 1: determine size of token buffer */
    int32_t len = 0;
    for (i = 0; i < term_count; i ++) {
        ecs_term_t *term = &q->terms[i];
        
        if (term->first.name) {
            len += ecs_os_strlen(term->first.name);
        }
        if (term->second.name) {
            len += ecs_os_strlen(term->second.name);
        }
        if (term->src.name) {
            len += ecs_os_strlen(term->src.name);
        }
    }

    /* Step 2: reassign term tokens to buffer */
    if (len) {
        impl->tokens = flecs_alloc(&q->stage->allocator, len);
        impl->tokens_len = flecs_ito(int16_t, len);
        char *token = impl->tokens, *next;

        for (i = 0; i < term_count; i ++) {
            ecs_term_t *term = &q->terms[i];
            if (term->first.name) {
                next = flecs_query_append_token(token, term->first.name);
                term->first.name = token;
                token = next;
            }
            if (term->second.name) {
                next = flecs_query_append_token(token, term->second.name);
                term->second.name = token;
                token = next;
            }
            if (term->src.name) {
                next = flecs_query_append_token(token, term->src.name);
                term->src.name = token;
                token = next;
            }
        }
    }
}

void ecs_query_fini(
    ecs_query_t *q)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    if (q->entity) {
        /* If filter is associated with entity, use poly dtor path */
        ecs_delete(q->world, q->entity);
    } else {
        flecs_query_fini(flecs_query_impl(q));
    }
}

ecs_query_t* ecs_query_init(
    ecs_world_t *world, 
    const ecs_query_desc_t *const_desc)
{
    ecs_query_impl_t *result = ecs_poly_new(ecs_query_impl_t);
    ecs_stage_t *stage = flecs_stage_from_world(&world);

    /* Initialize the query */
    ecs_query_desc_t desc = *const_desc;
    ecs_entity_t entity = const_desc->entity;
    result->pub.entity = entity;
    result->pub.world = world;
    if (flecs_query_finalize_query(world, &result->pub, &desc)) {
        goto error;
    }

    /* Initialize static context & mixins */
    result->pub.stage = stage;
    result->pub.ctx = const_desc->ctx;
    result->pub.binding_ctx = const_desc->binding_ctx;
    result->ctx_free = const_desc->ctx_free;
    result->binding_ctx_free = const_desc->binding_ctx_free;
    result->dtor = (ecs_poly_dtor_t)flecs_query_fini;
    result->iterable.init = flecs_query_iter_mixin_init;
    result->cache = NULL;

    /* Initialize query cache if necessary */
    if (flecs_query_create_cache(result, &desc)) {
        goto error;
    }

    /* Compile filter to operations */
    if (flecs_query_compile(world, stage, result)) {
        goto error;
    }

    /* Store remaining string tokens in terms (after entity lookups) in single
     * token buffer which simplifies memory management & reduces allocations. */
    flecs_query_populate_tokens(result);

    /* Entity could've been set by finalize query if query is cached */
    entity = result->pub.entity;
    if (entity) {
        EcsPoly *poly = ecs_poly_bind(world, entity, ecs_query_impl_t);
        poly->poly = result;
        ecs_poly_modified(world, entity, ecs_query_impl_t);
    }

    return &result->pub;
error:
    ecs_query_fini(&result->pub);
    return NULL;
}

bool ecs_query_has(
    ecs_query_t *q,
    ecs_entity_t entity,
    ecs_iter_t *it)
{
    ecs_poly_assert(q, ecs_query_impl_t);
    ecs_check(q->flags & EcsQueryMatchThis, ECS_INVALID_PARAMETER, NULL);

    *it = ecs_query_iter(q->world, q);
    ecs_iter_set_var(it, 0, entity);
    return ecs_query_next(it);
error:
    return false;
}

/** Returns true if rule matches with table. */
bool ecs_query_has_table(
    ecs_query_t *q,
    ecs_table_t *table,
    ecs_iter_t *it)
{
    ecs_poly_assert(q, ecs_query_impl_t);
    ecs_check(q->flags & EcsQueryMatchThis, ECS_INVALID_PARAMETER, NULL);

    *it = ecs_query_iter(q->world, q);
    ecs_iter_set_var_as_table(it, 0, table);
    return ecs_query_next(it);
error:
    return false;
}

ecs_query_count_t ecs_query_count(
    const ecs_query_t *q)
{
    ecs_poly_assert(q, ecs_query_impl_t);
    ecs_query_count_t result = {0};

    if (!(q->flags & EcsQueryMatchThis)) {
        return result;
    }

    ecs_run_aperiodic(q->world, EcsAperiodicEmptyTables);

    ecs_query_impl_t *impl = flecs_query_impl(q);
    if (impl->cache && q->flags & EcsQueryIsCacheable) {
        result.results = flecs_query_cache_table_count(impl->cache);
        result.entities = flecs_query_cache_entity_count(impl->cache);
        result.tables = flecs_query_cache_table_count(impl->cache);
        result.empty_tables = flecs_query_cache_empty_table_count(impl->cache);
    } else {
        ecs_iter_t it = flecs_query_iter(q->world, q);
        it.flags |= EcsIterIsInstanced;
        it.flags |= EcsIterNoData;

        while (ecs_query_next_instanced(&it)) {
            result.results ++;
            result.entities += it.count;
        }
    }

    return result;
}

bool ecs_query_is_true(
    const ecs_query_t *q)
{
    ecs_poly_assert(q, ecs_query_impl_t);

    ecs_run_aperiodic(q->world, EcsAperiodicEmptyTables);

    ecs_query_impl_t *impl = flecs_query_impl(q);
    if (impl->cache && q->flags & EcsQueryIsCacheable) {
        return flecs_query_cache_table_count(impl->cache) != 0;
    } else {
        ecs_iter_t it = flecs_query_iter(q->world, q);
        return ecs_iter_is_true(&it);
    }
}
