#include <query.h>
#include <stdlib.h>

static ecs_query_cache_kind_t cache_kind = EcsQueryCacheDefault;

void Toggle_setup(void) {
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

void Toggle_disabled_from_nothing(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {TagA},
            {TagB, .src.id = EcsIsEntity}
        },
        .cache_kind = cache_kind
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

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_disabled(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_enable_component(world, e1, Position, true);
    ecs_enable_component(world, e2, Position, false);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position",
        .cache_kind = cache_kind
    });

    int32_t table_count = 0, count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] != e2);
            test_assert(it.entities[i] == e1 || it.entities[i] == e3);
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
        }
        count += it.count;
        table_count ++;
    }

    test_int(count, 2);
    test_int(table_count, 2);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_disabled_pair(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tgt);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_entity_t e1 = ecs_new_w_pair(world, ecs_id(Position), Tgt);
    ecs_entity_t e2 = ecs_new_w_pair(world, ecs_id(Position), Tgt);
    ecs_entity_t e3 = ecs_new_w_pair(world, ecs_id(Position), Tgt);

    ecs_enable_pair(world, e1, Position, Tgt, true);
    ecs_enable_pair(world, e2, Position, Tgt, false);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Position, Tgt)",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t table_count = 0, count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] != e2);
            test_assert(it.entities[i] == e1 || it.entities[i] == e3);
            test_assert(ecs_is_enabled_pair(world, it.entities[i], Position, Tgt));
        }
        count += it.count;
        table_count ++;
    }

    test_int(count, 2);
    test_int(table_count, 2);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_disabled_skip_initial(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_enable_component(world, e1, Position, false);
    ecs_enable_component(world, e2, Position, true);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] != e1);
            test_assert(it.entities[i] == e2 || it.entities[i] == e3);
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
        }
        count += it.count;
    }

    test_int(count, 2);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_disabled_pair_skip_initial(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tgt);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_entity_t e1 = ecs_new_w_pair(world, ecs_id(Position), Tgt);
    ecs_entity_t e2 = ecs_new_w_pair(world, ecs_id(Position), Tgt);
    ecs_entity_t e3 = ecs_new_w_pair(world, ecs_id(Position), Tgt);

    ecs_enable_pair(world, e1, Position, Tgt, false);
    ecs_enable_pair(world, e2, Position, Tgt, true);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Position, Tgt)",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] != e1);
            test_assert(it.entities[i] == e2 || it.entities[i] == e3);
            test_assert(ecs_is_enabled_pair(world, it.entities[i], Position, Tgt));
        }
        count += it.count;
    }

    test_int(count, 2);

    ecs_query_fini(q);

    ecs_fini(world);
}

static
void test_disable_toggle_mod(int32_t total, int32_t mod) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < total; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_set(world, e, Position, {e, e});

        if (!(e % mod)) {
            ecs_enable_component(world, e, Position, false);
        } else {
            ecs_enable_component(world, e, Position, true);
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] % mod);
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_int(p[i].x, it.entities[i]);
            test_int(p[i].y, it.entities[i]);
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

static
void test_enable_toggle_mod(int32_t total, int32_t mod) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < total; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_set(world, e, Position, {e, e});
        if (e % mod) {
            ecs_enable_component(world, e, Position, false);
        } else {
            ecs_enable_component(world, e, Position, true);
            total_count ++;
        }
    }

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(!(it.entities[i] % mod));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_int(p[i].x, it.entities[i]);
            test_int(p[i].y, it.entities[i]);
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_64_mod_2(void) {
    test_disable_toggle_mod(64, 2);
}

void Toggle_64_mod_3(void) {
    test_disable_toggle_mod(64, 3);
}

void Toggle_64_mod_7(void) {
    test_disable_toggle_mod(64, 7);
}

void Toggle_64_mod_8(void) {
    test_disable_toggle_mod(64, 8);
}

void Toggle_64_mod_10(void) {
    test_disable_toggle_mod(64, 10);
}

void Toggle_64_mod_64(void) {
    test_disable_toggle_mod(64, 64);
}

void Toggle_64_mod_256(void) {
    test_disable_toggle_mod(64, 256);
}

void Toggle_64_mod_1024(void) {
    test_disable_toggle_mod(64, 1024);
}

void Toggle_100_mod_2(void) {
    test_disable_toggle_mod(100, 2);
}

void Toggle_100_mod_3(void) {
    test_disable_toggle_mod(100, 3);
}

void Toggle_100_mod_7(void) {
    test_disable_toggle_mod(100, 7);
}

void Toggle_100_mod_8(void) {
    test_disable_toggle_mod(100, 8);
}

void Toggle_100_mod_10(void) {
    test_disable_toggle_mod(100, 10);
}

void Toggle_100_mod_64(void) {
    test_disable_toggle_mod(100, 64);
}

void Toggle_100_mod_256(void) {
    test_disable_toggle_mod(100, 256);
}

void Toggle_100_mod_1024(void) {
    test_disable_toggle_mod(100, 1024);
}

void Toggle_128_mod_2(void) {
    test_disable_toggle_mod(128, 2);
}

void Toggle_128_mod_3(void) {
    test_disable_toggle_mod(128, 3);
}

void Toggle_128_mod_7(void) {
    test_disable_toggle_mod(128, 7);
}

void Toggle_128_mod_8(void) {
    test_disable_toggle_mod(128, 8);
}

void Toggle_128_mod_10(void) {
    test_disable_toggle_mod(128, 10);
}

void Toggle_128_mod_64(void) {
    test_disable_toggle_mod(128, 64);
}

void Toggle_128_mod_256(void) {
    test_disable_toggle_mod(128, 256);
}

void Toggle_128_mod_1024(void) {
    test_disable_toggle_mod(128, 1024);
}

void Toggle_200_mod_2(void) {
    test_disable_toggle_mod(200, 2);
}

void Toggle_200_mod_3(void) {
    test_disable_toggle_mod(200, 3);
}

void Toggle_200_mod_7(void) {
    test_disable_toggle_mod(200, 7);
}

void Toggle_200_mod_8(void) {
    test_disable_toggle_mod(200, 8);
}

void Toggle_200_mod_10(void) {
    test_disable_toggle_mod(200, 10);
}

void Toggle_200_mod_64(void) {
    test_disable_toggle_mod(200, 64);
}

void Toggle_200_mod_256(void) {
    test_disable_toggle_mod(200, 256);
}

void Toggle_200_mod_1024(void) {
    test_disable_toggle_mod(200, 1024);
}

void Toggle_1024_mod_2(void) {
    test_disable_toggle_mod(1024, 2);
}

void Toggle_1024_mod_3(void) {
    test_disable_toggle_mod(1024, 3);
}

void Toggle_1024_mod_7(void) {
    test_disable_toggle_mod(1024, 7);
}

void Toggle_1024_mod_8(void) {
    test_disable_toggle_mod(1024, 8);
}

void Toggle_1024_mod_10(void) {
    test_disable_toggle_mod(1024, 10);
}

void Toggle_1024_mod_64(void) {
    test_disable_toggle_mod(1024, 64);
}

void Toggle_1024_mod_256(void) {
    test_disable_toggle_mod(1024, 256);
}

void Toggle_1024_mod_1024(void) {
    test_disable_toggle_mod(1024, 1024);
}

void Toggle_enabled_64_mod_2(void) {
    test_enable_toggle_mod(64, 2);
}

void Toggle_enabled_64_mod_3(void) {
    test_enable_toggle_mod(64, 3);
}

void Toggle_enabled_64_mod_7(void) {
    test_enable_toggle_mod(64, 7);
}

void Toggle_enabled_64_mod_8(void) {
    test_enable_toggle_mod(64, 8);
}

void Toggle_enabled_64_mod_10(void) {
    test_enable_toggle_mod(64, 10);
}

void Toggle_enabled_64_mod_64(void) {
    test_enable_toggle_mod(64, 64);
}

void Toggle_enabled_64_mod_256(void) {
    test_enable_toggle_mod(64, 256);
}

void Toggle_enabled_64_mod_1024(void) {
    test_enable_toggle_mod(64, 1024);
}

void Toggle_enabled_100_mod_2(void) {
    test_enable_toggle_mod(100, 2);
}

void Toggle_enabled_100_mod_3(void) {
    test_enable_toggle_mod(100, 3);
}

void Toggle_enabled_100_mod_7(void) {
    test_enable_toggle_mod(100, 7);
}

void Toggle_enabled_100_mod_8(void) {
    test_enable_toggle_mod(100, 8);
}

void Toggle_enabled_100_mod_10(void) {
    test_enable_toggle_mod(100, 10);
}

void Toggle_enabled_100_mod_64(void) {
    test_enable_toggle_mod(100, 64);
}

void Toggle_enabled_100_mod_256(void) {
    test_enable_toggle_mod(100, 256);
}

void Toggle_enabled_100_mod_1024(void) {
    test_enable_toggle_mod(100, 1024);
}

void Toggle_enabled_128_mod_2(void) {
    test_enable_toggle_mod(128, 2);
}

void Toggle_enabled_128_mod_3(void) {
    test_enable_toggle_mod(128, 3);
}

void Toggle_enabled_128_mod_7(void) {
    test_enable_toggle_mod(128, 7);
}

void Toggle_enabled_128_mod_8(void) {
    test_enable_toggle_mod(128, 8);
}

void Toggle_enabled_128_mod_10(void) {
    test_enable_toggle_mod(128, 10);
}

void Toggle_enabled_128_mod_64(void) {
    test_enable_toggle_mod(128, 64);
}

void Toggle_enabled_128_mod_256(void) {
    test_enable_toggle_mod(128, 256);
}

void Toggle_enabled_128_mod_1024(void) {
    test_enable_toggle_mod(128, 1024);
}

void Toggle_enabled_200_mod_2(void) {
    test_enable_toggle_mod(200, 2);
}

void Toggle_enabled_200_mod_3(void) {
    test_enable_toggle_mod(200, 3);
}

void Toggle_enabled_200_mod_7(void) {
    test_enable_toggle_mod(200, 7);
}

void Toggle_enabled_200_mod_8(void) {
    test_enable_toggle_mod(200, 8);
}

void Toggle_enabled_200_mod_10(void) {
    test_enable_toggle_mod(200, 10);
}

void Toggle_enabled_200_mod_64(void) {
    test_enable_toggle_mod(200, 64);
}

void Toggle_enabled_200_mod_256(void) {
    test_enable_toggle_mod(200, 256);
}

void Toggle_enabled_200_mod_1024(void) {
    test_enable_toggle_mod(200, 1024);
}

void Toggle_enabled_1024_mod_2(void) {
    test_enable_toggle_mod(1024, 2);
}

void Toggle_enabled_1024_mod_3(void) {
    test_enable_toggle_mod(1024, 3);
}

void Toggle_enabled_1024_mod_7(void) {
    test_enable_toggle_mod(1024, 7);
}

void Toggle_enabled_1024_mod_8(void) {
    test_enable_toggle_mod(1024, 8);
}

void Toggle_enabled_1024_mod_10(void) {
    test_enable_toggle_mod(1024, 10);
}

void Toggle_enabled_1024_mod_64(void) {
    test_enable_toggle_mod(1024, 64);
}

void Toggle_enabled_1024_mod_256(void) {
    test_enable_toggle_mod(1024, 256);
}

void Toggle_enabled_1024_mod_1024(void) {
    test_enable_toggle_mod(1024, 1024);
}

void Toggle_mod_2_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        if (!(e % 2)) {
            ecs_enable_component(world, e, Position, true);
        } else {
            ecs_enable_component(world, e, Position, false);
        }
        
        if (!(e % 3)) {
            ecs_enable_component(world, e, Velocity, true);
        } else {
            ecs_enable_component(world, e, Velocity, false);
        }        

        if (!(e % 2) && !(e % 3)) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(!(it.entities[i] % 2) && !(it.entities[i] % 3));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_mod_8_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        if (!(e % 8)) {
            ecs_enable_component(world, e, Position, true);
        } else {
            ecs_enable_component(world, e, Position, false);
        }
        
        if (!(e % 4)) {
            ecs_enable_component(world, e, Velocity, true);
        } else {
            ecs_enable_component(world, e, Velocity, false);
        }        

        if (!(e % 8) && !(e % 4)) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(!(it.entities[i] % 8) && !(it.entities[i] % 4));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_mod_64_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        if (!(e % 64)) {
            ecs_enable_component(world, e, Position, true);
        } else {
            ecs_enable_component(world, e, Position, false);
        }
        
        if (!(e % 16)) {
            ecs_enable_component(world, e, Velocity, true);
        } else {
            ecs_enable_component(world, e, Velocity, false);
        }        

        if (!(e % 64) && !(e % 16)) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(!(it.entities[i] % 64) && !(it.entities[i] % 16));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_mod_256_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        if (!(e % 256)) {
            ecs_enable_component(world, e, Position, true);
        } else {
            ecs_enable_component(world, e, Position, false);
        }
        
        if (!(e % 64)) {
            ecs_enable_component(world, e, Velocity, true);
        } else {
            ecs_enable_component(world, e, Velocity, false);
        }        

        if (!(e % 256) && !(e % 64)) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(!(it.entities[i] % 256) && !(it.entities[i] % 64));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_mod_1024_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        if (!(e % 1024)) {
            ecs_enable_component(world, e, Position, true);
        } else {
            ecs_enable_component(world, e, Position, false);
        }
        
        if (!(e % 128)) {
            ecs_enable_component(world, e, Velocity, true);
        } else {
            ecs_enable_component(world, e, Velocity, false);
        }        

        if (!(e % 1024) && !(e % 128)) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(!(it.entities[i] % 1024) && !(it.entities[i] % 128));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_randomized_2_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);

        bool enable_1 = rand() % 2;
        ecs_enable_component(world, e, Position, enable_1);
        bool enable_2 = rand() % 2;
        ecs_enable_component(world, e, Velocity, enable_2);
        
        if (enable_1 && enable_2) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_randomized_3_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);
    ecs_add_id(world, ecs_id(Mass), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        ecs_add(world, e, Mass);

        bool enable_1 = rand() % 2;
        ecs_enable_component(world, e, Position, enable_1);
        bool enable_2 = rand() % 2;
        ecs_enable_component(world, e, Velocity, enable_2);
        bool enable_3 = rand() % 2;
        ecs_enable_component(world, e, Mass, enable_3);        

        if (enable_1 && enable_2 && enable_3) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity, Mass",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Mass));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_randomized_4_bitsets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Rotation);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);
    ecs_add_id(world, ecs_id(Velocity), EcsCanToggle);
    ecs_add_id(world, ecs_id(Mass), EcsCanToggle);
    ecs_add_id(world, ecs_id(Rotation), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 65536; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_add(world, e, Velocity);
        ecs_add(world, e, Mass);
        ecs_add(world, e, Rotation);

        bool enable_1 = rand() % 2;
        ecs_enable_component(world, e, Position, enable_1);
        bool enable_2 = rand() % 2;
        ecs_enable_component(world, e, Velocity, enable_2);
        bool enable_3 = rand() % 2;
        ecs_enable_component(world, e, Mass, enable_3);        
        bool enable_4 = rand() % 2;
        ecs_enable_component(world, e, Rotation, enable_4); 

        if (enable_1 && enable_2 && enable_3 && enable_4) {
            total_count ++;
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity, Mass, Rotation",
        .cache_kind = cache_kind
    });
    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Velocity));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Mass));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Rotation));
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_toggle_w_other_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 1024; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_set(world, e, Position, {e, e});

        if (!(e % 3)) {
            ecs_enable_component(world, e, Position, false);
            if (!(e % 5)) {
                ecs_add(world, e, Tag);
            }
        } else {
            ecs_enable_component(world, e, Position, true);
            if (!(e % 5)) {
                ecs_add(world, e, Tag);
                total_count ++;
            }
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Tag",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(Tag, ecs_field_id(&it, 2));
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] % 3);
            test_assert(!(it.entities[i] % 5));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_int(p[i].x, it.entities[i]);
            test_int(p[i].y, it.entities[i]);
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_toggle_w_other_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Tag);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    int32_t i, total_count = 0;
    for (i = 0; i < 1024; i ++) {
        ecs_entity_t e = ecs_new(world, Position);
        ecs_set(world, e, Position, {e, e});

        if (!(e % 3)) {
            ecs_enable_component(world, e, Position, false);
            if (!(e % 5)) {
                ecs_set(world, e, Velocity, {e * 2, e * 2});
            }
        } else {
            ecs_enable_component(world, e, Position, true);
            if (!(e % 5)) {
                ecs_set(world, e, Velocity, {e * 2, e * 2});
                total_count ++;
            }
        }
    }

    test_assert(total_count != 0);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity",
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, q);

    int32_t count = 0;

    while (ecs_query_next(&it)) {
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);

        int32_t i;
        for (i = 0; i < it.count; i ++) {
            test_assert(it.entities[i] % 3);
            test_assert(!(it.entities[i] % 5));
            test_assert(ecs_is_enabled_component(world, it.entities[i], Position));
            test_int(p[i].x, it.entities[i]);
            test_int(p[i].y, it.entities[i]);
            test_int(v[i].x, it.entities[i] * 2);
            test_int(v[i].y, it.entities[i] * 2);
        }
        count += it.count;
    }

    test_int(count, total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

static
int compare_position(ecs_entity_t e1, const void *ptr1, ecs_entity_t e2, const void *ptr2) {
    const Position *p1 = ptr1;
    const Position *p2 = ptr2;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

void Toggle_sort(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_entity_t e1 = ecs_set(world, 0, Position, {3, 2});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {2, 2});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {1, 2});
    ecs_entity_t e4 = ecs_set(world, 0, Position, {0, 2});

    ecs_enable_component(world, e1, Position, true);
    ecs_enable_component(world, e2, Position, true);
    ecs_enable_component(world, e3, Position, false);
    ecs_enable_component(world, e4, Position, false);

    test_bool(ecs_is_enabled_component(world, e1, Position), true);
    test_bool(ecs_is_enabled_component(world, e2, Position), true);
    test_bool(ecs_is_enabled_component(world, e3, Position), false);
    test_bool(ecs_is_enabled_component(world, e4, Position), false);
    
    ecs_query_t *q = ecs_query(world, {
        .expr = "Position",
        .order_by_component = ecs_id(Position),
        .order_by = compare_position,
        .cache_kind = cache_kind
    });

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 2);
    test_assert(it.entities[0] == e2);
    test_assert(it.entities[1] == e1);
    test_assert(!ecs_query_next(&it));

    /* Entities will have shuffled around, ensure bits got shuffled too */
    test_bool(ecs_is_enabled_component(world, e1, Position), true);
    test_bool(ecs_is_enabled_component(world, e2, Position), true);
    test_bool(ecs_is_enabled_component(world, e3, Position), false);
    test_bool(ecs_is_enabled_component(world, e4, Position), false);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Toggle_table_move_2_from_3(void) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, Tag);

    ecs_add_id(world, ecs_id(Position), EcsCanToggle);

    ecs_query_t *q = ecs_query(world, { 
        .expr = "Position",
        .cache_kind = cache_kind
    });

    ecs_entity_t e1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(world, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(world, 0, Position, {30, 40});

    ecs_enable_component(world, e1, Position, true);
    ecs_enable_component(world, e2, Position, false);
    ecs_enable_component(world, e3, Position, true);

    test_bool(ecs_is_enabled_component(world, e1, Position), true);
    test_bool(ecs_is_enabled_component(world, e2, Position), false);
    test_bool(ecs_is_enabled_component(world, e3, Position), true);

    ecs_add(world, e3, Tag);
    ecs_add(world, e2, Tag);
    
    test_bool(ecs_is_enabled_component(world, e1, Position), true);
    test_bool(ecs_is_enabled_component(world, e2, Position), false);
    test_bool(ecs_is_enabled_component(world, e3, Position), true);

    ecs_iter_t it = ecs_query_iter(world, q);
    {
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 10); test_int(p->y, 20);
    }
    {
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e3, it.entities[0]);
        Position *p = ecs_field(&it, Position, 1);
        test_int(p->x, 30); test_int(p->y, 40);
    }
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}
