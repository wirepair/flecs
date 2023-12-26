#include <query.h>
#include <stdio.h>

static ecs_query_cache_kind_t cache_kind = EcsQueryCacheDefault;

void Basic_setup(void) {
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

void Basic_1_fact_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_tag_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_component_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent), RelB(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent), Velocity(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_tag_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, TgtA), RelA(ent, TgtB)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_component_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent, TgtA), Position(ent, TgtB)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtB, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(ecs_id(Position), TgtB), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent1), RelB(ent2)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent1, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent2, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent1), Velocity(ent2)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent1, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent2, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_tag_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent1, TgtA), RelA(ent2, TgtB)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_component_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(ent1, TgtA), Position(ent2, TgtB)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, ent1, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, ent2, Position, TgtB, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(ecs_id(Position), TgtB), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);
    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_pair_any_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_pair_any_rel(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_fact_w_pair_any_rel_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");
    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent), _(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);
    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_pair_any_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, _), RelA(ent, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_pair_any_rel(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent, TgtA), _(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_same_src_w_pair_any_rel_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");
    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent, _), _(ent, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent1), _(ent2)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent1, RelA);
    ecs_add(world, ent1, RelB);
    ecs_add(world, ent2, RelA);
    ecs_add(world, ent2, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_pair_any_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent1, _), RelA(ent2, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelA, TgtB);
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_pair_any_rel(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent1, _), RelA(ent2, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelA, TgtB);
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_facts_other_src_w_pair_any_rel_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelB, TgtA);
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelB, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "_(ent1, _), _(ent2, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_tag_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_component_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, e1, Position, TgtA, {10, 20});
    ecs_set_pair(world, e2, Position, TgtA, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_tag_2_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_component_2_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 10); test_int(p[0].y, 20);
        }

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 30); test_int(p[0].y, 40);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_tag_pair_2_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_this_src_w_component_pair_2_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set_pair(world, e1, Position, TgtA, {10, 20});
    ecs_set_pair(world, e2, Position, TgtA, {30, 40});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 10); test_int(p[0].y, 20);
        }

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 30); test_int(p[0].y, 40);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_this_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this), RelB($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e1, RelB);
    ecs_add(world, e2, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_this_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this), Velocity($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    ecs_set(world, e1, Velocity, {1, 2});
    ecs_set(world, e2, Velocity, {3, 4});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        test_int(v[1].x, 3); test_int(v[1].y, 4);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_this_src_ent_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this), RelB(e3)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e3, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_this_src_ent_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this), Velocity(e3)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});
    ecs_set(world, e3, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e3, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_ent_src_this_src_w_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelB(e3), RelA($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelB, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(e3, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_ent_src_this_src_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Velocity(e3), Position($this)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});
    ecs_set(world, e3, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 1));
        test_uint(ecs_id(Position), ecs_field_id(&it, 2));
        test_uint(e3, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Velocity *v = ecs_field(&it, Velocity, 1);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        const Position *p = ecs_field(&it, Position, 2);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_recycled_tag(void) {
    ecs_world_t *world = ecs_mini();

    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, RelA);
    test_assert((uint32_t)RelA != RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_recycled_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_delete(world, ecs_new_id(world));
    ecs_entity_t ent = ecs_new_entity(world, "ent");
    test_assert((uint32_t)ent != ent);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_recycled_pair_rel(void) {
    ecs_world_t *world = ecs_mini();

    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, RelA);
    test_assert((uint32_t)RelA != RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_recycled_pair_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, TgtA);
    test_assert((uint32_t)TgtA != TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this), *($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    
    ecs_add(world, e2, RelA);
    ecs_add(world, e2, RelB);
    ecs_add(world, e2, RelC);

    ecs_add(world, e3, RelA);
    ecs_add(world, e3, RelB);
    ecs_add(world, e3, RelC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelC, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_rel_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), *($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelB, TgtB);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e2, RelC, TgtA);
    ecs_add_pair(world, e2, RelC, TgtB);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);
    ecs_add_pair(world, e3, RelC, TgtA);
    ecs_add_pair(world, e3, RelC, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelC, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_tgt_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), RelA($this, *)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelA, TgtC);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelA, TgtC);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtC), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_rel_tgt_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), *($this, *)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "_",
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, Tgt);

    ecs_iter_t it = ecs_query_iter(world, r);
    ecs_entity_t prev = 0;
    int32_t count = 0, e1_matched = 0;
    while (ecs_query_next(&it)) {
        test_assert(it.count > 0);
        test_assert(!prev || prev != it.entities[0]);
        prev = it.entities[0];
        if (it.entities[0] == e1) {
            e1_matched ++;
        }
        count ++;
    }

    test_assert(count > 0);
    test_int(e1_matched, 1);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_not_any(void) {
    ecs_world_t *world = ecs_mini();

    ecs_query_t *r = ecs_query(world, {
        .expr = "!_",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_any_written(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this), _($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    
    ecs_add(world, e2, RelA);
    ecs_add(world, e2, RelB);
    ecs_add(world, e2, RelC);

    ecs_add(world, e3, RelA);
    ecs_add(world, e3, RelB);
    ecs_add(world, e3, RelC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_rel_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), _($this, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelB, TgtB);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e2, RelC, TgtA);
    ecs_add_pair(world, e2, RelC, TgtB);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);
    ecs_add_pair(world, e3, RelC, TgtA);
    ecs_add_pair(world, e3, RelC, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_tgt_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), RelA($this, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelA, TgtC);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelA, TgtC);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_src_w_pair_rel_tgt_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA($this, TgtA), _($this, _)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_ent_src_w_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "*(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    ecs_add(world, e1, RelC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelB, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelC, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_ent_src_w_pair_rel_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "*(ent, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelC, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelC, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_ent_src_w_pair_tgt_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent, *)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelA, TgtC);
    ecs_add_pair(world, e1, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtC), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_ent_src_w_pair_rel_tgt_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");
    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "*(ent, *)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(EcsIdentifier), EcsName), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(*)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_new(world, RelA);
    ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src_w_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(*, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_new_w_pair(world, RelA, TgtA);
    ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_wildcard_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(*), RelB(*)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_entity_t e2 = ecs_new(world, RelA);
    ecs_entity_t e3 = ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelB);
    ecs_add(world, e2, RelB);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_wildcard_src_w_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(*, TgtA), RelB(*, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_entity_t e2 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_entity_t e3 = ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_rule_w_iter_next(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_iter_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_iter_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_iter_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src_w_pair_tgt_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(*, $x)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int x_var = ecs_query_find_var(r, "x");
    test_assert(x_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, Rel, TgtA);
    ecs_new_w_pair(world, Rel, TgtB);
    ecs_new_w_pair(world, Rel, TgtC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtA), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtA, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtB), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtB, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtC), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtC, ecs_iter_get_var(&it, x_var));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src_w_pair_rel_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "$x(*, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int x_var = ecs_query_find_var(r, "x");
    test_assert(x_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, RelA, Tgt);
    ecs_new_w_pair(world, RelB, Tgt);
    ecs_new_w_pair(world, RelC, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelA, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelB, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelC, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelC, ecs_iter_get_var(&it, x_var));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src_w_pair_tgt_this(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(*, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "This");
    test_assert(this_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, Rel, TgtA);
    ecs_new_w_pair(world, Rel, TgtB);
    ecs_new_w_pair(world, Rel, TgtC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtA), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtA, ecs_iter_get_var(&it, this_var));
        test_uint(TgtA, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtB), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtB, ecs_iter_get_var(&it, this_var));
        test_uint(TgtB, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtC), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(TgtC, ecs_iter_get_var(&it, this_var));
        test_uint(TgtC, it.entities[0]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_wildcard_src_w_pair_rel_this(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "$this(*, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "This");
    test_assert(this_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, RelA, Tgt);
    ecs_new_w_pair(world, RelB, Tgt);
    ecs_new_w_pair(world, RelC, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelA, ecs_iter_get_var(&it, this_var));
        test_uint(RelA, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelB, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelB, ecs_iter_get_var(&it, this_var));
        test_uint(RelB, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelC, Tgt), ecs_field_id(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(RelC, ecs_iter_get_var(&it, this_var));
        test_uint(RelC, it.entities[0]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(_)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_new(world, RelA);
    ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src_w_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(_, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_new_w_pair(world, RelA, TgtA);
    ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_any_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(_), RelB(_)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_entity_t e2 = ecs_new(world, RelA);
    ecs_entity_t e3 = ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add(world, e1, RelB);
    ecs_add(world, e2, RelB);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_any_src_w_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "RelA(_, TgtA), RelB(_, TgtA)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_entity_t e2 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_entity_t e3 = ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src_w_pair_tgt_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(_, $x)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int x_var = ecs_query_find_var(r, "x");
    test_assert(x_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, Rel, TgtA);
    ecs_new_w_pair(world, Rel, TgtB);
    ecs_new_w_pair(world, Rel, TgtC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtC), ecs_field_id(&it, 1));
        test_uint(TgtC, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtB), ecs_field_id(&it, 1));
        test_uint(TgtB, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Rel, TgtA), ecs_field_id(&it, 1));
        test_uint(TgtA, ecs_iter_get_var(&it, x_var));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src_w_pair_rel_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "$x(_, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int x_var = ecs_query_find_var(r, "x");
    test_assert(x_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, RelA, Tgt);
    ecs_new_w_pair(world, RelB, Tgt);
    ecs_new_w_pair(world, RelC, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelC, Tgt), ecs_field_id(&it, 1));
        test_uint(RelC, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, Tgt), ecs_field_id(&it, 1));
        test_uint(RelB, ecs_iter_get_var(&it, x_var));

        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, Tgt), ecs_field_id(&it, 1));
        test_uint(RelA, ecs_iter_get_var(&it, x_var));

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src_w_pair_tgt_this(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(_, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "This");
    test_assert(this_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, Rel, TgtA);
    ecs_new_w_pair(world, Rel, TgtB);
    ecs_new_w_pair(world, Rel, TgtC);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtC), ecs_field_id(&it, 1));
        test_uint(TgtC, ecs_iter_get_var(&it, this_var));
        test_uint(TgtC, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtB), ecs_field_id(&it, 1));
        test_uint(TgtB, ecs_iter_get_var(&it, this_var));
        test_uint(TgtB, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(Rel, TgtA), ecs_field_id(&it, 1));
        test_uint(TgtA, ecs_iter_get_var(&it, this_var));
        test_uint(TgtA, it.entities[0]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_1_any_src_w_pair_rel_this(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "$this(_, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "This");
    test_assert(this_var != -1);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_new_w_pair(world, RelA, Tgt);
    ecs_new_w_pair(world, RelB, Tgt);
    ecs_new_w_pair(world, RelC, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelC, Tgt), ecs_field_id(&it, 1));
        test_uint(RelC, ecs_iter_get_var(&it, this_var));
        test_uint(RelC, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelB, Tgt), ecs_field_id(&it, 1));
        test_uint(RelB, ecs_iter_get_var(&it, this_var));
        test_uint(RelB, it.entities[0]);

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, Tgt), ecs_field_id(&it, 1));
        test_uint(RelA, ecs_iter_get_var(&it, this_var));
        test_uint(RelA, it.entities[0]);

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_empty_rule(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_iter_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_invalid_rule(void) {
    ecs_log_set_level(-4);

    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, RelA);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo",
        .cache_kind = cache_kind
    });

    test_assert(r == NULL);

    ecs_fini(world);
}

void Basic_not_instanced_table_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(3, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_uint(e3, it.entities[2]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 20); test_int(p[1].y, 30);
        test_int(p[2].x, 30); test_int(p[2].y, 40);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_not_instanced_entity_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e1 = ecs_new_entity(world, "e1");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(e1)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_set(world, e1, Position, {10, 20});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 10);
        test_int(p->y, 20);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_not_instanced_mixed_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e0 = ecs_new_entity(world, "e0");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this), Velocity(e0)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_set(world, e0, Velocity, {1, 2});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 10);
        test_int(p->y, 20);

        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    {
        test_bool(true, ecs_iter_next(&it));
        test_int(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e2, it.entities[0]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 20);
        test_int(p->y, 30);

        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    {
        test_bool(true, ecs_iter_next(&it));
        test_int(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e0, ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e3, it.entities[0]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 30);
        test_int(p->y, 40);

        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_instanced_table_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(3, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_uint(e3, it.entities[2]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 20); test_int(p[1].y, 30);
        test_int(p[2].x, 30); test_int(p[2].y, 40);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_instanced_entity_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e1 = ecs_new_entity(world, "e1");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(e1)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_set(world, e1, Position, {10, 20});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 10);
        test_int(p->y, 20);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_instanced_mixed_src(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e0 = ecs_new_entity(world, "e0");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position($this), Velocity(e0)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_set(world, e0, Velocity, {1, 2});

    ecs_iter_t it = ecs_query_iter(world, r);
    {
        test_bool(true, ecs_iter_next(&it));
        test_int(3, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_uint(e3, it.entities[2]);

        const Position *p = ecs_field(&it, Position, 1);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 20); test_int(p[1].y, 30);
        test_int(p[2].x, 30); test_int(p[2].y, 40);

        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_bool(false, ecs_iter_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_in_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[in] Position(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_readonly(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_out_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[out] Position(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_field_is_readonly(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_inout_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[inout] Position(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_field_is_readonly(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_nodata_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[none] Position(ent)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_field_is_readonly(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p == NULL);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_find_this_lowercase(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "this");
    test_assert(this_var != -1);
    test_assert(this_var == 0);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_find_this_uppercase(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel($this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "This");
    test_assert(this_var != -1);
    test_assert(this_var == 0);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_find_this_tgt_lowercase(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(*, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "this");
    test_assert(this_var != -1);
    test_assert(this_var != 0);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_find_this_tgt_uppercase(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(*, $This)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int this_var = ecs_query_find_var(r, "this");
    test_assert(this_var != -1);
    test_assert(this_var != 0);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_get_filter(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    const ecs_query_t *f = r;
    test_assert(f != NULL);
    test_int(f->term_count, 1);
    test_uint(f->terms[0].id, Rel);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo()",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Foo), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "*()",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_2_terms(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(), Bar()",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Foo), ecs_field_id(&it, 1));
        test_uint(ecs_id(Bar), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(0, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Foo, Tgt), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_pair_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "*(0, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, Tgt), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_2_terms_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(0, Tgt), Bar(0, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(Foo, Tgt), ecs_field_id(&it, 1));
        test_uint(ecs_pair(Bar, Tgt), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_2_terms_mixed(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, Bar()",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add(world, e, Foo);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(Bar, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_2_terms_mixed_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "(Foo, Tgt), Bar(0, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add_pair(world, e, Foo, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e, it.entities[0]);
        test_uint(ecs_pair(Foo, Tgt), ecs_field_id(&it, 1));
        test_uint(ecs_pair(Bar, Tgt), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_iter_empty_source_2_terms_mixed_pair_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "(Foo, Tgt), *(0, Tgt)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add_pair(world, e, Foo, Tgt);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e, it.entities[0]);
        test_uint(ecs_pair(Foo, Tgt), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, Tgt), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_this_var_w_empty_entity(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);

    ecs_entity_t t = ecs_new_id(world);
    ecs_entity_t e = ecs_new_w_pair(world, Rel, t);

    ecs_query_t *r = ecs_query(world, { 
        .expr = "Rel($x, $this)",
        .cache_kind = cache_kind
    });
    test_assert(r != NULL);

    int x_var = ecs_query_find_var(r, "x");
    test_assert(x_var != -1);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_uint(1, it.count);
    test_uint(t, it.entities[0]);
    test_uint(ecs_pair(Rel, t), ecs_field_id(&it, 1));
    test_uint(e, ecs_field_src(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_uint(e, ecs_iter_get_var(&it, x_var));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_match_disabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ?Disabled",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_2);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_prefab(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ?Prefab",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_3);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_disabled_prefab(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);
    ecs_entity_t e_4 = ecs_new(world, TagA);
    ecs_add_id(world, e_4, EcsPrefab);
    ecs_add_id(world, e_4, EcsDisabled);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ?Disabled",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_3 = ecs_query(world, {
        .expr = "TagA, ?Prefab",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_4 = ecs_query(world, {
        .expr = "TagA, ?Prefab, ?Disabled",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);
    test_assert(r_3 != NULL);
    test_assert(r_4 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);
    test_bool(r_3->flags & EcsQueryMatchDisabled, false);
    test_bool(r_4->flags & EcsQueryMatchDisabled, true);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, false);
    test_bool(r_3->flags & EcsQueryMatchPrefab, true);
    test_bool(r_4->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_assert(!ecs_query_next(&it));

    {
        it = ecs_query_iter(world, r_2);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_3);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_4);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_4);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(!ecs_query_next(&it));
    }

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);
    ecs_query_fini(r_3);
    ecs_query_fini(r_4);

    ecs_fini(world);
}

void Basic_match_disabled_this_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_new_w_pair(world, EcsChildOf, e_1);
    ecs_new_w_pair(world, EcsChildOf, e_2);
    ecs_new_w_pair(world, EcsChildOf, e_3);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this), ?Disabled",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_2);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_prefab_this_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_new_w_pair(world, EcsChildOf, e_1);
    ecs_new_w_pair(world, EcsChildOf, e_2);
    ecs_new_w_pair(world, EcsChildOf, e_3);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this), ?Prefab",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_3);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_disabled_prefab_this_tgt(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);
    ecs_entity_t e_4 = ecs_new(world, TagA);
    ecs_add_id(world, e_4, EcsPrefab);
    ecs_add_id(world, e_4, EcsDisabled);

    ecs_new_w_pair(world, EcsChildOf, e_1);
    ecs_new_w_pair(world, EcsChildOf, e_2);
    ecs_new_w_pair(world, EcsChildOf, e_3);
    ecs_new_w_pair(world, EcsChildOf, e_4);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this), ?Disabled",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_3 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this), ?Prefab",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_4 = ecs_query(world, {
        .expr = "TagA, ChildOf($child, $this), ?Prefab, ?Disabled",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);
    test_assert(r_3 != NULL);
    test_assert(r_4 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);
    test_bool(r_3->flags & EcsQueryMatchDisabled, false);
    test_bool(r_4->flags & EcsQueryMatchDisabled, true);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, false);
    test_bool(r_3->flags & EcsQueryMatchPrefab, true);
    test_bool(r_4->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_assert(!ecs_query_next(&it));

    {
        it = ecs_query_iter(world, r_2);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_3);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_4);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_4);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(!ecs_query_next(&it));
    }

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);
    ecs_query_fini(r_3);
    ecs_query_fini(r_4);

    ecs_fini(world);
}

void Basic_match_self_disabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA(self)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA(self), ?Disabled(self)",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_2);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_self_prefab(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA(self)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA(self), ?Prefab(self)",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_assert(!ecs_query_next(&it));

    it = ecs_query_iter(world, r_2);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_3);
    test_int(ecs_field_id(&it, 1), TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);

    ecs_fini(world);
}

void Basic_match_self_disabled_prefab(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, EcsDisabled);
    ecs_entity_t e_3 = ecs_new(world, TagA);
    ecs_add_id(world, e_3, EcsPrefab);
    ecs_entity_t e_4 = ecs_new(world, TagA);
    ecs_add_id(world, e_4, EcsPrefab);
    ecs_add_id(world, e_4, EcsDisabled);

    ecs_query_t *r_1 = ecs_query(world, {
        .expr = "TagA(self)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_2 = ecs_query(world, {
        .expr = "TagA(self), ?Disabled(self)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_3 = ecs_query(world, {
        .expr = "TagA(self), ?Prefab(self)",
        .cache_kind = cache_kind
    });

    ecs_query_t *r_4 = ecs_query(world, {
        .expr = "TagA(self), ?Prefab(self), ?Disabled(self)",
        .cache_kind = cache_kind
    });

    test_assert(r_1 != NULL);
    test_assert(r_2 != NULL);
    test_assert(r_3 != NULL);
    test_assert(r_4 != NULL);

    test_bool(r_1->flags & EcsQueryMatchDisabled, false);
    test_bool(r_2->flags & EcsQueryMatchDisabled, true);
    test_bool(r_3->flags & EcsQueryMatchDisabled, false);
    test_bool(r_4->flags & EcsQueryMatchDisabled, true);

    test_bool(r_1->flags & EcsQueryMatchPrefab, false);
    test_bool(r_2->flags & EcsQueryMatchPrefab, false);
    test_bool(r_3->flags & EcsQueryMatchPrefab, true);
    test_bool(r_4->flags & EcsQueryMatchPrefab, true);

    ecs_iter_t it = ecs_query_iter(world, r_1);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_assert(!ecs_query_next(&it));

    {
        it = ecs_query_iter(world, r_2);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_3);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_assert(!ecs_query_next(&it));
    }

    {
        it = ecs_query_iter(world, r_4);
        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_1);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_2);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_3);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(ecs_query_next(&it));
        test_int(it.count, 1);
        test_int(it.entities[0], e_4);
        test_int(ecs_field_id(&it, 1), TagA);
        test_bool(true, ecs_field_is_set(&it, 1));

        test_assert(!ecs_query_next(&it));
    }

    ecs_query_fini(r_1);
    ecs_query_fini(r_2);
    ecs_query_fini(r_3);
    ecs_query_fini(r_4);

    ecs_fini(world);
}

void Basic_inout_none_first_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *r = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), .inout = EcsInOutNone },
            { .id = ecs_id(Velocity) }
        },
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e1, Velocity, {1, 2});

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    {
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p == NULL);
    }
    {
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_inout_none_second_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *r = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position) },
            { .id = ecs_id(Velocity), .inout = EcsInOutNone }
        },
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e1, Velocity, {1, 2});

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    {
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
    }
    {
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v == NULL);
    }

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_no_data_rule(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *r = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position) },
            { .id = ecs_id(Velocity) }
        },
        .flags = EcsQueryNoData,
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e1, Velocity, {1, 2});

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    {
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p == NULL);
    }
    {
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v == NULL);
    }

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_frame_offset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_query_t *f = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), }
        },
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_entity_t e4 = ecs_new(world, Position);
    ecs_entity_t e5 = ecs_new(world, Position);

    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagB);
    ecs_add(world, e5, TagC);

    ecs_iter_t it = ecs_query_iter(world, f);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 0);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e1);
    test_assert(it.entities[1] == e2);
    test_assert(it.ids[0] == ecs_id(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 2);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e3);
    test_assert(it.entities[1] == e4);
    test_assert(it.ids[0] == ecs_id(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.frame_offset, 4);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e5);
    test_assert(it.ids[0] == ecs_id(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_frame_offset_no_data(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_query_t *f = ecs_query(world, {
        .terms = {
            { .id = TagA, }
        },
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_entity_t e3 = ecs_new(world, TagA);
    ecs_entity_t e4 = ecs_new(world, TagA);
    ecs_entity_t e5 = ecs_new(world, TagA);

    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagB);
    ecs_add(world, e5, TagC);

    ecs_iter_t it = ecs_query_iter(world, f);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 0);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e1);
    test_assert(it.entities[1] == e2);
    test_assert(it.ids[0] == TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 2);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e3);
    test_assert(it.entities[1] == e4);
    test_assert(it.ids[0] == TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.frame_offset, 4);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e5);
    test_assert(it.ids[0] == TagA);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_entity_t e4 = ecs_new(world, Position);

    ecs_add(world, e2, TagA);
    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagC);

    ecs_table_t *t1 = ecs_get_table(world, e1);
    ecs_table_t *t2 = ecs_get_table(world, e2);
    ecs_table_t *t3 = ecs_get_table(world, e3);
    ecs_table_t *t4 = ecs_get_table(world, e4);

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ecs_query_t *f = ecs_query(world, {
        .terms = {{ ecs_id(Position) }},
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t1);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t2);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t3);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t4);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables_no_data(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add(world, e2, TagA);
    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagC);

    ecs_table_t *t1 = ecs_get_table(world, e1);
    ecs_table_t *t2 = ecs_get_table(world, e2);
    ecs_table_t *t3 = ecs_get_table(world, e3);
    ecs_table_t *t4 = ecs_get_table(world, e4);

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ecs_query_t *f = ecs_query(world, {
        .terms = {{ Foo }},
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    
    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t1);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t2);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t3);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t4);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables_w_not(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add(world, e2, TagA);
    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagC);

    ecs_table_t *t1 = ecs_get_table(world, e1);
    ecs_get_table(world, e2);
    ecs_table_t *t3 = ecs_get_table(world, e3);
    ecs_table_t *t4 = ecs_get_table(world, e4);

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ecs_query_t *f = ecs_query(world, {
        .terms = {{ Foo }, { TagA, .oper = EcsNot }},
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    
    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t1);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t3);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t4);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables_w_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);
    ECS_TAG(world, TgtD);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, TgtA);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, TgtB);
    ecs_entity_t e3 = ecs_new_w_pair(world, Rel, TgtC);
    ecs_entity_t e4 = ecs_new_w_pair(world, Rel, TgtD);

    ecs_table_t *t1 = ecs_get_table(world, e1);
    ecs_table_t *t2 = ecs_get_table(world, e2);
    ecs_table_t *t3 = ecs_get_table(world, e3);
    ecs_table_t *t4 = ecs_get_table(world, e4);

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ecs_query_t *f = ecs_query(world, {
        .terms = {{ ecs_pair(Rel, EcsWildcard) }},
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t1);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, TgtA));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t2);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, TgtB));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t3);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, TgtC));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t4);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, TgtD));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables_w_no_empty_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *f = ecs_query(world, {
        .terms = {
            { Foo }
        },
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_add(world, e2, Bar);

    ecs_iter_t it = ecs_query_iter(world, f);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_match_empty_tables_trivial(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);
    ecs_entity_t e4 = ecs_new(world, Position);

    ecs_add(world, e2, TagA);
    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagC);

    ecs_table_t *t1 = ecs_get_table(world, e1);
    ecs_table_t *t2 = ecs_get_table(world, e2);
    ecs_table_t *t3 = ecs_get_table(world, e3);
    ecs_table_t *t4 = ecs_get_table(world, e4);

    ecs_delete(world, e1);
    ecs_delete(world, e2);

    ecs_query_t *f = ecs_query(world, {
        .terms = {{ ecs_id(Position), .src.id = EcsSelf }},
        .flags = EcsQueryMatchEmptyTables,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    
    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t1);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t2);
    test_int(it.count, 0);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t3);
    test_int(it.count, 1);
    test_int(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), true);
    test_assert(it.table == t4);
    test_int(it.count, 1);
    test_int(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), ecs_id(Position));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool( ecs_query_next(&it), false);

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_oneof_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Parent);
    ECS_ENTITY(world, Rel, (OneOf, Parent));
    ECS_ENTITY(world, ObjA, (ChildOf, Parent));
    ECS_ENTITY(world, ObjB, (ChildOf, Parent));

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    test_assert( ecs_has_pair(world, e1, Rel, ObjA));
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);
    test_assert( ecs_has_pair(world, e2, Rel, ObjB));

    ecs_query_t *f = ecs_query(world, {
        .terms = {{
            .id = ecs_pair(Rel, EcsWildcard)
        }},
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjA), ecs_field_id(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjB), ecs_field_id(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_oneof_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Parent);
    ECS_ENTITY(world, Rel, (OneOf, Parent));
    ECS_ENTITY(world, ObjA, (ChildOf, Parent));
    ECS_ENTITY(world, ObjB, (ChildOf, Parent));

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    test_assert( ecs_has_pair(world, e1, Rel, ObjA));
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);
    test_assert( ecs_has_pair(world, e2, Rel, ObjB));

    ecs_query_t *f = ecs_query(world, {
        .terms = {{
            .id = ecs_pair(Rel, EcsAny)
        }},
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, EcsWildcard), ecs_field_id(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, EcsWildcard), ecs_field_id(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_instanced_w_singleton(void) {
    ecs_world_t *world = ecs_mini();
    
    ECS_TAG(world, Tag);

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_singleton_set(world, Velocity, {1, 2});

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e4 = ecs_set(world, 0, Position, {40, 50});
    ecs_entity_t e5 = ecs_set(world, 0, Position, {50, 60});

    ecs_add(world, e4, Tag);
    ecs_add(world, e5, Tag);

    ecs_query_t *f = ecs_query(world, {
        .expr = "Position, Velocity($)",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_int(it.count, 3);
        test_int(it.entities[0], e1);
        test_int(it.entities[1], e2);
        test_int(it.entities[2], e3);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_int(p[0].x, 10);
        test_int(p[0].y, 20);
        test_int(p[1].x, 20);
        test_int(p[1].y, 30);
        test_int(p[2].x, 30);
        test_int(p[2].y, 40);
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
        test_int(it.count, 2);
        test_int(it.entities[0], e4);
        test_int(it.entities[1], e5);
        test_int(p[0].x, 40);
        test_int(p[0].y, 50);
        test_int(p[1].x, 50);
        test_int(p[1].y, 60);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_instanced_w_base(void) {
    ecs_world_t *world = ecs_mini();
    
    ECS_TAG(world, Tag);

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base_1 = ecs_set(world, 0, Velocity, {1, 2});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {80, 90});

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e4 = ecs_set(world, 0, Position, {40, 50});
    ecs_entity_t e5 = ecs_set(world, 0, Position, {50, 60});
    ecs_add(world, e4, Tag);
    ecs_add(world, e5, Tag);

    ecs_add_pair(world, e1, EcsIsA, base_1);
    ecs_add_pair(world, e2, EcsIsA, base_1);
    ecs_add_pair(world, e3, EcsIsA, base_1);
    ecs_add_pair(world, e4, EcsIsA, base_1);
    ecs_add_pair(world, e5, EcsIsA, base_1);

    ecs_entity_t e6 = ecs_set(world, 0, Position, {60, 70});
    ecs_entity_t e7 = ecs_set(world, 0, Position, {70, 80});
    ecs_set(world, e6, Velocity, {2, 3});
    ecs_set(world, e7, Velocity, {4, 5});

    ecs_entity_t e8 = ecs_set(world, 0, Velocity, {6, 7});
    ecs_entity_t e9 = ecs_set(world, 0, Velocity, {8, 9});
    ecs_add_pair(world, e8, EcsIsA, base_2);
    ecs_add_pair(world, e9, EcsIsA, base_2);

    ecs_query_t *f = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind,
        .flags = EcsQueryIsInstanced
    });

    ecs_iter_t it = ecs_query_iter(world, f);

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), false);
        test_bool(ecs_field_is_self(&it, 2), true);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 2);
        test_int(it.entities[0], e8);
        test_int(it.entities[1], e9);
        test_int(p->x, 80);
        test_int(p->y, 90);
        test_int(v[0].x, 6);
        test_int(v[0].y, 7);
        test_int(v[1].x, 8);
        test_int(v[1].y, 9);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);

        test_int(it.count, 3);
        test_int(it.entities[0], e1);
        test_int(it.entities[1], e2);
        test_int(it.entities[2], e3);
        test_int(p[0].x, 10);
        test_int(p[0].y, 20);
        test_int(p[1].x, 20);
        test_int(p[1].y, 30);
        test_int(p[2].x, 30);
        test_int(p[2].y, 40);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 2);
        test_int(it.entities[0], e4);
        test_int(it.entities[1], e5);
        test_int(p[0].x, 40);
        test_int(p[0].y, 50);
        test_int(p[1].x, 50);
        test_int(p[1].y, 60);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), true);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 2);
        test_int(it.entities[0], e6);
        test_int(p[0].x, 60);
        test_int(p[0].y, 70);
        test_int(v[0].x, 2);
        test_int(v[0].y, 3);

        test_int(it.entities[1], e7);
        test_int(p[1].x, 70);
        test_int(p[1].y, 80);
        test_int(v[1].x, 4);
        test_int(v[1].y, 5);
    }

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_not_instanced_w_singleton(void) {
    ecs_world_t *world = ecs_mini();
    
    ECS_TAG(world, Tag);

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_singleton_set(world, Velocity, {1, 2});

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e4 = ecs_set(world, 0, Position, {40, 50});
    ecs_entity_t e5 = ecs_set(world, 0, Position, {50, 60});

    ecs_add(world, e4, Tag);
    ecs_add(world, e5, Tag);

    ecs_query_t *f = ecs_query(world, {
        .expr = "Position, Velocity($)",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);
    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e1);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_int(p[0].x, 10);
        test_int(p[0].y, 20);
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e2);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_int(p[0].x, 20);
        test_int(p[0].y, 30);
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e3);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_int(p[0].x, 30);
        test_int(p[0].y, 40);
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e4);
        test_int(p[0].x, 40);
        test_int(p[0].y, 50);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e5);
        test_int(p[0].x, 50);
        test_int(p[0].y, 60);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_src(&it, 2));
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));
    }

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_not_instanced_w_base(void) {
    ecs_world_t *world = ecs_mini();
    
    ECS_TAG(world, Tag);

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base_1 = ecs_set(world, 0, Velocity, {1, 2});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {80, 90});

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e4 = ecs_set(world, 0, Position, {40, 50});
    ecs_entity_t e5 = ecs_set(world, 0, Position, {50, 60});
    ecs_add(world, e4, Tag);
    ecs_add(world, e5, Tag);

    ecs_add_pair(world, e1, EcsIsA, base_1);
    ecs_add_pair(world, e2, EcsIsA, base_1);
    ecs_add_pair(world, e3, EcsIsA, base_1);
    ecs_add_pair(world, e4, EcsIsA, base_1);
    ecs_add_pair(world, e5, EcsIsA, base_1);

    ecs_entity_t e6 = ecs_set(world, 0, Position, {60, 70});
    ecs_entity_t e7 = ecs_set(world, 0, Position, {70, 80});
    ecs_set(world, e6, Velocity, {2, 3});
    ecs_set(world, e7, Velocity, {4, 5});

    ecs_entity_t e8 = ecs_set(world, 0, Velocity, {6, 7});
    ecs_entity_t e9 = ecs_set(world, 0, Velocity, {8, 9});
    ecs_add_pair(world, e8, EcsIsA, base_2);
    ecs_add_pair(world, e9, EcsIsA, base_2);

    ecs_query_t *f = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, f);

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), false);
        test_bool(ecs_field_is_self(&it, 2), true);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e8);
        test_int(p->x, 80);
        test_int(p->y, 90);
        test_int(v[0].x, 6);
        test_int(v[0].y, 7);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), false);
        test_bool(ecs_field_is_self(&it, 2), true);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e9);
        test_int(p->x, 80);
        test_int(p->y, 90);
        test_int(v[0].x, 8);
        test_int(v[0].y, 9);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);

        test_int(it.count, 1);
        test_int(it.entities[0], e1);
        test_int(p[0].x, 10);
        test_int(p[0].y, 20);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);

        test_int(it.count, 1);
        test_int(it.entities[0], e2);
        test_int(p[0].x, 20);
        test_int(p[0].y, 30);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);

        test_int(it.count, 1);
        test_int(it.entities[0], e3);
        test_int(p[0].x, 30);
        test_int(p[0].y, 40);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e4);
        test_int(p[0].x, 40);
        test_int(p[0].y, 50);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), false);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e5);
        test_int(p[0].x, 50);
        test_int(p[0].y, 60);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        test_bool(ecs_field_is_self(&it, 1), true);
        test_bool(ecs_field_is_self(&it, 2), true);
        test_bool(true, ecs_field_is_set(&it, 1));
        test_bool(true, ecs_field_is_set(&it, 2));

        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 2);
        test_int(it.entities[0], e6);
        test_int(p[0].x, 60);
        test_int(p[0].y, 70);
        test_int(v[0].x, 2);
        test_int(v[0].y, 3);

        test_int(it.entities[1], e7);
        test_int(p[1].x, 70);
        test_int(p[1].y, 80);
        test_int(v[1].x, 4);
        test_int(v[1].y, 5);
    }

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(f);

    ecs_fini(world);
}

void Basic_unknown_before_known(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($gc, $c), ChildOf($c, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int c_var = ecs_query_find_var(r, "c");
    test_assert(c_var != -1);
    int gc_var = ecs_query_find_var(r, "gc");
    test_assert(gc_var != -1);

    ecs_entity_t p = ecs_new(world, Foo);
    ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, p);
    /* ecs_entity_t c2 = */ ecs_new_w_pair(world, EcsChildOf, p);
    ecs_entity_t gc = ecs_new_w_pair(world, EcsChildOf, c);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 3));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc, ecs_iter_get_var(&it, gc_var));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r);
    
    ecs_fini(world);
}

void Basic_unknown_before_known_after_or(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($gc, $c), Foo($gc) || Bar($gc), ChildOf($c, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int c_var = ecs_query_find_var(r, "c");
    test_assert(c_var != -1);
    int gc_var = ecs_query_find_var(r, "gc");
    test_assert(gc_var != -1);

    ecs_entity_t p = ecs_new(world, Foo);
    ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, p);
    /* ecs_entity_t c2 = */ ecs_new_w_pair(world, EcsChildOf, p);
    ecs_entity_t gc1 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc1, Foo);
    ecs_entity_t gc2 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc2, Bar);
    /* ecs_entity_t gc3 = */ ecs_new_w_pair(world, EcsChildOf, c);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 4));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 4));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc1, ecs_iter_get_var(&it, gc_var));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 4));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 4));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc2, ecs_iter_get_var(&it, gc_var));
    test_assert(!ecs_query_next(&it));
    
    ecs_query_fini(r);
    
    ecs_fini(world);
}

void Basic_unknown_before_known_after_not(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($gc, $c), !Foo($gc), ChildOf($c, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int c_var = ecs_query_find_var(r, "c");
    test_assert(c_var != -1);
    int gc_var = ecs_query_find_var(r, "gc");
    test_assert(gc_var != -1);

    ecs_entity_t p = ecs_new(world, Foo);
    ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, p);
    /* ecs_entity_t c2 = */ ecs_new_w_pair(world, EcsChildOf, p);
    ecs_entity_t gc1 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_entity_t gc2 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc2, Foo);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(Foo, ecs_field_id(&it, 3));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 4));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_field_is_set(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 4));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc1, ecs_iter_get_var(&it, gc_var));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r);
    
    ecs_fini(world);
}

void Basic_unknown_before_known_after_optional(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($gc, $c), ?Foo($gc), ChildOf($c, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int c_var = ecs_query_find_var(r, "c");
    test_assert(c_var != -1);
    int gc_var = ecs_query_find_var(r, "gc");
    test_assert(gc_var != -1);

    ecs_entity_t p = ecs_new(world, Foo);
    ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, p);
    /* ecs_entity_t c2 = */ ecs_new_w_pair(world, EcsChildOf, p);
    ecs_entity_t gc1 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_entity_t gc2 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc2, Foo);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(Foo, ecs_field_id(&it, 3));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 4));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_field_is_set(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 4));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc1, ecs_iter_get_var(&it, gc_var));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(ecs_pair(EcsChildOf, c), ecs_field_id(&it, 2));
    test_uint(Foo, ecs_field_id(&it, 3));
    test_uint(ecs_pair(EcsChildOf, p), ecs_field_id(&it, 4));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 4));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc2, ecs_iter_get_var(&it, gc_var));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r);
    
    ecs_fini(world);
}

void Basic_unknown_before_known_after_scope(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($gc, $c), !{Foo($gc) || Bar($gc)}, ChildOf($c, $this)",
        .cache_kind = cache_kind
    });

    test_assert(r != NULL);

    int c_var = ecs_query_find_var(r, "c");
    test_assert(c_var != -1);
    int gc_var = ecs_query_find_var(r, "gc");
    test_assert(gc_var != -1);

    ecs_entity_t p = ecs_new(world, Foo);
    ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, p);
    /* ecs_entity_t c2 = */ ecs_new_w_pair(world, EcsChildOf, p);
    ecs_entity_t gc1 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_entity_t gc2 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc2, Foo);
    ecs_entity_t gc3 = ecs_new_w_pair(world, EcsChildOf, c);
    ecs_add(world, gc3, Bar);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p, it.entities[0]);
    test_uint(Foo, ecs_field_id(&it, 1));
    test_uint(c, ecs_iter_get_var(&it, c_var));
    test_uint(gc1, ecs_iter_get_var(&it, gc_var));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(r);
    
    ecs_fini(world);
}

void Basic_2_trivial_mixed_2_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Mass);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tag);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), Bar(self), Mass(ent:self)",
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add(world, e1, Foo);
    ecs_add(world, e1, Bar);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add(world, e2, Foo);
    ecs_add(world, e2, Bar);

    ecs_entity_t e3 = ecs_new_id(world);
    ecs_add(world, e3, Foo);
    ecs_add(world, e3, Bar);
    ecs_add(world, e3, Tag);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Mass, {100});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);

        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(Bar, ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e3, it.entities[0]);

        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(Bar, ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_trivial_mixed_2_tables_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TAG(world, Tag);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self), Velocity(self), Mass(ent:self)",
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e1, Velocity, {1, 2});

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_set(world, e2, Position, {20, 30});
    ecs_set(world, e2, Velocity, {2, 3});

    ecs_entity_t e3 = ecs_new_id(world);
    ecs_set(world, e3, Position, {30, 40});
    ecs_set(world, e3, Velocity, {3, 4});
    ecs_add(world, e3, Tag);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Mass, {100});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);

        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 10); test_int(p[0].y, 20);
            test_int(p[1].x, 20); test_int(p[1].y, 30);

            Velocity *v = ecs_field(&it, Velocity, 2);
            test_assert(v != NULL);
            test_int(v[0].x, 1); test_int(v[0].y, 2);
            test_int(v[1].x, 2); test_int(v[1].y, 3);

            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e3, it.entities[0]);

        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 30); test_int(p[0].y, 40);

            Velocity *v = ecs_field(&it, Velocity, 2);
            test_assert(v != NULL);
            test_int(v[0].x, 3); test_int(v[0].y, 4);

            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}

void Basic_2_trivial_mixed_2_tables_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Mass);
    ECS_TAG(world, Foo);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, Tag);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), ChildOf(self, *), Mass(ent:self)",
        .flags = EcsQueryIsInstanced
    });

    test_assert(r != NULL);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add(world, e1, Foo);
    ecs_add_pair(world, e1, EcsChildOf, TgtA);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add(world, e2, Foo);
    ecs_add_pair(world, e2, EcsChildOf, TgtA);

    ecs_entity_t e3 = ecs_new_id(world);
    ecs_add(world, e3, Foo);
    ecs_add_pair(world, e3, EcsChildOf, TgtA);
    ecs_add(world, e3, Tag);

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_set(world, ent, Mass, {100});

    {
        ecs_iter_t it = ecs_query_iter(world, r);
        test_bool(true, ecs_query_next(&it));
        test_uint(2, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);

        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsChildOf, TgtA), ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(true, ecs_query_next(&it));
        test_uint(1, it.count);
        test_uint(e3, it.entities[0]);

        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsChildOf, TgtA), ecs_field_id(&it, 2));
        test_uint(ecs_id(Mass), ecs_field_id(&it, 3));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(ent, ecs_field_src(&it, 3));

        {
            Mass *m = ecs_field(&it, Mass, 3);
            test_assert(m != NULL);
            test_int(*m, 100);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(r);

    ecs_fini(world);
}
