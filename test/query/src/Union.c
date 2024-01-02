#include <query.h>

void Union_query_w_existing_switch_and_case(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_entity_t e1 = ecs_new_w_pair(world, Movement, Walking);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement, *)"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);

    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, EcsWildcard));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_w_new_switch_and_case(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Movement, Walking);
    ecs_entity_t e2 = ecs_new_w_pair(world, Movement, Running);
    ecs_entity_t e3 = ecs_new_w_pair(world, Movement, Walking);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 3);
    test_uint(it.entities[0], e1);
    test_uint(it.entities[1], e2);
    test_uint(it.entities[2], e3);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, EcsWildcard));
    test_assert(it.sizes != NULL);
    test_int(it.sizes[0], ECS_SIZEOF(ecs_entity_t));
    test_assert(it.ptrs != NULL);
    ecs_entity_t *cases = ecs_field(&it, ecs_entity_t, 1);
    test_uint(cases[0], Walking);
    test_uint(cases[1], Running);
    test_uint(cases[2], Walking);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_for_case_existing(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_entity_t e1 = ecs_new_w_pair(world, Movement, Walking);
    ecs_new_w_pair(world, Movement, Running);
    ecs_entity_t e3 = ecs_new_w_pair(world, Movement, Walking);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement, Walking)"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_for_case_new(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement, Walking)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Movement, Walking);
    ecs_new_w_pair(world, Movement, Running);
    ecs_entity_t e3 = ecs_new_w_pair(world, Movement, Walking);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_case_w_generation(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Rel, Union);

    ecs_entity_t tgt_1 = ecs_new_id(world);
    ecs_delete(world, tgt_1);
    tgt_1 = ecs_new_id(world);
    test_assert(tgt_1 != (uint32_t)tgt_1);

    ecs_entity_t tgt_2 = ecs_new_id(world);
    ecs_delete(world, tgt_2);
    tgt_2 = ecs_new_id(world);
    test_assert(tgt_2 != (uint32_t)tgt_2);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, tgt_1);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, tgt_2);

    ecs_iter_t it = ecs_query_iter(world, q);
    {
        test_bool(true, ecs_query_next(&it));
        test_int(it.count, 2);
        test_uint(it.entities[0], e1);
        test_uint(it.entities[1], e2);
        test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, EcsWildcard));
        ecs_entity_t *cases = ecs_field(&it, ecs_entity_t, 1);
        test_assert(cases != NULL);
        test_uint(cases[0], tgt_1);
        test_uint(cases[1], tgt_2);
    }

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_case_w_not_alive(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Rel, Union);

    ecs_entity_t tgt_1 = ecs_new_id(world);
    ecs_delete(world, tgt_1);
    tgt_1 = ecs_new_id(world);
    test_assert(tgt_1 != (uint32_t)tgt_1);

    ecs_entity_t tgt_2 = ecs_new_id(world);
    ecs_delete(world, tgt_2);
    tgt_2 = ecs_new_id(world);
    test_assert(tgt_2 != (uint32_t)tgt_2);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, tgt_1);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, tgt_2);

    ecs_delete(world, tgt_1);
    ecs_delete(world, tgt_2);

    ecs_iter_t it = ecs_query_iter(world, q);
    {
        test_bool(true, ecs_query_next(&it));
        test_int(it.count, 2);
        test_uint(it.entities[0], e1);
        test_uint(it.entities[1], e2);
        test_uint(ecs_field_id(&it, 1), ecs_pair(Rel, EcsWildcard));
        ecs_entity_t *cases = ecs_field(&it, ecs_entity_t, 1);
        test_assert(cases != NULL);
        test_uint(cases[0], tgt_1);
        test_uint(cases[1], tgt_2);
    }

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_for_switch_filter_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_query_t *q = ecs_query(world, {
        .expr = "[none] (Movement, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Movement, Walking);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, EcsWildcard));
    test_int(it.sizes[0], ECS_SIZEOF(ecs_entity_t));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_case_from_nothing(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {Tag},
            {ecs_pair(Movement, Walking), .src.id = EcsIsEntity }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_id(world, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), Tag);
    test_uint(ecs_field_id(&it, 2), ecs_pair(Movement, Walking));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(false, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_case_inherited(void) {
    test_quarantine("Aug 1st 2022");

    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_entity_t base_1 = ecs_new_w_pair(world, Movement, Walking);
    ecs_entity_t inst_1 = ecs_new_w_pair(world, EcsIsA, base_1);

    ecs_entity_t base_2 = ecs_new_w_pair(world, Movement, Running);
    ecs_new_w_pair(world, EcsIsA, base_2);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { ecs_pair(Movement, Walking) }
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base_1);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst_1);
    test_uint(ecs_field_id(&it, 1), ecs_pair(Movement, Walking));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Union_query_switch_from_nothing(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Movement, Union);
    ECS_TAG(world, Walking);
    ECS_TAG(world, Running);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {Tag},
            { ecs_pair(Movement, EcsWildcard), .src.id = EcsIsEntity }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_id(world, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), Tag);
    test_uint(ecs_field_id(&it, 2), ecs_pair(Movement, EcsWildcard));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(false, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}
