#include "../private_api.h"

bool flecs_query_cache_search(
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
        op_ctx->last = NULL;

        if (cache->order_by && cache->list.info.table_count) {
            op_ctx->node = ecs_vec_first(&cache->table_slices);
        }
    }

    printf("- cache iter\n");

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

    if (node != op_ctx->last) {
        ctx->vars[0].range.table = node->table;
        ctx->vars[0].range.count = 0;
        ctx->vars[0].range.offset = 0;
        it->group_id = node->group_id;
        op_ctx->node = node->next;
        printf("next = %p\n", op_ctx->node);
        op_ctx->prev = node;
        return true;
    }

    return false;
}
