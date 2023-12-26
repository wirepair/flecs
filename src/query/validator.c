/**
 * @file filter.c
 * @brief Uncached query implementation.
 * 
 * Uncached queries (filters) are stateless objects that do not cache their 
 * results. This file contains the creation and validation of uncached queries
 * and code for query iteration.
 * 
 * There file contains the implementation for term queries and filters. Term 
 * queries are uncached queries that only apply to a single term. Querys are
 * uncached queries that support multiple terms. Querys are built on top of
 * term queries: before iteration a filter will first find a "pivot" term (the
 * term with the smallest number of elements), and create a term iterator for
 * it. The output of that term iterator is then evaluated against the rest of
 * the terms of the filter.
 * 
 * Cached queries and observers are built using filters.
 */

#include "../private_api.h"
#include <ctype.h>

static
void flecs_query_validator_error(
    const ecs_query_validator_ctx_t *ctx,
    const char *fmt,
    ...)
{
    va_list args;
    va_start(args, fmt);

    int32_t term_start = 0;

    char *expr = NULL;
    if (ctx->filter) {
        expr = flecs_query_str(ctx->world, ctx->filter, ctx, &term_start);
    } else {
        expr = ecs_term_str(ctx->world, ctx->term);
    }
    const char *name = NULL;
    if (ctx->filter && ctx->filter->entity) {
        name = ecs_get_name(ctx->filter->world, ctx->filter->entity);
    }
    ecs_parser_errorv(name, expr, term_start, fmt, args);
    ecs_os_free(expr);

    va_end(args);
}

static
int flecs_term_ref_finalize_flags(
    ecs_term_ref_t *ref,
    ecs_query_validator_ctx_t *ctx)
{
    if ((ref->id & EcsIsEntity) && (ref->id & EcsIsVariable)) {
        flecs_query_validator_error(ctx, "cannot set both IsEntity and IsVariable");
        return -1;
    }

    if (!(ref->id & (EcsIsEntity|EcsIsVariable|EcsIsName))) {
        if (ECS_TERM_REF_ID(ref) || ref->name) {
            if (ECS_TERM_REF_ID(ref) == EcsThis || 
                ECS_TERM_REF_ID(ref) == EcsWildcard || 
                ECS_TERM_REF_ID(ref) == EcsAny || 
                ECS_TERM_REF_ID(ref) == EcsVariable) 
            {
                /* Builtin variable ids default to variable */
                ref->id |= EcsIsVariable;
            } else {
                ref->id |= EcsIsEntity;
            }
        }
    }

    return 0;
}

static
int flecs_term_ref_lookup(
    const ecs_world_t *world,
    ecs_entity_t scope,
    ecs_term_ref_t *ref,
    ecs_query_validator_ctx_t *ctx)
{
    const char *name = ref->name;
    if (!name) {
        return 0;
    }

    if (ref->id & EcsIsVariable) {
        if (!ecs_os_strcmp(name, "This") || !ecs_os_strcmp(name, "this")) {
            ref->id = EcsThis | ECS_TERM_REF_FLAGS(ref);
            ref->name = NULL;
            return 0;
        }
        return 0;
    } else if (ref->id & EcsIsName) {
        if (ref->name == NULL) {
            flecs_query_validator_error(ctx, "IsName flag specified without name");
            return -1;
        }
        return 0;
    }

    ecs_assert(ref->id & EcsIsEntity, ECS_INTERNAL_ERROR, NULL);

    if (ecs_identifier_is_0(name)) {
        if (ECS_TERM_REF_ID(ref)) {
            flecs_query_validator_error(ctx, "name '0' does not match entity id");
            return -1;
        }
        return 0;
    }

    ecs_entity_t e = ecs_lookup_symbol(world, name, true, true);
    if (scope && !e) {
        e = ecs_lookup_child(world, scope, name);
    }

    if (!e) {
        if (ctx->filter && (ctx->filter->flags & EcsQueryAllowUnresolvedByName)) {
            ref->id |= EcsIsName;
            ref->id &= ~EcsIsEntity;
            return 0;
        } else {
            flecs_query_validator_error(ctx, "unresolved identifier '%s'", name);
            return -1;
        }
    }

    ecs_entity_t ref_id = ECS_TERM_REF_ID(ref);
    if (ref_id && ref_id != e) {
        char *e_str = ecs_get_fullpath(world, ref_id);
        flecs_query_validator_error(ctx, "name '%s' does not match term.id '%s'", 
            name, e_str);
        ecs_os_free(e_str);
        return -1;
    }

    ref->id = e | ECS_TERM_REF_FLAGS(ref);
    ref_id = ECS_TERM_REF_ID(ref);

    if (!ecs_os_strcmp(name, "*") || !ecs_os_strcmp(name, "_") || 
        !ecs_os_strcmp(name, "$")) 
    {
        ref->id &= ~EcsIsEntity;
        ref->id |= EcsIsVariable;
    }

    /* Check if looked up id is alive (relevant for numerical ids) */
    if (!(ref->id & EcsIsName) && ref_id) {
        if (!ecs_is_alive(world, ref_id)) {
            flecs_query_validator_error(ctx, "identifier '%s' is not alive", ref->name);
            return -1;
        }

        ref->name = NULL;
        return 0;
    }

    return 0;
}

static
int flecs_term_refs_finalize(
    const ecs_world_t *world,
    ecs_term_t *term,
    ecs_query_validator_ctx_t *ctx)
{
    ecs_term_ref_t *src = &term->src;
    ecs_term_ref_t *first = &term->first;
    ecs_term_ref_t *second = &term->second;

    if ((term->src.id & EcsCascade) && !(term->src.id & EcsUp)) {
        /* If cascade is specified without up/down, add up */
        term->src.id |= EcsUp;
    }

    if (!(src->id & EcsTraverseFlags)) {
        /* When no traversal flags are specified, the default traversal 
         * relationship is IsA so inherited components are matched by default */
        src->id |= EcsSelf | EcsUp;
        if (!term->trav) {
            term->trav = EcsIsA;
        }
    } else if ((src->id & EcsUp) && !term->trav) {
        /* When traversal flags are specified but no traversal relationship,
         * default to ChildOf, which is the most common kind of traversal. */
        term->trav = EcsChildOf;
    }

    /* Include subsets for component by default, to support inheritance */
    if (!(first->id & EcsTraverseFlags)) {
        first->id |= EcsSelf;
    }

    /* Traverse Self by default for pair target */
    if (!(second->id & EcsTraverseFlags)) {
        if (ECS_TERM_REF_ID(second) || second->name || (second->id & EcsIsEntity)) {
            second->id |= EcsSelf;
        }
    }

    /* Source defaults to This */
    if (!ECS_TERM_REF_ID(src) && (src->name == NULL) && !(src->id & EcsIsEntity)) {
        src->id = EcsThis | ECS_TERM_REF_FLAGS(src);
        src->id |= EcsIsVariable;
    }

    /* Initialize term identifier flags */
    if (flecs_term_ref_finalize_flags(src, ctx)) {
        return -1;
    }

    if (flecs_term_ref_finalize_flags(first, ctx)) {
        return -1;
    }

    if (flecs_term_ref_finalize_flags(second, ctx)) {
        return -1;
    }

    /* Lookup term identifiers by name */
    if (flecs_term_ref_lookup(world, 0, src, ctx)) {
        return -1;
    }
    if (flecs_term_ref_lookup(world, 0, first, ctx)) {
        return -1;
    }

    ecs_entity_t first_id = 0;
    ecs_entity_t oneof = 0;
    if (first->id & EcsIsEntity) {
        first_id = ECS_TERM_REF_ID(first);

        /* If first element of pair has OneOf property, lookup second element of
         * pair in the value of the OneOf property */
        oneof = flecs_get_oneof(world, first_id);
    }

    if (flecs_term_ref_lookup(world, oneof, &term->second, ctx)) {
        return -1;
    }

    /* If source is 0, reset traversal flags */
    if (ECS_TERM_REF_ID(src) == 0 && src->id & EcsIsEntity) {
        src->id &= ~EcsTraverseFlags;
        term->trav = 0;
    }

    /* If source is wildcard, term won't return any data */
    if ((src->id & EcsIsVariable) && ecs_id_is_wildcard(ECS_TERM_REF_ID(src))) {
        term->inout |= EcsInOutNone;
    }

    return 0;
}

static
ecs_entity_t flecs_term_ref_get_entity(
    const ecs_term_ref_t *ref)
{
    if (ref->id & EcsIsEntity) {
        return ECS_TERM_REF_ID(ref); /* Id is known */
    } else if (ref->id & EcsIsVariable) {
        /* Return wildcard for variables, as they aren't known yet */
        if (ECS_TERM_REF_ID(ref) != EcsAny) {
            /* Any variable should not use wildcard, as this would return all
             * ids matching a wildcard, whereas Any returns the first match */
            return EcsWildcard;
        } else {
            return EcsAny;
        }
    } else {
        return 0; /* Term id is uninitialized */
    }
}

static
int flecs_term_populate_id(
    ecs_term_t *term)
{
    ecs_entity_t first = flecs_term_ref_get_entity(&term->first);
    ecs_entity_t second = flecs_term_ref_get_entity(&term->second);
    ecs_id_t flags = term->id & ECS_ID_FLAGS_MASK;

    if (first & ECS_ID_FLAGS_MASK) {
        return -1;
    }
    if (second & ECS_ID_FLAGS_MASK) {
        return -1;
    }

    if ((second || (term->second.id & EcsIsEntity))) {
        flags |= ECS_PAIR;
    }

    if (!second && !ECS_HAS_ID_FLAG(flags, PAIR)) {
        term->id = first | flags;
    } else {
        term->id = ecs_pair(first, second) | flags;
    }

    return 0;
}

static
int flecs_term_populate_from_id(
    const ecs_world_t *world,
    ecs_term_t *term,
    ecs_query_validator_ctx_t *ctx)
{
    ecs_entity_t first = 0;
    ecs_entity_t second = 0;

    if (ECS_HAS_ID_FLAG(term->id, PAIR)) {
        first = ECS_PAIR_FIRST(term->id);
        second = ECS_PAIR_SECOND(term->id);

        if (!first) {
            flecs_query_validator_error(ctx, "missing first element in term.id");
            return -1;
        }
        if (!second) {
            if (first != EcsChildOf) {
                flecs_query_validator_error(ctx, "missing second element in term.id");
                return -1;
            } else {
                /* (ChildOf, 0) is allowed so filter can be used to efficiently
                 * query for root entities */
            }
        }
    } else {
        first = term->id & ECS_COMPONENT_MASK;
        if (!first) {
            flecs_query_validator_error(ctx, "missing first element in term.id");
            return -1;
        }
    }

    ecs_entity_t term_first = flecs_term_ref_get_entity(&term->first);
    if (term_first) {
        if ((uint32_t)term_first != (uint32_t)first) {
            flecs_query_validator_error(ctx, "mismatch between term.id and term.first");
            return -1;
        }
    } else {
        ecs_entity_t first_id = ecs_get_alive(world, first);
        if (!first_id) {
            term->first.id = first | ECS_TERM_REF_FLAGS(&term->first);
        } else {
            term->first.id = first_id | ECS_TERM_REF_FLAGS(&term->first);
        }
    }

    ecs_entity_t term_second = flecs_term_ref_get_entity(&term->second);
    if (term_second) {
        if ((uint32_t)term_second != second) {
            flecs_query_validator_error(ctx, "mismatch between term.id and term.second");
            return -1;
        }
    } else if (second) {
        ecs_entity_t second_id = ecs_get_alive(world, second);
        if (!second_id) {
            term->second.id = second | ECS_TERM_REF_FLAGS(&term->second);
        } else {
            term->second.id = second_id | ECS_TERM_REF_FLAGS(&term->second);
        }
    }

    return 0;
}

static
int flecs_term_verify_eq_pred(
    const ecs_term_t *term,
    ecs_query_validator_ctx_t *ctx)
{
    const ecs_term_ref_t *second = &term->second;
    const ecs_term_ref_t *src = &term->src;
    ecs_entity_t first_id = ECS_TERM_REF_ID(&term->first);
    ecs_entity_t second_id = ECS_TERM_REF_ID(&term->second);
    ecs_entity_t src_id = ECS_TERM_REF_ID(&term->src);

    if (term->oper != EcsAnd && term->oper != EcsNot && term->oper != EcsOr) {
        flecs_query_validator_error(ctx, "invalid operator combination");
        goto error;
    }

    if ((src->id & EcsIsName) && (second->id & EcsIsName)) {
        flecs_query_validator_error(ctx, "both sides of operator cannot be a name");
        goto error;
    }

    if ((src->id & EcsIsEntity) && (second->id & EcsIsEntity)) {
        flecs_query_validator_error(ctx, "both sides of operator cannot be an entity");
        goto error;
    }

    if (!(src->id & EcsIsVariable)) {
        flecs_query_validator_error(ctx, "left-hand of operator must be a variable");
        goto error;
    }

    if (first_id == EcsPredMatch && !(second->id & EcsIsName)) {
        flecs_query_validator_error(ctx, "right-hand of match operator must be a string");
        goto error;
    }

    if ((src->id & EcsIsVariable) && (second->id & EcsIsVariable)) {
        if (src_id && src_id == second_id) {
            flecs_query_validator_error(ctx, "both sides of operator are equal");
            goto error;
        }
        if (src->name && second->name && !ecs_os_strcmp(src->name, second->name)) {
            flecs_query_validator_error(ctx, "both sides of operator are equal");
            goto error;
        }
    }

    return 0;
error:
    return -1;
}

static
int flecs_term_verify(
    const ecs_world_t *world,
    const ecs_term_t *term,
    ecs_query_validator_ctx_t *ctx)
{
    const ecs_term_ref_t *first = &term->first;
    const ecs_term_ref_t *second = &term->second;
    const ecs_term_ref_t *src = &term->src;
    ecs_entity_t first_id = 0, second_id = 0;
    ecs_id_t flags = term->id & ECS_ID_FLAGS_MASK;
    ecs_id_t id = term->id;

    if ((src->id & EcsIsName) && (second->id & EcsIsName)) {
        flecs_query_validator_error(ctx, "mismatch between term.id_flags & term.id");
        return -1;
    }

    ecs_entity_t src_id = ECS_TERM_REF_ID(src);
    if (first->id & EcsIsEntity) {
        first_id = ECS_TERM_REF_ID(first);
    }
    if (second->id & EcsIsEntity) {
        second_id = ECS_TERM_REF_ID(second);
    }

    if (first_id == EcsPredEq || first_id == EcsPredMatch || first_id == EcsPredLookup) {
        return flecs_term_verify_eq_pred(term, ctx);
    }

    if (ecs_term_ref_is_set(second) && !ECS_HAS_ID_FLAG(flags, PAIR)) {
        flecs_query_validator_error(ctx, "expected PAIR flag for term with pair");
        return -1;
    } else if (!ecs_term_ref_is_set(second) && ECS_HAS_ID_FLAG(flags, PAIR)) {
        if (first_id != EcsChildOf) {
            flecs_query_validator_error(ctx, "unexpected PAIR flag for term without pair");
            return -1;
        } else {
            /* Exception is made for ChildOf so we can use (ChildOf, 0) to match
             * all entities in the root */
        }
    }

    if (!ecs_term_ref_is_set(src)) {
        flecs_query_validator_error(ctx, "term.src is not initialized");
        return -1;
    }

    if (!ecs_term_ref_is_set(first)) {
        flecs_query_validator_error(ctx, "term.first is not initialized");
        return -1;
    }

    if (ECS_HAS_ID_FLAG(flags, PAIR)) {
        if (!ECS_PAIR_FIRST(id)) {
            flecs_query_validator_error(ctx, "invalid 0 for first element in pair id");
            return -1;
        }
        if ((ECS_PAIR_FIRST(id) != EcsChildOf) && !ECS_PAIR_SECOND(id)) {
            flecs_query_validator_error(ctx, "invalid 0 for second element in pair id");
            return -1;
        }

        if ((first->id & EcsIsEntity) && 
            (ecs_entity_t_lo(first_id) != ECS_PAIR_FIRST(id))) 
        {
            flecs_query_validator_error(ctx, "mismatch between term.id and term.first");
            return -1;
        }
        if ((first->id & EcsIsVariable) && 
            !ecs_id_is_wildcard(ECS_PAIR_FIRST(id)))
        {
            char *id_str = ecs_id_str(world, id);
            flecs_query_validator_error(ctx, 
                "expected wildcard for variable term.first (got %s)", id_str);
            ecs_os_free(id_str);
            return -1;
        }

        if ((second->id & EcsIsEntity) && 
            (ecs_entity_t_lo(second_id) != ECS_PAIR_SECOND(id))) 
        {
            flecs_query_validator_error(ctx, "mismatch between term.id and term.second");
            return -1;
        }
        if ((second->id & EcsIsVariable) && 
            !ecs_id_is_wildcard(ECS_PAIR_SECOND(id))) 
        {
            char *id_str = ecs_id_str(world, id);
            flecs_query_validator_error(ctx, 
                "expected wildcard for variable term.second (got %s)", id_str);
            ecs_os_free(id_str);
            return -1;
        }
    } else {
        ecs_entity_t component = id & ECS_COMPONENT_MASK;
        if (!component) {
            flecs_query_validator_error(ctx, "missing component id");
            return -1;
        }
        if ((first->id & EcsIsEntity) && 
            (ecs_entity_t_lo(first_id) != ecs_entity_t_lo(component))) 
        {
            flecs_query_validator_error(ctx, "mismatch between term.id and term.first");
            return -1;
        }
        if ((first->id & EcsIsVariable) && !ecs_id_is_wildcard(component)) {
            char *id_str = ecs_id_str(world, id);
            flecs_query_validator_error(ctx, 
                "expected wildcard for variable term.first (got %s)", id_str);
            ecs_os_free(id_str);
            return -1;
        }
    }

    if (first_id) {
        if (ecs_term_ref_is_set(second)) {
            ecs_flags64_t mask = EcsIsEntity | EcsIsVariable;
            if ((src->id & mask) == (second->id & mask)) {
                bool is_same = false;
                if (src->id & EcsIsEntity) {
                    is_same = src_id == second_id;
                } else if (src->name && second->name) {
                    is_same = !ecs_os_strcmp(src->name, second->name);
                }

                if (is_same && ecs_has_id(world, first_id, EcsAcyclic)
                    && !(term->flags & EcsTermReflexive)) 
                {
                    char *pred_str = ecs_get_fullpath(world, term->first.id);
                    flecs_query_validator_error(ctx, "term with acyclic relationship"
                        " '%s' cannot have same subject and object",
                            pred_str);
                    ecs_os_free(pred_str);
                    return -1;
                }
            }
        }

        if (second_id && !ecs_id_is_wildcard(second_id)) {
            ecs_entity_t oneof = flecs_get_oneof(world, first_id);
            if (oneof) {
                if (!ecs_has_pair(world, second_id, EcsChildOf, oneof)) {
                    char *second_str = ecs_get_fullpath(world, second_id);
                    char *oneof_str = ecs_get_fullpath(world, oneof);
                    char *id_str = ecs_id_str(world, term->id);
                    flecs_query_validator_error(ctx, 
                        "invalid target '%s' for %s: must be child of '%s'",
                            second_str, id_str, oneof_str);
                    ecs_os_free(second_str);
                    ecs_os_free(oneof_str);
                    ecs_os_free(id_str);
                    return -1;
                }
            }
        }
    }

    if (term->trav) {
        if (!ecs_has_id(world, term->trav, EcsTraversable)) {
            char *r_str = ecs_get_fullpath(world, term->trav);
            flecs_query_validator_error(ctx, 
                "cannot traverse non-traversable relationship '%s'", r_str);
            ecs_os_free(r_str);
            return -1;
        }
    }

    return 0;
}

static
int flecs_term_finalize(
    const ecs_world_t *world,
    ecs_term_t *term,
    ecs_query_validator_ctx_t *ctx)
{
    ctx->term = term;

    ecs_term_ref_t *src = &term->src;
    ecs_term_ref_t *first = &term->first;
    ecs_term_ref_t *second = &term->second;
    ecs_flags64_t src_flags = ECS_TERM_REF_FLAGS(src);
    ecs_flags64_t first_flags = ECS_TERM_REF_FLAGS(first);
    ecs_flags64_t second_flags = ECS_TERM_REF_FLAGS(second);

    if (term->id & ~ECS_ID_FLAGS_MASK) {
        if (flecs_term_populate_from_id(world, term, ctx)) {
            return -1;
        }
    }

    if (flecs_term_refs_finalize(world, term, ctx)) {
        return -1;
    }

    ecs_entity_t first_id = ECS_TERM_REF_ID(first);
    ecs_entity_t second_id = ECS_TERM_REF_ID(second);
    ecs_entity_t src_id = ECS_TERM_REF_ID(src);

    if ((first->id & EcsIsVariable) && (first_id == EcsAny)) {
        term->flags |= EcsTermMatchAny;
    }
    if ((second->id & EcsIsVariable) && (second_id == EcsAny)) {
        term->flags |= EcsTermMatchAny;
    }
    if ((src->id & EcsIsVariable) && (src_id == EcsAny)) {
        term->flags |= EcsTermMatchAnySrc;
    }

    ecs_flags64_t ent_var_mask = EcsIsEntity | EcsIsVariable;

    /* If EcsVariable is used by itself, assign to predicate (singleton) */
    if ((ECS_TERM_REF_ID(src) == EcsVariable) && (src->id & EcsIsVariable)) {
        src->id = first->id | ECS_TERM_REF_FLAGS(src);
        src->id &= ~ent_var_mask;
        src->id |= first->id & ent_var_mask;
    }
    if ((ECS_TERM_REF_ID(second) == EcsVariable) && (second->id & EcsIsVariable)) {
        second->id = first->id | ECS_TERM_REF_FLAGS(second);
        second->id &= ~ent_var_mask;
        second->id |= first->id & ent_var_mask;
    }

    if (!(term->id & ~ECS_ID_FLAGS_MASK)) {
        if (flecs_term_populate_id(term)) {
            return -1;
        }
    }

    /* If term queries for !(ChildOf, _), translate it to the builtin 
     * (ChildOf, 0) index which is a cheaper way to find root entities */
    if (term->oper == EcsNot && term->id == ecs_pair(EcsChildOf, EcsAny)) {
        term->oper = EcsAnd;
        term->id = ecs_pair(EcsChildOf, 0);
        second->id = 0 | ECS_TERM_REF_FLAGS(second);
        second->id |= EcsIsEntity;
        second->id &= ~EcsIsVariable;
    }

    if (!(first->id & EcsIsEntity)) {
        first_id = 0;
    }

    term->idr = flecs_query_cache_id_record_get(world, term->id);
    ecs_flags32_t id_flags = term->idr ? term->idr->flags : 0;

    if (first_id) {
        /* Only enable inheritance for ids which are inherited from at the time
         * of filter creation. To force component inheritance to be evaluated,
         * an application can explicitly set traversal flags. */
        if (flecs_id_record_get(world, ecs_pair(EcsIsA, first->id))) {
            if (!((first_flags & EcsTraverseFlags) == EcsSelf)) {
                term->flags |= EcsTermIdInherited;
            }
        }

        /* Don't traverse ids that cannot be inherited */
        if ((id_flags & EcsIdDontInherit) && (term->trav == EcsIsA)) {
            if (src_flags & EcsUp) {
                flecs_query_validator_error(ctx, 
                    "traversing not allowed for id that can't be inherited");
                return -1;
            }
            src->id &= ~EcsUp;
            term->trav = 0;
        }

        /* If component id is final, don't attempt component inheritance */
        ecs_record_t *first_record = flecs_entities_get(world, first_id);
        ecs_table_t *first_table = first_record ? first_record->table : NULL;
        if (first_table) {
            /* Add traversal flags for transitive relationships */
            if (ecs_term_ref_is_set(second) && !((second_flags & EcsTraverseFlags) == EcsSelf)) {
                if (!((src->id & EcsIsVariable) && (src_id == EcsAny))) {
                    if (!((second->id & EcsIsVariable) && (second_id == EcsAny))) {
                        if (ecs_table_has_id(world, first_table, EcsTransitive)) {
                            term->flags |= EcsTermTransitive;
                        }
                    }
                }
            }

            if (ecs_table_has_id(world, first_table, EcsReflexive)) {
                term->flags |= EcsTermReflexive;
            }
        }
    }

    if (ECS_TERM_REF_ID(first) == EcsVariable) {
        flecs_query_validator_error(ctx, "invalid $ for term.first");
        return -1;
    }

    if (term->oper == EcsAndFrom || term->oper == EcsOrFrom || term->oper == EcsNotFrom) {
        if (term->inout != EcsInOutDefault && term->inout != EcsInOutNone) {
            flecs_query_validator_error(ctx, 
                "invalid inout value for AndFrom/OrFrom/NotFrom term");
            return -1;
        }
    }

    /* Is term trivial/cacheable */
    bool cacheable_term = true;
    bool trivial_term = true;
    if (term->oper != EcsAnd) {
        trivial_term = false;
    }

    if (ecs_id_is_wildcard(term->id)) {
        if (!(term->idr && term->idr->flags & EcsIdExclusive)) {
            trivial_term = false;
        }
        if (first->id & EcsIsVariable) {
            if (!ecs_id_is_wildcard(first_id) || first_id == EcsAny) {
                trivial_term = false;
                cacheable_term = false;
            }
        }
        if (second->id & EcsIsVariable) {
            if (!ecs_id_is_wildcard(second_id) || second_id == EcsAny) {
                trivial_term = false;
                cacheable_term = false;
            }
        }
    }
    if (!ecs_term_match_this(term)) {
        trivial_term = false;
    }
    if (term->flags & EcsTermTransitive) {
        trivial_term = false;
        cacheable_term = false;
    }
    if (term->flags & EcsTermIdInherited) {
        trivial_term = false;
        cacheable_term = false;
    }
    if (term->trav && term->trav != EcsIsA) {
        trivial_term = false;
    }
    if (!(src->id & EcsSelf)) {
        trivial_term = false;
    }
    if (ECS_TERM_REF_ID(src) != EcsThis) {
        cacheable_term = false;
    }

    ECS_BIT_COND(term->flags, EcsTermIsTrivial, trivial_term);
    ECS_BIT_COND(term->flags, EcsTermIsCacheable, cacheable_term);

    if (flecs_term_verify(world, term, ctx)) {
        return -1;
    }

    return 0;
}

bool ecs_identifier_is_0(
    const char *id)
{
    return id[0] == '0' && !id[1];
}

bool ecs_term_ref_is_set(
    const ecs_term_ref_t *ref)
{
    return ECS_TERM_REF_ID(ref) != 0 || ref->name != NULL || ref->id & EcsIsEntity;
}

bool ecs_term_is_initialized(
    const ecs_term_t *term)
{
    return term->id != 0 || ecs_term_ref_is_set(&term->first);
}

bool ecs_term_match_this(
    const ecs_term_t *term)
{
    return (term->src.id & EcsIsVariable) && 
        (ECS_TERM_REF_ID(&term->src) == EcsThis);
}

bool ecs_term_match_0(
    const ecs_term_t *term)
{
    return (!ECS_TERM_REF_ID(&term->src) && (term->src.id & EcsIsEntity));
}

int ecs_term_finalize(
    const ecs_world_t *world,
    ecs_term_t *term)
{
    ecs_query_validator_ctx_t ctx = {0};
    ctx.world = world;
    ctx.term = term;
    return flecs_term_finalize(world, term, &ctx);
}

static
ecs_term_t* flecs_query_or_other_type(
    ecs_query_t *q,
    int32_t t)
{
    ecs_term_t *term = &q->terms[t];
    ecs_term_t *first = NULL;
    while (t--) {
        if (q->terms[t].oper != EcsOr) {
            break;
        }
        first = &q->terms[t];
    }

    if (first) {
        ecs_world_t *world = q->world;
        const ecs_type_info_t *first_type;
        if (first->idr) {
            first_type = first->idr->type_info;
        } else {
            first_type = ecs_get_type_info(world, first->id);
        }
        const ecs_type_info_t *term_type;
        if (term->idr) {
            term_type = term->idr->type_info;
        } else {
            term_type = ecs_get_type_info(world, term->id);
        }

        if (first_type == term_type) {
            return NULL;
        }
        return first;
    } else {
        return NULL;
    }
}

static
int flecs_query_query_finalize_terms(
    const ecs_world_t *world,
    ecs_query_t *q)
{
    int32_t i, term_count = q->term_count, field_count = 0;
    ecs_term_t *terms = q->terms;
    int32_t filter_terms = 0, scope_nesting = 0, cacheable_terms = 0;
    bool cond_set = false;

    ecs_query_validator_ctx_t ctx = {0};
    ctx.world = world;
    ctx.filter = q;

    q->flags |= EcsQueryMatchOnlyThis;

    for (i = 0; i < term_count; i ++) {
        bool filter_term = false;
        ecs_term_t *term = &terms[i];
        ctx.term_index = i;
        if (flecs_term_finalize(world, term, &ctx)) {
            return -1;
        }

        if (term->flags & EcsTermIsCacheable) {
            cacheable_terms ++;
        }

        if (i && term[-1].oper == EcsOr) {
            if (ECS_TERM_REF_ID(&term[-1].src) != ECS_TERM_REF_ID(&term->src)) {
                flecs_query_validator_error(&ctx, "mismatching src.id for OR terms");
                return -1;
            }
            if (term->oper != EcsOr && term->oper != EcsAnd) {
                flecs_query_validator_error(&ctx, 
                    "term after OR operator must use AND operator");
                return -1;
            }
        } else {
            field_count ++;
        }

        term->field_index = flecs_ito(int16_t, field_count - 1);

        if (ecs_id_is_wildcard(term->id)) {
            q->flags |= EcsQueryMatchWildcards;
        }

        if (ecs_term_match_this(term)) {
            ECS_BIT_SET(q->flags, EcsQueryMatchThis);
        } else {
            ECS_BIT_CLEAR(q->flags, EcsQueryMatchOnlyThis);
        }

        if (ECS_TERM_REF_ID(term) == EcsPrefab) {
            ECS_BIT_SET(q->flags, EcsQueryMatchPrefab);
        }
        if (ECS_TERM_REF_ID(term) == EcsDisabled && (term->src.id & EcsSelf)) {
            ECS_BIT_SET(q->flags, EcsQueryMatchDisabled);
        }

        if (ECS_BIT_IS_SET(q->flags, EcsQueryNoData)) {
            term->inout = EcsInOutNone;
        }
        
        if (term->oper == EcsNot && term->inout == EcsInOutDefault) {
            term->inout = EcsInOutNone;
        }

        if ((term->id == EcsWildcard) || (term->id == 
            ecs_pair(EcsWildcard, EcsWildcard))) 
        {
            /* If term type is unknown beforehand, default the inout type to
             * none. This prevents accidentally requesting lots of components,
             * which can put stress on serializer code. */
            if (term->inout == EcsInOutDefault) {
                term->inout = EcsInOutNone;
            }
        }

        if (term->inout == EcsInOutNone) {
            filter_term = true;
        } else if (term->idr) {
            if (!term->idr->type_info && !(term->idr->flags & EcsIdUnion)) {
                filter_term = true;
            }
        } else if (!ecs_id_is_union(world, term->id)) {
            /* Union ids aren't filters because they return their target
             * as component value with type ecs_entity_t */
            if (ecs_id_is_tag(world, term->id)) {
                filter_term = true;
            } else if (ECS_PAIR_SECOND(term->id) == EcsWildcard) {
                /* If the second element of a pair is a wildcard and the first
                 * element is not a type, we can't know in advance what the
                 * type of the term is, so it can't provide data. */
                if (!ecs_get_type_info(world, ecs_pair_first(world, term->id))) {
                    filter_term = true;
                }
            }
        }

        if (term->inout != EcsIn && term->inout != EcsInOutNone) {
            /* Non-this terms default to EcsIn */
            if (ecs_term_match_this(term) || term->inout != EcsInOutDefault) {
                q->flags |= EcsQueryHasOutTerms;
            }

            bool match_non_this = !ecs_term_match_this(term) || 
                (term->src.id & EcsUp);
            if (match_non_this && term->inout != EcsInOutDefault) {
                q->flags |= EcsQueryHasNonThisOutTerms;
            }
        }

        if (!filter_term) {
            if (term->oper == EcsOr || (i && term[-1].oper == EcsOr)) {
                ecs_term_t *first = flecs_query_or_other_type(q, i);
                if (first) {
                    if (first == &term[-1]) {
                        filter_terms ++;
                    }
                    filter_term = true;
                }
            }
        }

        if (filter_term) {
            filter_terms ++;
            term->flags |= EcsTermNoData;
        } else {
            q->data_fields |= (1llu << term->field_index);
        }

        if (term->idr) {
            if (ecs_os_has_threading()) {
                ecs_os_ainc(&term->idr->keep_alive);
            } else {
                term->idr->keep_alive ++;
            }
        }

        if (term->oper == EcsOptional || term->oper == EcsNot) {
            cond_set = true;
        }

        ecs_entity_t first_id = ECS_TERM_REF_ID(&term->first);
        if (first_id == EcsPredEq || first_id == EcsPredMatch ||
            first_id == EcsPredLookup)
        {
            q->flags |= EcsQueryHasPred;
        }

        if (first_id == EcsScopeOpen) {
            q->flags |= EcsQueryHasScopes;
            scope_nesting ++;
        }
        if (first_id == EcsScopeClose) {
            if (i && ECS_TERM_REF_ID(&terms[i - 1].first) == EcsScopeOpen) {
                flecs_query_validator_error(&ctx, "invalid empty scope");
                return -1;
            }

            q->flags |= EcsQueryHasScopes;
            scope_nesting --;
        }
        if (scope_nesting < 0) {
            flecs_query_validator_error(&ctx, "'}' without matching '{'");
        }
    }

    if (scope_nesting != 0) {
        flecs_query_validator_error(&ctx, "missing '}'");
        return -1;
    }

    if (term_count && (terms[term_count - 1].oper == EcsOr)) {
        flecs_query_validator_error(&ctx, 
            "last term of filter can't have OR operator");
        return -1;
    }

    q->field_count = flecs_ito(int8_t, field_count);

    if (field_count) {
        for (i = 0; i < term_count; i ++) {
            ecs_term_t *term = &terms[i];
            ecs_id_record_t *idr = term->idr;
            int32_t field = term->field_index;

            if (term->oper == EcsOr || (i && (term[-1].oper == EcsOr))) {
                if (flecs_query_or_other_type(q, i)) {
                    q->sizes[field] = 0;
                    continue;
                }
            }

            if (idr) {
                if (!ECS_IS_PAIR(idr->id) || ECS_PAIR_FIRST(idr->id) != EcsWildcard) {
                    if (idr->flags & EcsIdUnion) {
                        q->sizes[field] = ECS_SIZEOF(ecs_entity_t);
                    } else if (idr->type_info) {
                        q->sizes[field] = idr->type_info->size;
                    }
                }
            } else {
                bool is_union = false;
                if (ECS_IS_PAIR(term->id)) {
                    ecs_entity_t first = ecs_pair_first(world, term->id);
                    if (ecs_has_id(world, first, EcsUnion)) {
                        is_union = true;
                    }
                }
                if (is_union) {
                    q->sizes[field] = ECS_SIZEOF(ecs_entity_t);
                } else {
                    const ecs_type_info_t *ti = ecs_get_type_info(
                        world, term->id);
                    if (ti) {
                        q->sizes[field] = ti->size;
                    }
                }
            }
        }
    }

    ecs_assert(filter_terms <= term_count, ECS_INTERNAL_ERROR, NULL);
    if (filter_terms == term_count) {
        ECS_BIT_SET(q->flags, EcsQueryNoData);
    }

    ECS_BIT_COND(q->flags, EcsQueryHasCondSet, cond_set);

    /* Check if this is a trivial filter */
    if ((q->flags & EcsQueryMatchOnlyThis)) {
        if (!(q->flags & 
            (EcsQueryHasPred|EcsQueryMatchDisabled|EcsQueryMatchPrefab))) 
        {
            ECS_BIT_SET(q->flags, EcsQueryMatchOnlySelf);

            for (i = 0; i < term_count; i ++) {
                ecs_term_t *term = &terms[i];
                ecs_term_ref_t *src = &term->src;

                if (src->id & EcsUp) {
                    ECS_BIT_CLEAR(q->flags, EcsQueryMatchOnlySelf);
                }

                if (!(term->flags & EcsTermIsTrivial)) {
                    break;
                }

                if (!(q->flags & EcsQueryNoData)) {
                    if (term->inout == EcsInOutNone) {
                        break;
                    }
                }
            }
            if (term_count && (i == term_count)) {
                ECS_BIT_SET(q->flags, EcsQueryIsTrivial);
            }
        }
    }

    /* Set cacheable flags */
    if (!(q->flags & EcsQueryMatchEmptyTables)) {
        ECS_BIT_COND(q->flags, EcsQueryHasCacheable, 
            cacheable_terms != 0);
        ECS_BIT_COND(q->flags, EcsQueryIsCacheable, 
            cacheable_terms == term_count);
    }

    return 0;
}

static
int flecs_query_query_populate_terms(
    ecs_world_t *world,
    ecs_stage_t *stage,
    ecs_query_t *q,
    const ecs_query_desc_t *desc)
{
    /* Count number of initialized terms in desc->terms */
    int32_t i, term_count = 0;
    for (i = 0; i < FLECS_TERM_COUNT_MAX; i ++) {
        if (!ecs_term_is_initialized(&desc->terms[i])) {
            break;
        }
        term_count ++;
    }

    /* Copy terms from array to filter */
    if (term_count) {
        ecs_os_memcpy_n(&q->terms, desc->terms, ecs_term_t, term_count);
    }

    /* Parse query expression if set */
    const char *expr = desc->expr;
    if (expr && expr[0]) {
#ifdef FLECS_PARSER
        ecs_entity_t entity = desc->entity;
        const char *filter_name = entity ? ecs_get_name(world, entity) : NULL;
        const char *ptr = desc->expr;
        ecs_oper_kind_t extra_oper = 0;
        ecs_term_ref_t extra_args[FLECS_TERM_ARG_COUNT_MAX];
        ecs_os_memset_n(extra_args, 0, ecs_term_ref_t, 
            FLECS_TERM_ARG_COUNT_MAX);

        do {
            if (term_count == FLECS_TERM_COUNT_MAX) {
                ecs_err("max number of terms (%d) reached, increase "
                    "FLECS_TERM_COUNT_MAX to support more",
                    FLECS_TERM_COUNT_MAX);
                goto error;
            }

            /* Parse next term */
            ecs_term_t *term = &q->terms[term_count];
            ptr = ecs_parse_term(world, stage, filter_name, expr, ptr, 
                term, &extra_oper, extra_args, true);
            if (!ptr) {
                /* Parser error */
                goto error;
            }

            if (!ecs_term_is_initialized(term)) {
                /* Last term parsed */
                break;
            }

            term_count ++;

            /* Unpack terms with more than two args into multiple terms so that:
             *   Rel(X, Y, Z)
             * becomes:
             *   Rel(X, Y), Rel(Y, Z) */
            int32_t arg = 0;
            while (ecs_term_ref_is_set(&extra_args[arg ++])) {
                ecs_assert(arg <= FLECS_TERM_ARG_COUNT_MAX, 
                    ECS_INTERNAL_ERROR, NULL);

                if (term_count == FLECS_TERM_COUNT_MAX) {
                    ecs_err("max number of terms (%d) reached, increase "
                        "FLECS_TERM_COUNT_MAX to support more",
                        FLECS_TERM_COUNT_MAX);
                    goto error;
                }

                term = &q->terms[term_count ++];
                *term = term[-1];

                if (extra_oper == EcsAnd) {
                    term->src = term[-1].second;
                    term->second = extra_args[arg - 1];
                } else if (extra_oper == EcsOr) {
                    term->src = term[-1].src;
                    term->second = extra_args[arg - 1];
                    term[-1].oper = EcsOr;
                }

                if (term->first.name != NULL) {
                    term->first.name = term->first.name;
                }
                if (term->src.name != NULL) {
                    term->src.name = term->src.name;
                }
            }

            if (arg) {
                ecs_os_memset_n(extra_args, 0, ecs_term_ref_t, 
                    FLECS_TERM_ARG_COUNT_MAX);
            }
        } while (ptr[0] && ptr[0] != '\n');
#else
        (void)expr;
        ecs_abort(ECS_UNSUPPORTED, "parser addon is not available");
#endif
    }

    q->term_count = term_count;

    return 0;
error:  
    return -1;
}

int flecs_query_finalize_query(
    ecs_world_t *world,
    ecs_query_t *q,
    const ecs_query_desc_t *desc)    
{
    ecs_check(world != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(desc != NULL, ECS_INVALID_PARAMETER, NULL);
    ecs_check(desc->_canary == 0, ECS_INVALID_PARAMETER, NULL);
    ecs_stage_t *stage = flecs_stage_from_world(&world);

    q->flags |= desc->flags;

    /* Populate term array from desc terms & DSL expression */
    if (flecs_query_query_populate_terms(world, stage, q, desc)) {
        goto error;
    }

    /* Ensure all fields are consistent and properly filled out */
    if (flecs_query_query_finalize_terms(world, q)) {
        goto error;
    }

    return 0;
error:
    return -1;
}
