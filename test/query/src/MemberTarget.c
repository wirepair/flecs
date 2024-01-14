#include <query.h>

static ecs_query_cache_kind_t cache_kind = EcsQueryCacheDefault;

void MemberTarget_setup(void) {
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

typedef struct {
    ecs_entity_t value;
} Movement;

typedef struct {
    ecs_entity_t a;
    ecs_entity_t b;
} TwoMembers;

static ecs_entity_t ecs_id(Movement) = 0;
static ecs_entity_t ecs_id(TwoMembers) = 0;
static ecs_entity_t Running = 0;
static ecs_entity_t Walking = 0;
static ecs_entity_t Sitting = 0;

static void register_types(
    ecs_world_t *world)
{
    ecs_id(Movement) = ecs_struct(world, {
        .entity = ecs_entity(world, { .name = "Movement" }),
        .members = {
            { "value", ecs_id(ecs_entity_t) }
        }
    });

    ecs_id(TwoMembers) = ecs_struct(world, {
        .entity = ecs_entity(world, { .name = "TwoMembers" }),
        .members = {
            { "a", ecs_id(ecs_entity_t) },
            { "b", ecs_id(ecs_entity_t) }
        }
    });

    Running = ecs_entity(world, { .name = "Running" });
    Walking = ecs_entity(world, { .name = "Walking" });
    Sitting = ecs_entity(world, { .name = "Sitting" });
}

void MemberTarget_this_member_eq_1(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_eq_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    printf("%s\n", ecs_query_plan(q));

    /* ecs_entity_t e1 = */ ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e5 = */ ecs_set(world, 0, Movement, { Sitting });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_eq_no_matches(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    /* ecs_entity_t e1 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e2 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Sitting });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e5 = */ ecs_set(world, 0, Movement, { Sitting });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_eq_all_matches(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, *)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, $x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Walking, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Sitting, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_var_written(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo($x), (Movement.value, $x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    ecs_add(world, Running, Foo);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_var_read(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Movement.value, $x), Foo($x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    ecs_add(world, Running, Foo);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, Movement, { Walking });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Foo, ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Foo, ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(Foo, ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_eq_1_2nd_member(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(TwoMembers.b, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, TwoMembers, { Walking, Running });
    ecs_entity_t e2 = ecs_set(world, 0, TwoMembers, { Walking, Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, TwoMembers, { Walking, Walking });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, TwoMembers, { Walking, Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, TwoMembers, { Walking, Running });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_eq_2_2nd_member(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(TwoMembers.b, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    /* ecs_entity_t e1 = */ ecs_set(world, 0, TwoMembers, { Sitting, Walking });
    ecs_entity_t e2 = ecs_set(world, 0, TwoMembers, { Sitting, Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, TwoMembers, { Sitting, Walking });
    ecs_entity_t e4 = ecs_set(world, 0, TwoMembers, { Sitting, Running });
    /* ecs_entity_t e5 = */ ecs_set(world, 0, TwoMembers, { Sitting, Sitting });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_var_same_1(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(TwoMembers.a, $x), (TwoMembers.b, $x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    ecs_entity_t e1 = ecs_set(world, 0, TwoMembers, { Running, Running });
    ecs_entity_t e2 = ecs_set(world, 0, TwoMembers, { Walking, Walking });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, TwoMembers, { Walking, Sitting });
    /* ecs_entity_t e4 = */ ecs_set(world, 0, TwoMembers, { Sitting, Walking });
    ecs_entity_t e5 = ecs_set(world, 0, TwoMembers, { Sitting, Sitting });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Walking, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Sitting, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_member_var_same_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(TwoMembers.a, $x), (TwoMembers.b, $x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    /* ecs_entity_t e1 = */ ecs_set(world, 0, TwoMembers, { Walking, Running });
    ecs_entity_t e2 = ecs_set(world, 0, TwoMembers, { Running, Running });
    /* ecs_entity_t e3 = */ ecs_set(world, 0, TwoMembers, { Walking, Sitting });
    ecs_entity_t e4 = ecs_set(world, 0, TwoMembers, { Walking, Walking });
    /* ecs_entity_t e5 = */ ecs_set(world, 0, TwoMembers, { Running, Sitting });

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Walking, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 1);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_written_member_eq_1(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo, (Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    ecs_add(world, e1, Foo);
    ecs_add(world, e2, Foo);
    ecs_add(world, e3, Foo);
    ecs_add(world, e4, Foo);
    ecs_add(world, e5, Foo);

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_written_member_eq_2(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo, (Movement.value, Running)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Sitting });

    ecs_add(world, e1, Foo);
    ecs_add(world, e2, Foo);
    ecs_add(world, e3, Foo);
    ecs_add(world, e4, Foo);
    ecs_add(world, e5, Foo);

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_written_member_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo, (Movement.value, *)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    ecs_add(world, e1, Foo);
    ecs_add(world, e2, Foo);
    ecs_add(world, e3, Foo);
    ecs_add(world, e4, Foo);
    ecs_add(world, e5, Foo);

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}

void MemberTarget_this_written_member_var(void) {
    ecs_world_t *world = ecs_mini();

    ECS_IMPORT(world, FlecsMeta);
    ECS_TAG(world, Foo);

    register_types(world);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo, (Movement.value, $x)",
        .cache_kind = cache_kind
    });

    test_assert(q != NULL);

    int x_var = ecs_query_find_var(q, "x");
    test_assert(x_var != -1);

    ecs_entity_t e1 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e2 = ecs_set(world, 0, Movement, { Running });
    ecs_entity_t e3 = ecs_set(world, 0, Movement, { Walking });
    ecs_entity_t e4 = ecs_set(world, 0, Movement, { Sitting });
    ecs_entity_t e5 = ecs_set(world, 0, Movement, { Running });

    ecs_add(world, e1, Foo);
    ecs_add(world, e2, Foo);
    ecs_add(world, e3, Foo);
    ecs_add(world, e4, Foo);
    ecs_add(world, e5, Foo);

    {
        ecs_iter_t it = ecs_query_iter(world, q);
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Walking, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Walking);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e4, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Sitting, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Sitting);
        }

        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e5, it.entities[0]);
        test_uint(Foo, ecs_field_id(&it, 1));
        test_uint(ecs_id(ecs_entity_t), ecs_field_id(&it, 2));
        test_uint(Running, ecs_iter_get_var(&it, x_var));
        {
            ecs_entity_t *m = ecs_field(&it, ecs_entity_t, 2);
            test_assert(m != NULL);
            test_int(m[0], Running);
        }

        test_bool(false, ecs_query_next(&it));
    }

    ecs_query_fini(q);

    ecs_fini(world);
}
