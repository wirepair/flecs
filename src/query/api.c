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
void flecs_query_fini(
    ecs_query_impl_t *impl)
{
    if (impl->vars != &impl->vars_cache.var) {
        ecs_os_free(impl->vars);
    }

    ecs_os_free(impl->ops);
    ecs_os_free(impl->src_vars);
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
        impl->tokens_len = len;
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
    if (flecs_query_finalize_query(world, &result->pub, &desc)) {
        goto error;
    }

    /* Compile filter to operations */
    if (flecs_query_compile(world, stage, result)) {
        goto error;
    }

    /* Store remaining string tokens in terms (after entity lookups) in single
     * token buffer which simplifies memory management & reduces allocations. */
    flecs_query_populate_tokens(result);

    ecs_entity_t entity = const_desc->entity;
    result->dtor = (ecs_poly_dtor_t)flecs_query_fini;
    result->iterable.init = flecs_query_iter_mixin_init;
    result->pub.entity = entity;
    result->pub.world = world;
    result->pub.stage = stage;

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
