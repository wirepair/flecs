#include <api.h>
#include <stdlib.h>

void Toggle_is_component_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);

    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_fini(world);
}

void Toggle_is_empty_entity_disabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, 0);

    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_fini(world);
}

void Toggle_is_0_entity_disabled(void) {
    install_test_abort();

    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    test_expect_abort();

    test_bool(ecs_is_enabled_component(world, 0, Position), false);
}

void Toggle_is_0_component_disabled(void) {
    install_test_abort();
    
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, 0);

    test_expect_abort();

    test_bool(ecs_is_enabled_id(world, e, 0), false);
}

void Toggle_is_nonexist_component_disabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Velocity);

    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_fini(world);
}

void Toggle_is_enabled_component_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_fini(world);
}

void Toggle_is_disabled_component_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, false);
    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_fini(world);
}

void Toggle_has_enabled_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, true);
    
    test_bool(ecs_has_id(world, e, ECS_TOGGLE | ecs_id(Position)), true);

    ecs_fini(world);
}

void Toggle_is_enabled_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_add(world, e, Position);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_has_id(world, e, ECS_TOGGLE | ecs_id(Position)), true);
    test_bool(ecs_has(world, e, Position), true);

    ecs_fini(world);
}

void Toggle_is_enabled_after_remove(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_remove(world, e, Position);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_has_id(world, e, ECS_TOGGLE | ecs_id(Position)), true);
    test_bool(ecs_has(world, e, Position), false);

    ecs_fini(world);
}

void Toggle_is_enabled_after_disable(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Position, false);
    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_fini(world);
}

void Toggle_is_disabled_after_enable(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);

    ecs_enable_component(world, e, Position, false);
    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Position, false);
    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_fini(world);
}

void Toggle_is_enabled_randomized(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t entities[100000];
    bool enabled[100000];

    int32_t i;
    for (i = 0; i < 100000; i ++) {
        enabled[i] = rand() % 2;
        entities[i] = ecs_new_id(world);
        ecs_enable_component(world, entities[i], Position, enabled[i]);
    }

    for (i = 0; i < 100000; i ++) {
        test_bool(
            ecs_is_enabled_component(world, entities[i], Position), enabled[i]);
    }

    ecs_fini(world);
}

void Toggle_is_enabled_after_add_randomized(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t entities[100000];
    bool enabled[100000];

    int32_t i;
    for (i = 0; i < 100000; i ++) {
        enabled[i] = rand() % 2;
        entities[i] = ecs_new_id(world);
        ecs_enable_component(world, entities[i], Position, enabled[i]);
    }

    for (i = 0; i < 100000; i ++) {
        ecs_add(world, entities[i], Position);
    }

    for (i = 0; i < 100000; i ++) {
        test_bool(
            ecs_is_enabled_component(world, entities[i], Position), enabled[i]);
    }

    ecs_fini(world);
}

void Toggle_is_enabled_after_randomized_add_randomized(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t entities[100000];
    bool enabled[100000];

    int32_t i;
    for (i = 0; i < 100000; i ++) {
        enabled[i] = rand() % 2;
        entities[i] = ecs_new_id(world);
        ecs_enable_component(world, entities[i], Position, enabled[i]);
    }

    for (i = 0; i < 100000; i ++) {
        if (!(rand() % 5)) {
            ecs_add(world, entities[i], Position);
        }
    }

    for (i = 0; i < 100000; i ++) {
        test_bool(
            ecs_is_enabled_component(world, entities[i], Position), enabled[i]);
    }

    ecs_fini(world);
}

void Toggle_is_enabled_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, 0);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Velocity, false);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);

    ecs_fini(world);
}

void Toggle_is_enabled_3(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e = ecs_new(world, 0);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Velocity, false);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);

    ecs_enable_component(world, e, Mass, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);
    test_bool(ecs_is_enabled_component(world, e, Mass), true);

    ecs_fini(world);
}

void Toggle_is_enabled_2_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, 0);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Velocity, false);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);

    ecs_add(world, e, Position);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);    

    ecs_fini(world);
}

void Toggle_is_enabled_3_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e = ecs_new(world, 0);

    ecs_enable_component(world, e, Position, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_enable_component(world, e, Velocity, false);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);

    ecs_enable_component(world, e, Mass, true);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);
    test_bool(ecs_is_enabled_component(world, e, Mass), true);

    ecs_add(world, e, Position);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    test_bool(ecs_is_enabled_component(world, e, Velocity), false);
    test_bool(ecs_is_enabled_component(world, e, Mass), true);

    ecs_fini(world);
}

void Toggle_is_pair_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t obj = ecs_new_id(world);
    ecs_entity_t e = ecs_new_w_pair(world, ecs_id(Position), obj);

    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_fini(world);
}

void Toggle_is_enabled_pair_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_fini(world);
}

void Toggle_is_disabled_pair_enabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), false);

    ecs_fini(world);
}

void Toggle_has_enabled_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_has_id(world, e, ECS_TOGGLE | ecs_pair(ecs_id(Position), obj)), true);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_add_pair(world, e, ecs_id(Position), obj);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_has_id(world, e, ECS_TOGGLE |  ecs_pair(ecs_id(Position), obj)), true);
    test_bool(ecs_has_pair(world, e, ecs_id(Position), obj), true);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_after_remove(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_remove_pair(world, e, ecs_id(Position), obj);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_has_id(world, e, ECS_TOGGLE | ecs_pair(ecs_id(Position), obj)), true);
    test_bool(ecs_has_pair(world, e, ecs_id(Position), obj), false);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_after_disable(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Position, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), false);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_fini(world);
}

void Toggle_is_pair_disabled_after_enable(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), false);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Position, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), false);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Velocity, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_3(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Velocity, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);

    ecs_enable_pair(world, e, Mass, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);
    test_bool(ecs_is_enabled_pair(world, e, Mass, obj), true);

    ecs_fini(world);
}

void Toggle_is_pair_enabled_2_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Velocity, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);

    ecs_add_pair(world, e, ecs_id(Position), obj);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);    

    ecs_fini(world);
}

void Toggle_is_pair_enabled_3_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e = ecs_new(world, 0);
    ecs_entity_t obj = ecs_new_id(world);

    ecs_enable_pair(world, e, Position, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);

    ecs_enable_pair(world, e, Velocity, obj, false);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);

    ecs_enable_pair(world, e, Mass, obj, true);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);
    test_bool(ecs_is_enabled_pair(world, e, Mass, obj), true);

    ecs_add_pair(world, e, ecs_id(Position), obj);
    test_bool(ecs_is_enabled_pair(world, e, Position, obj), true);
    test_bool(ecs_is_enabled_pair(world, e, Velocity, obj), false);
    test_bool(ecs_is_enabled_pair(world, e, Mass, obj), true);

    ecs_fini(world);
}


void Toggle_defer_enable(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);
    test_bool(ecs_is_enabled_component(world, e, Position), true);

    ecs_defer_begin(world);
    ecs_enable_component(world, e, Position, false);
    test_bool(ecs_is_enabled_component(world, e, Position), true);
    ecs_defer_end(world);

    test_bool(ecs_is_enabled_component(world, e, Position), false);

    ecs_fini(world);
}
