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

    return true;
}

bool flecs_query_cache_data_search(
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

static
void flecs_query_is_cache_data_populate(
    ecs_iter_t *it,
    const ecs_query_run_ctx_t *ctx,
    ecs_query_cache_table_match_t *node)
{
    ecs_table_t *table = node->table;
    ecs_var_t *var = &ctx->vars[0];
    int32_t i, count = var->range.count, offset = var->range.offset;
    if (!count) {
        count = ecs_table_count(table);
        if (!count) {
            return;
        }
    }
    if (!it->references) {
        int32_t field_count = it->field_count;
        ecs_data_t *data = &table->data;
        for (i = 0; i < field_count; i ++) {
            int32_t column = node->storage_columns[i];
            if (column < 0) {
                it->ptrs[i] = NULL;
                continue;
            }

            ecs_size_t size = it->sizes[i];
            if (!size) {
                it->ptrs[i] = NULL;
                continue;
            }

            it->ptrs[i] = ecs_vec_get(&data->columns[column].data,
                it->sizes[i], offset);
        }

        ECS_BIT_CLEAR(it->flags, EcsIterHasShared);
    } else {
        if (!count) {
            count = ecs_table_count(table);
        }
        flecs_iter_populate_data(
            it->real_world, it, table, offset, count, it->ptrs);
    }
}

bool flecs_query_is_cache_data_search(
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

    flecs_query_is_cache_data_populate(it, ctx, node);

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
