 /**
 * @file addons/rules/api.c
 * @brief User facing API for rules.
 */

#include "rules.h"
#include <ctype.h>

#ifdef FLECS_RULES

static ecs_mixins_t ecs_rule_t_mixins = {
    .type_name = "ecs_rule_t",
    .elems = {
        [EcsMixinWorld] = offsetof(ecs_rule_t, filter.world),
        [EcsMixinEntity] = offsetof(ecs_rule_t, filter.entity),
        [EcsMixinIterable] = offsetof(ecs_rule_t, iterable),
        [EcsMixinDtor] = offsetof(ecs_rule_t, dtor)
    }
};

int32_t ecs_rule_var_count(
    const ecs_filter_t *q)
{
    ecs_poly_assert(q, ecs_rule_t);

    return flecs_rule(q)->var_pub_count;
}

int32_t ecs_rule_find_var(
    const ecs_filter_t *q,
    const char *name)
{
    ecs_poly_assert(q, ecs_rule_t);

    ecs_rule_t *impl = flecs_rule(q);
    ecs_var_id_t var_id = flecs_rule_find_var_id(impl, name, EcsVarEntity);
    if (var_id == EcsVarNone) {
        if (impl->filter.flags & EcsFilterMatchThis) {
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

const char* ecs_rule_var_name(
    const ecs_filter_t *q,
    int32_t var_id)
{
    ecs_poly_assert(q, ecs_rule_t);

    if (var_id) {
        return flecs_rule(q)->vars[var_id].name;
    } else {
        return EcsThisName;
    }
}

bool ecs_rule_var_is_entity(
    const ecs_filter_t *q,
    int32_t var_id)
{
    ecs_poly_assert(q, ecs_rule_t);

    return flecs_rule(q)->vars[var_id].kind == EcsVarEntity;
}

/* Implementation for iterable mixin */
static
void flecs_rule_iter_mixin_init(
    const ecs_world_t *world,
    const ecs_poly_t *poly,
    ecs_iter_t *iter,
    ecs_term_t *filter)
{
    ecs_poly_assert(poly, ecs_rule_t);

    if (filter) {
        iter[1] = ecs_rule_iter(world, ECS_CONST_CAST(ecs_filter_t*, poly));
        iter[0] = ecs_term_chain_iter(&iter[1], filter);
    } else {
        iter[0] = ecs_rule_iter(world, ECS_CONST_CAST(ecs_filter_t*, poly));
    }
}

static
void flecs_rule_fini(
    ecs_rule_t *impl)
{
    if (impl->vars != &impl->vars_cache.var) {
        ecs_os_free(impl->vars);
    }

    ecs_os_free(impl->ops);
    ecs_os_free(impl->src_vars);
    flecs_name_index_fini(&impl->tvar_index);
    flecs_name_index_fini(&impl->evar_index);
    ecs_filter_fini(&impl->filter);

    ecs_poly_free(impl, ecs_rule_t);
}

void ecs_rule_fini(
    ecs_filter_t *q)
{
    ecs_poly_assert(q, ecs_rule_t);

    ecs_rule_t *impl = flecs_rule(q);
    if (impl->filter.entity) {
        /* If filter is associated with entity, use poly dtor path */
        ecs_delete(impl->filter.world, impl->filter.entity);
    } else {
        flecs_rule_fini(impl);
    }
}

ecs_filter_t* ecs_rule_init(
    ecs_world_t *world, 
    const ecs_filter_desc_t *const_desc)
{
    ecs_rule_t *result = ecs_poly_new(ecs_rule_t);
    ecs_stage_t *stage = flecs_stage_from_world(&world);

    /* Initialize the query */
    ecs_filter_desc_t desc = *const_desc;
    desc.storage = &result->filter; /* Use storage of rule */
    result->filter = ECS_FILTER_INIT;
    if (ecs_filter_init(world, &desc) == NULL) {
        /* Patch type */
        result->filter.hdr.type = ecs_rule_t_magic;
        goto error;
    }

    /* Patch type TODO remove when merged with filters */
    result->filter.hdr.type = ecs_rule_t_magic;
    result->filter.hdr.mixins = &ecs_rule_t_mixins;

    result->iterable.init = flecs_rule_iter_mixin_init;

    /* Compile filter to operations */
    if (flecs_rule_compile(world, stage, result)) {
        goto error;
    }

    ecs_entity_t entity = const_desc->entity;
    result->dtor = (ecs_poly_dtor_t)flecs_rule_fini;

    if (entity) {
        EcsPoly *poly = ecs_poly_bind(world, entity, ecs_rule_t);
        poly->poly = result;
        ecs_poly_modified(world, entity, ecs_rule_t);
    }

    return &result->filter;
error:
    ecs_rule_fini(&result->filter);
    return NULL;
}

#endif
