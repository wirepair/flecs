/**
 * @file entity_filter.c
 * @brief Querys that are applied to entities in a table.
 * 
 * After a table has been matched by a query, additional filters may have to
 * be applied before returning entities to the application. The two scenarios
 * under which this happens are queries for union relationship pairs (entities
 * for multiple targets are stored in the same table) and toggles (components 
 * that are enabled/disabled with a bitset).
 */

#include "private_api.h"

static
int32_t flecs_get_flattened_target(
    ecs_world_t *world,
    EcsTarget *cur,
    ecs_entity_t rel,
    ecs_id_t id,
    ecs_entity_t *src_out,
    ecs_table_record_t **tr_out)
{
    ecs_id_record_t *idr = flecs_id_record_get(world, id);
    if (!idr) {
        return -1;
    }

    ecs_record_t *r = cur->target;
    ecs_assert(r != NULL, ECS_INTERNAL_ERROR, NULL);

    ecs_table_t *table = r->table;
    if (!table) {
        return -1;
    }

    ecs_table_record_t *tr = flecs_id_record_get_table(idr, table);
    if (tr) {
        *src_out = ecs_record_get_entity(r);
        *tr_out = tr;
        return tr->index;
    }

    if (table->flags & EcsTableHasTarget) {
        int32_t col = table->column_map[table->_->ft_offset];
        ecs_assert(col != -1, ECS_INTERNAL_ERROR, NULL);
        EcsTarget *next = table->data.columns[col].data.array;
        next = ECS_ELEM_T(next, EcsTarget, ECS_RECORD_TO_ROW(r->row));
        return flecs_get_flattened_target(
            world, next, rel, id, src_out, tr_out);
    }

    return ecs_search_relation(
        world, table, 0, id, rel, EcsSelf|EcsUp, src_out, NULL, tr_out);
}

void flecs_entity_filter_init(
    ecs_world_t *world,
    ecs_entity_filter_t **entity_filter,
    const ecs_query_t *filter,
    const ecs_table_t *table,
    ecs_id_t *ids,
    int32_t *columns)
{
    ecs_poly_assert(world, ecs_world_t);
    ecs_assert(entity_filter != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(filter != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(table != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(ids != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_assert(columns != NULL, ECS_INTERNAL_ERROR, NULL);
    ecs_allocator_t *a = &world->allocator;
    ecs_entity_filter_t ef;
    ecs_os_zeromem(&ef);
    ecs_vec_t *ft_terms = &ef.ft_terms;
    if (*entity_filter) {
        ef.ft_terms = (*entity_filter)->ft_terms;
    }

    ecs_vec_reset_t(a, ft_terms, flecs_flat_table_term_t);
    const ecs_term_t *terms = filter->terms;
    int32_t i, term_count = filter->term_count;
    bool has_filter = false;
    ef.flat_tree_column = -1;

    /* Look for flattened fields */
    if (table->flags & EcsTableHasTarget) {
        const ecs_table_record_t *tr = flecs_table_record_get(world, table, 
            ecs_pair_t(EcsTarget, EcsWildcard));
        ecs_assert(tr != NULL, ECS_INTERNAL_ERROR, NULL);
        int32_t column = tr->index;
        ecs_assert(column != -1, ECS_INTERNAL_ERROR, NULL);
        ecs_entity_t rel = ecs_pair_second(world, table->type.array[column]);

        for (i = 0; i < term_count; i ++) {
            if (ecs_term_match_0(&terms[i])) {
                continue;
            }

            if (terms[i].trav == rel) {
                ef.flat_tree_column = table->column_map[column];
                ecs_assert(ef.flat_tree_column != -1, 
                    ECS_INTERNAL_ERROR, NULL);
                has_filter = true;
                
                flecs_flat_table_term_t *term = ecs_vec_append_t(
                    a, ft_terms, flecs_flat_table_term_t);
                term->field_index = terms[i].field_index;
                term->term = &terms[i];
                ecs_os_zeromem(&term->monitor);
            }
        }
    }

    if (has_filter) {
        if (!*entity_filter) {
            *entity_filter = ecs_os_malloc_t(ecs_entity_filter_t);
        }
        ecs_assert(*entity_filter != NULL, ECS_OUT_OF_MEMORY, NULL);
        **entity_filter = ef;
    }
}

void flecs_entity_filter_fini(
    ecs_world_t *world,
    ecs_entity_filter_t *ef)
{
    if (!ef) {
        return;
    }

    ecs_allocator_t *a = &world->allocator;

    flecs_flat_table_term_t *fields = ecs_vec_first(&ef->ft_terms);
    int32_t i, term_count = ecs_vec_count(&ef->ft_terms);
    for (i = 0; i < term_count; i ++) {
        ecs_vec_fini_t(NULL, &fields[i].monitor, flecs_flat_monitor_t);
    }

    ecs_vec_fini_t(a, &ef->ft_terms, flecs_flat_table_term_t);
    ecs_os_free(ef);
}

int flecs_entity_filter_next(
    ecs_entity_filter_iter_t *it)
{
    ecs_table_t *table = it->range.table;
    ecs_entity_filter_t *ef = it->entity_filter;
    int32_t flat_tree_column = ef->flat_tree_column;
    ecs_table_range_t *range = &it->range;
    int32_t range_end = range->offset + range->count;
    int result = EcsIterNext;
    bool found = false;

    do {
        found = false;

        if (flat_tree_column != -1) {
            bool first_for_table = it->prev != table;
            ecs_iter_t *iter = it->it;
            ecs_world_t *world = iter->real_world;
            EcsTarget *ft = table->data.columns[flat_tree_column].data.array;
            int32_t ft_offset;
            int32_t ft_count;

            if (first_for_table) {
                ft_offset = it->flat_tree_offset = range->offset;
                it->target_count = 1;
            } else {
                it->flat_tree_offset += ft[it->flat_tree_offset].count;
                ft_offset = it->flat_tree_offset;
                it->target_count ++;
            }

            ecs_assert(ft_offset < ecs_table_count(table), 
                ECS_INTERNAL_ERROR, NULL);

            EcsTarget *cur = &ft[ft_offset];
            ft_count = cur->count;
            bool is_last = (ft_offset + ft_count) >= range_end;

            int32_t i, field_count = ecs_vec_count(&ef->ft_terms);
            flecs_flat_table_term_t *fields = ecs_vec_first(&ef->ft_terms);
            for (i = 0; i < field_count; i ++) {
                flecs_flat_table_term_t *field = &fields[i];
                ecs_vec_init_if_t(&field->monitor, flecs_flat_monitor_t);
                int32_t field_index = field->field_index;
                ecs_id_t id = it->it->ids[field_index];
                ecs_id_t flat_pair = table->type.array[flat_tree_column];
                ecs_entity_t rel = ECS_PAIR_FIRST(flat_pair);
                ecs_entity_t tgt;
                ecs_table_record_t *tr;
                int32_t tgt_col = flecs_get_flattened_target(
                    world, cur, rel, id, &tgt, &tr);
                if (tgt_col != -1) {
                    iter->sources[field_index] = tgt;
                    iter->columns[field_index] = /* encode flattened field */
                        -(iter->field_count + tgt_col + 1);
                    ecs_assert(tr != NULL, ECS_INTERNAL_ERROR, NULL);

                    /* Keep track of maximum value encountered in target table
                     * dirty state so this doesn't have to be recomputed when
                     * synchronizing the query monitor. */
                    ecs_vec_set_min_count_zeromem_t(NULL, &field->monitor, 
                        flecs_flat_monitor_t, it->target_count);
                    ecs_table_t *tgt_table = tr->hdr.table;
                    int32_t *ds = flecs_table_get_dirty_state(world, tgt_table);
                    ecs_assert(ds != NULL, ECS_INTERNAL_ERROR, NULL);
                    ecs_vec_get_t(&field->monitor, flecs_flat_monitor_t, 
                        it->target_count - 1)->table_state = ds[tgt_col + 1];
                } else {
                    if (field->term->oper == EcsOptional) {
                        iter->columns[field_index] = 0;
                        iter->ptrs[field_index] = NULL;
                    } else {
                        it->prev = NULL;
                        break;
                    }
                }
            }
            if (i != field_count) {
                if (is_last) {
                    break;
                }
            } else {
                found = true;
                if ((ft_offset + ft_count) == range_end) {
                    result = EcsIterNextYield;
                } else {
                    result = EcsIterYield;
                }
            }

            range->offset = ft_offset;
            range->count = ft_count;
            it->prev = table;
        }
    } while (!found);

    it->prev = table;

    if (!found) {
        return EcsIterNext;
    } else {
        return result;
    }
}
