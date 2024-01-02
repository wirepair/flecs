#include <query.h>

void Toggle_query_disabled_from_nothing(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {TagA},
            {TagB, .src.id = EcsIsEntity}
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_id(world, TagA);
    ecs_add(world, e1, TagB);
    ecs_add_id(world, e1, ECS_TOGGLE | TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(ecs_field_id(&it, 1), TagA);
    test_uint(ecs_field_id(&it, 2), TagB);
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(false, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}
