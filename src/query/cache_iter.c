#include "../private_api.h"

static
ecs_query_cache_table_match_t* flecs_query_cache_next(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    const ecs_query_t *q = &impl->pub;
    ecs_query_cache_t *cache = impl->cache;
    ecs_iter_t *it = ctx->it;

    if (first) {
        op_ctx->node = cache->list.first;
        op_ctx->last = cache->list.last;

        if (cache->order_by && cache->list.info.table_count) {
            op_ctx->node = ecs_vec_first(&cache->table_slices);
        }
    }

    ecs_query_cache_table_match_t *node = op_ctx->node;
    ecs_query_cache_table_match_t *prev = op_ctx->prev;

    if (prev) {
        if (q->flags & EcsQueryHasMonitor) {
            flecs_query_cache_sync_match_monitor(cache, prev);
        }
        if (q->flags & EcsQueryHasOutTerms) {
            if (it->count) {
                flecs_query_cache_mark_columns_dirty(cache, prev);
            }
        }
    }

    if (prev != op_ctx->last) {
        ctx->vars[0].range.table = node->table;
        it->group_id = node->group_id;
        it->instance_count = 0;
        it->references = ecs_vec_first(&node->refs);
        op_ctx->node = node->next;
        op_ctx->prev = node;
        return node;
    }

    return NULL;
}

static
void flecs_query_populate_ptrs(
    ecs_iter_t *it,
    ecs_table_t *table,
    int32_t offset,
    ecs_query_cache_table_match_t *node)
{
    int32_t i, field_count = it->field_count;
    ecs_data_t *data = &table->data;
    for (i = 0; i < field_count; i ++) {
        int32_t storage_column = node->storage_columns[i];
        ecs_size_t size = it->sizes[i];
        if (storage_column < 0 || !size) {
            /* Tag / no data */
            it->ptrs[i] = NULL;
            continue;
        }

        it->ptrs[i] = ecs_vec_get(&data->columns[storage_column].data,
            it->sizes[i], offset);
    }

    ECS_BIT_CLEAR(it->flags, EcsIterHasShared);
}

static
void flecs_query_populate_ptrs_w_field_map(
    ecs_iter_t *it,
    ecs_table_t *table,
    int32_t offset,
    ecs_query_cache_table_match_t *node,
    int8_t *field_map,
    int32_t field_count)
{
    int32_t i;
    ecs_data_t *data = &table->data;
    for (i = 0; i < field_count; i ++) {
        int32_t storage_column = node->storage_columns[i];
        int8_t field_index = field_map[i];
        ecs_size_t size = it->sizes[field_index];
        if (storage_column < 0 || !size) {
            /* Tag / no data */
            it->ptrs[field_index] = NULL;
            continue;
        }

        it->ptrs[field_index] = ecs_vec_get(&data->columns[storage_column].data,
            size, offset);
    }

    ECS_BIT_CLEAR(it->flags, EcsIterHasShared);
}

static
void flecs_query_populate_ptrs_w_shared(
    ecs_iter_t *it,
    ecs_table_t *table,
    int32_t offset,
    ecs_query_cache_table_match_t *node,
    int8_t *field_map,
    int32_t field_count)
{
    bool has_shared = false;
    int32_t i;

    for (i = 0; i < field_count; i ++) {
        int32_t column = node->columns[i];
        int8_t field_index = i;
        if (field_map) {
            field_index = field_map[i];
        }

        ecs_size_t size = it->sizes[field_index];
        if (!column || !size) {
            /* Tag / no data */
            it->ptrs[field_index] = NULL;
            continue;
        }

        ecs_entity_t src = it->sources[i];
        if (src != 0) {
            ecs_ref_t *ref = &it->references[-column - 1];
            if (ref->id) {
                it->ptrs[field_index] = (void*)ecs_ref_get_id(
                    it->real_world, ref, ref->id);
                has_shared = true;
            } else {
                it->ptrs[field_index] = NULL;
            }
        } else {
            int32_t storage_column = node->storage_columns[i];
            if (storage_column < 0) {
                it->ptrs[field_index] = NULL;
                continue;
            }
            ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
            it->ptrs[field_index] = ecs_vec_get(
                &table->data.columns[storage_column].data, size, offset);
        }
    }

    ECS_BIT_COND(it->flags, EcsIterHasShared, has_shared);
}

bool flecs_query_cache_search(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    ecs_query_cache_table_match_t *node = flecs_query_cache_next(
        impl, ctx, op_ctx, first);
    if (!node) {
        return false;
    }

    ecs_iter_t *it = ctx->it;
    ecs_query_cache_t *cache = impl->cache;
    int32_t i, field_count = cache->query->field_count;
    int8_t *field_map = impl->field_map;

    for (i = 0; i < field_count; i ++) {
        int8_t field_index = field_map[i];
        it->columns[field_index] = node->columns[i];
        it->ids[field_index] = node->ids[i];
        it->sources[field_index] = node->sources[i];
    }

    ctx->vars[0].range.count = 0;
    ctx->vars[0].range.offset = 0;
    return true;
}

bool flecs_query_is_cache_search(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    ecs_query_cache_table_match_t *node = flecs_query_cache_next(
        impl, ctx, op_ctx, first);
    if (!node) {
        return false;
    }

    ecs_iter_t *it = ctx->it;
    it->columns = node->columns;
    it->ids = node->ids;
    it->sources = node->sources;

    ctx->vars[0].range.count = 0;
    ctx->vars[0].range.offset = 0;
    return true;
}

/* Populate for query that is partially cached.
 * This requires a mapping from cached fields to query fields. */
static
void flecs_query_cache_data_populate(
    const ecs_query_impl_t *impl,
    ecs_iter_t *it,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_cache_table_match_t *node)
{
    ecs_table_t *table = node->table;
    ecs_var_t *var = &ctx->vars[0];
    int32_t count = var->range.count, offset = var->range.offset;

    if (!count) {
        count = ecs_table_count(table);
    }

    /* If NoData flag is set on iterator, don't populate fields */
    if (ECS_BIT_IS_SET(it->flags, EcsIterNoData) || !count) {
        ECS_BIT_CLEAR(it->flags, EcsIterHasShared);
        return;
    }

    ecs_query_t *cache_query = impl->cache->query;
    if (!it->references) {
        flecs_query_populate_ptrs_w_field_map(
            it, table, offset, node, impl->field_map, cache_query->field_count);
    } else {
        flecs_query_populate_ptrs_w_shared(
            it, table, offset, node, impl->field_map, cache_query->field_count);
    }
}

/* Populate for query that is entirely cached.
 * Cached fields the same as query fields. */
static
void flecs_query_is_cache_data_populate(
    ecs_iter_t *it,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_cache_table_match_t *node)
{
    ecs_table_t *table = node->table;
    ecs_var_t *var = &ctx->vars[0];
    int32_t count = var->range.count, offset = var->range.offset;

    if (!count) {
        count = ecs_table_count(table);
    }

    /* If NoData flag is set on iterator, don't populate fields */
    if (ECS_BIT_IS_SET(it->flags, EcsIterNoData) || !count) {
        ECS_BIT_CLEAR(it->flags, EcsIterHasShared);
        return;
    }

    if (!it->references) {
        flecs_query_populate_ptrs(it, table, offset, node);
    } else {
        flecs_query_populate_ptrs_w_shared(it, table, offset, node, NULL, 
            it->field_count);
    }
}

bool flecs_query_cache_data_search(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    if (!flecs_query_cache_search(impl, ctx, op_ctx, first)) {
        return false;
    }

    flecs_query_cache_data_populate(impl, ctx->it, ctx, op_ctx->prev);
    return true;
}

bool flecs_query_is_cache_data_search(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    if (!flecs_query_is_cache_search(impl, ctx, op_ctx, first)) {
        return false;
    }

    flecs_query_is_cache_data_populate(ctx->it, ctx, op_ctx->prev);
    return true;
}

bool flecs_query_is_cache_test(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    ecs_iter_t *it = ctx->it;
    if (first) {
        ecs_var_t *var = &ctx->vars[0];
        ecs_table_t *table = var->range.table;
        ecs_assert(table != NULL, ECS_INVALID_OPERATION, NULL);

        ecs_query_cache_table_t *qt = flecs_query_cache_get_table(
            impl->cache, table);
        if (!qt) {
            return false;
        }

        op_ctx->prev = NULL;
        op_ctx->node = qt->first;
        op_ctx->last = qt->last;
    }

    ecs_query_cache_table_match_t *node = flecs_query_cache_next(
        impl, ctx, op_ctx, false);
    if (!node) {
        return false;
    }

    it->columns = node->columns;
    it->ids = node->ids;
    it->sources = node->sources;

    return true;
}

bool flecs_query_is_cache_data_test(
    const ecs_query_impl_t *impl,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_impl_cache_ctx_t *op_ctx,
    bool first)
{
    if (!flecs_query_is_cache_test(impl, ctx, op_ctx, first)) {
        return false;
    }

    flecs_query_is_cache_data_populate(ctx->it, ctx, op_ctx->prev);
    return true;
}
