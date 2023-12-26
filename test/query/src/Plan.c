#include <query.h>

void Plan_reordered_plan_1(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo, ChildOf($this, $p, $gp, $ggp), Bar($ggp)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      "
    LINE " 1. [ 0,  2]  selfupid    $[this]           (Foo)"
    LINE " 2. [ 1,  3]  and         $[this]           (ChildOf, $p)"
    LINE " 3. [ 2,  4]  and         $p                (ChildOf, $gp)"
    LINE " 4. [ 3,  5]  and         $gp               (ChildOf, $ggp)"
    LINE " 5. [ 4,  6]  selfupid    $ggp              (Bar)"
    LINE " 6. [ 5,  7]  setvars     "
    LINE " 7. [ 6,  8]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_reordered_plan_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo($ggp), ChildOf($this, $p, $gp, $ggp), Bar($this)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      "
    LINE " 1. [ 0,  2]  selfupid    $[ggp]            (Foo)"
    LINE " 2. [ 1,  3]  each        $ggp              ($[ggp])"
    LINE " 3. [ 2,  4]  and         $[gp]             (ChildOf, $ggp)"
    LINE " 4. [ 3,  5]  each        $gp               ($[gp])"
    LINE " 5. [ 4,  6]  and         $[p]              (ChildOf, $gp)"
    LINE " 6. [ 5,  7]  each        $p                ($[p])"
    LINE " 7. [ 6,  8]  and         $[this]           (ChildOf, $p)"
    LINE " 8. [ 7,  9]  selfupid    $[this]           (Bar)"
    LINE " 9. [ 8, 10]  setvars     "
    LINE "10. [ 9, 11]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_1_trivial_plan(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  andid       $[this]           (Foo)"
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_2_trivial_plan(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), Bar(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  triv        "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_1_trivial_plan_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  andid       $[this]           (Position)"
    LINE " 2. [ 1,  3]  popself     "
    LINE " 3. [ 2,  4]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_2_trivial_plan_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self), Velocity(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivpop     "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), Bar(self), ChildOf(self, p)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  triv        "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), Bar(self), ChildOf(self, *)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivwc      "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), Bar(self), ChildOf(self, _)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  triv        "
    LINE " 2. [ 1,  3]  andany      $[this]           (ChildOf, $_'1)"
    LINE " 3. [ 2,  4]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_pair_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self), Velocity(self), ChildOf(self, p)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivpop     "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_wildcard_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self), Velocity(self), ChildOf(self, *)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivwc      "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_3_trivial_plan_w_any_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "Position(self), Velocity(self), ChildOf(self, _)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivpop     "
    LINE " 2. [ 1,  3]  andany      $[this]           (ChildOf, $_'1)"
    LINE " 3. [ 2,  4]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_1_trivial_component_w_none(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[none] Position(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  andid       $[this]           (Position)"
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_2_trivial_component_w_none(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_new_entity(world, "p");

    ecs_query_t *r = ecs_query(world, {
        .expr = "[none] Position(self), [none] Velocity(self)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  triv        "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}

void Plan_2_trivial_plan_w_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self), ChildOf(self, *)"
    });

    ecs_log_enable_colors(false);

    const char *expect = 
    HEAD " 0. [-1,  1]  setids      " 
    LINE " 1. [ 0,  2]  trivwc      "
    LINE " 2. [ 1,  3]  yield       "
    LINE "";
    char *plan = ecs_query_plan(r);

    test_str(expect, plan);
    ecs_os_free(plan);

    ecs_query_fini(r);

    ecs_fini(world);
}
