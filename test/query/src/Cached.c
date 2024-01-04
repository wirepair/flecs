#include <query.h>
#include <stdlib.h>

void Cached_simple_query_existing_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_2_existing_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_add(world, e2, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_new_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new(world, TagA);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_2_new_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_add(world, e2, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_existing_and_new_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e1 = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_add(world, e2, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_wildcard_query_existing_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjA), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjB), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_wildcard_query_new_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjA), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjB), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_wildcard_query_existing_table_2_results_p_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    ECS_TAG(world, ObjC);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);
    ecs_add_pair(world, e1, Rel, ObjC);
    ecs_add_pair(world, e2, Rel, ObjC);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjA), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjC), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjB), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjC), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_wildcard_query_new_table_2_results_p_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    ECS_TAG(world, ObjC);

    ecs_query_t *q = ecs_query(world, {
        .expr = "(Rel, *)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, ObjA);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, ObjB);
    ecs_add_pair(world, e1, Rel, ObjC);
    ecs_add_pair(world, e2, Rel, ObjC);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjA), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjC), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjB), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(ecs_pair(Rel, ObjC), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_wildcard_query_2nd_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);
    ECS_TAG(world, Tag);

    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_add_pair(world, e1, Rel, TgtA);
    ecs_add_pair(world, e1, Rel, TgtB);

    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_add_pair(world, e2, Rel, TgtA);

    ecs_entity_t e3 = ecs_new(world, Tag);
    ecs_add_pair(world, e3, Rel, TgtA);
    ecs_add_pair(world, e3, Rel, TgtC);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ Tag }, { ecs_pair(Rel, EcsWildcard) }}
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtB), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtC), it.ids[1]);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_wildcard_query_2nd_term_self(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);
    ECS_TAG(world, Tag);

    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_add_pair(world, e1, Rel, TgtA);
    ecs_add_pair(world, e1, Rel, TgtB);

    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_add_pair(world, e2, Rel, TgtA);

    ecs_entity_t e3 = ecs_new(world, Tag);
    ecs_add_pair(world, e3, Rel, TgtA);
    ecs_add_pair(world, e3, Rel, TgtC);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ Tag }, { ecs_pair(Rel, EcsWildcard), .src.id = EcsSelf }}
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtB), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtA), it.ids[1]);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(Tag, it.ids[0]);
    test_uint(ecs_pair(Rel, TgtC), it.ids[1]);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_simple_query_existing_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_add(world, e1, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_remove(world, e1, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_existing_empty_type(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_PREFAB(world, TypeX, TagA, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_add(world, e1, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_simple_query_new_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_add(world, e1, TagB);
    ecs_remove(world, e1, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_component_query_existing_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_assert(ecs_field_size(&it, 1) == sizeof(Position));
    test_assert(ecs_field(&it, Position, 1) != NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_component_query_new_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new(world, Position);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_assert(ecs_field(&it, Position, 1) != NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_component_query_existing_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TagA);

    ecs_entity_t e = ecs_new(world, Position);
    ecs_add(world, e, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_remove(world, e, TagA);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_assert(ecs_field(&it, Position, 1) != NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_2_component_query_existing_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TAG(world, Tag);
    ECS_PREFAB(world, MyType, Position, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    ecs_add(world, e, Velocity);
    ecs_add(world, e, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity"
    });
    test_assert(q != NULL);

    ecs_remove(world, e, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_assert(ecs_field(&it, Position, 1) != NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_2_component_query_existing_empty_type(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_PREFAB(world, MyType, Position, Velocity);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity"
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new(world, Position);
    ecs_add(world, e, Velocity);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_uint(ecs_field_size(&it, 1), sizeof(Position));
    test_assert(ecs_field(&it, Position, 1) != NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_only_optional(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "?TagA"
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new(world, TagA);
    int32_t count = 0;

    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        if (ecs_field_is_set(&it, 1)) {
            test_assert(count == 0);
            test_int(it.count, 1);
            test_uint(it.entities[0], e);
            count ++;
        }
    }

    test_int(count, 1);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_only_optional_new_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_entity_t e = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "?TagA"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        if (ecs_field_is_set(&it, 1)) {
            test_assert(count == 0);
            test_int(it.count, 1);
            test_uint(it.entities[0], e);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    total_count = 0;

    ecs_remove(world, e, TagA);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 1));
        test_assert(it.count > 0);
        total_count ++;
    }

    test_assert(total_count == (prev_total_count - 1));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_only_optional_new_empty_non_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e = ecs_new(world, TagA);
    ecs_add(world, e, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "?TagA"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        if (ecs_field_is_set(&it, 1)) {
            test_assert(count == 0);
            test_int(it.count, 1);
            test_uint(it.entities[0], e);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    count = 0; total_count = 0;

    ecs_remove(world, e, TagA);
    ecs_table_t *table = ecs_get_table(world, e);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 1));
        test_assert(it.count > 0);
        total_count ++;
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
    }

    test_int(count, 1);
    test_assert(total_count == prev_total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_only_optional_new_unset_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_entity_t e = ecs_new(world, TagA);
    ecs_add(world, e, TagB);
    ecs_table_t *table = ecs_get_table(world, e);

    ecs_query_t *q = ecs_query(world, {
        .expr = "?TagC"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 1));
        test_assert(it.count > 0);
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    count = 0; total_count = 0;

    ecs_remove(world, e, TagA);
    table = ecs_get_table(world, e);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 1));
        test_assert(it.count > 0);
        total_count ++;
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
    }

    test_int(count, 1);
    test_assert(total_count == prev_total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_singleton_w_optional_new_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Singleton);
    ECS_TAG(world, TagA);

    ecs_singleton_add(world, Singleton);

    ecs_entity_t e = ecs_new(world, TagA);
    ecs_set_name(world, e, "e");

    ecs_query_t *q = ecs_query(world, {
        .expr = "Singleton($), ?TagA"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        if (ecs_field_is_set(&it, 2)) {
            test_assert(count == 0);
            test_int(it.count, 1);
            test_uint(it.entities[0], e);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    total_count = 0;

    ecs_remove(world, e, TagA);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 2));
        test_assert(it.count > 0);
        total_count ++;
    }

    test_assert(total_count == (prev_total_count - 1));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_singleton_w_optional_new_empty_non_empty_table(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Singleton);
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_singleton_add(world, Singleton);

    ecs_entity_t e = ecs_new(world, TagA);
    ecs_add(world, e, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Singleton($), ?TagA"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        if (ecs_field_is_set(&it, 2)) {
            test_assert(count == 0);
            test_int(it.count, 1);
            test_uint(it.entities[0], e);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    count = 0; total_count = 0;

    ecs_remove(world, e, TagA);
    ecs_table_t *table = ecs_get_table(world, e);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 2));
        test_assert(it.count > 0);
        total_count ++;
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
    }

    test_int(count, 1);
    test_assert(total_count == prev_total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_singleton_w_optional_new_unset_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Singleton);
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_singleton_add(world, Singleton);

    ecs_entity_t e = ecs_new(world, TagA);
    ecs_add(world, e, TagB);
    ecs_table_t *table = ecs_get_table(world, e);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Singleton($), ?TagC"
    });
    test_assert(q != NULL);

    int32_t count = 0, total_count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 2));
        test_assert(it.count > 0);
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
        total_count ++;
    }

    test_int(count, 1);
    test_assert(total_count >= count);

    int32_t prev_total_count = total_count;
    count = 0; total_count = 0;

    ecs_remove(world, e, TagA);
    table = ecs_get_table(world, e);

    it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(!ecs_field_is_set(&it, 2));
        test_assert(it.count > 0);
        total_count ++;
        if (it.entities[0] == e) {
            test_assert(table == it.table);
            count ++;
        }
    }

    test_int(count, 1);
    test_assert(total_count == prev_total_count);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_query_from_entity_w_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t g = ecs_new_entity(world, "Game");
    ecs_set(world, g, Position, {10, 20});
    ecs_set(world, g, Velocity, {1, 2});

    ecs_entity_t p = ecs_new_w_id(world, EcsPrefab);
    ecs_set(world, p, Mass, {30});
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, p);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Velocity), .src.name = "Game" },
            { .id = ecs_id(Mass), .src.id = EcsUp, .trav = EcsIsA }
        }
    });

    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_w_from_entity_match_after(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e1 = ecs_new_entity(world, "e");
    ecs_entity_t e2 = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA, TagB(e)"
    });
    test_assert(q != NULL);

    ecs_add(world, e1, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(ecs_field_src(&it, 1), 0);
    test_uint(ecs_field_id(&it, 1), TagA);
    test_uint(ecs_field_src(&it, 2), e1);
    test_uint(ecs_field_id(&it, 2), TagB);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_w_from_singleton_match_after(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e2 = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA, TagB($)"
    });
    test_assert(q != NULL);

    ecs_singleton_add(world, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(ecs_field_src(&it, 1), 0);
    test_uint(ecs_field_id(&it, 1), TagA);
    test_uint(ecs_field_src(&it, 2), TagB);
    test_uint(ecs_field_id(&it, 2), TagB);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_rematch_optional_after_add(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t base = ecs_new(world, 0);
    
    ecs_entity_t e1 = ecs_new(world, Position);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_entity_t e2 = ecs_new(world, Position);
    ecs_add(world, e2, Velocity);
    ecs_entity_t e3 = ecs_new(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, ?Velocity(up(IsA))"
    });
    test_assert(q != NULL);

    /* First iteration, base doesn't have Velocity but query should match with
     * entity anyway since the component is optional */
    ecs_iter_t it = ecs_query_iter(world, q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }
    test_int(count, 3);

    /* Add Velocity to base, should trigger rematch */
    ecs_add(world, base, Velocity);

    /* Trigger a merge, which triggers the rematch */
    ecs_readonly_begin(world);
    ecs_readonly_end(world);

    /* Second iteration, base has Velocity and entity should be able to access
     * the shared component. */
    it = ecs_query_iter(world, q);
    count = 0;
    
    while (ecs_query_next(&it)) {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        
        test_int(it.count, 1);
        test_assert(p != NULL);
        
        if (it.entities[0] == e1) {
            test_assert(v != NULL);
        } else if (it.entities[0] == e2) {
            test_assert(v == NULL);
        } else if (it.entities[0] == e3) {
            test_assert(v == NULL);
        }

        count ++;
    }
    test_int(count, 3);    

    ecs_fini(world);    
}

void Cached_get_owned_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_new(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag"
    });

    int count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(ecs_field_w_size(&it, 0, 1) == NULL);
        test_int(it.count, 1);
        test_int(it.entities[0], e);
        count += it.count;
    }

    test_int(count, 1);

    ecs_fini(world);
}

void Cached_get_shared_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t instance = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });

    int count = 0;
    ecs_iter_t it = ecs_query_iter(world, q);
    while (ecs_query_next(&it)) {
        test_assert(ecs_field_w_size(&it, 0, 1) == NULL);
        test_int(it.count, 1);
        test_int(it.entities[0], instance);
        count += it.count;
    }

    test_int(count, 1);

    ecs_fini(world);
}

void Cached_explicit_delete(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    /* Ensure query isn't deleted twice when deleting world */
     ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_get_column_size(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_int(ecs_field_size(&it, 1), sizeof(Position));
    test_assert(!ecs_query_next(&it));

    ecs_fini(world);    
}

void Cached_stresstest_query_free(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Hello);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add(world, e, Foo);
    ecs_add(world, e, Bar);
    ecs_add(world, e, Hello);

    /* Create & delete query to test if query is properly unregistered with
     * the table */

    for (int i = 0; i < 10000; i ++) {
        ecs_query_t *q = ecs_query(world, {
            .expr = "Foo"
        });
         ecs_query_fini(q);
    }

    /* If code did not crash, test passes */
    test_assert(true);

    ecs_fini(world);
}

void Cached_only_from_entity(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set_name(world, 0, "e");

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(e)"
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(!ecs_query_next(&it));

    ecs_add(world, e, Tag);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_assert(ecs_field_src(&it, 1) == e);
    test_assert(ecs_field_id(&it, 1) == Tag);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_only_from_singleton(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set_name(world, 0, "e");

    ecs_query_t *q = ecs_query(world, {
        .expr = "e($)"
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(!ecs_query_next(&it));

    ecs_add_id(world, e, e);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_assert(ecs_field_src(&it, 1) == e);
    test_assert(ecs_field_id(&it, 1) == e);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_only_not_from_entity(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set_name(world, 0, "e");

    ecs_query_t *q = ecs_query(world, {
        .expr = "!Tag(e)"
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_field_src(&it, 1) == e);
    test_assert(ecs_field_id(&it, 1) == Tag);
    test_assert(!ecs_query_next(&it));

    ecs_add(world, e, Tag);

    it = ecs_query_iter(world, q);
    test_assert(!ecs_query_next(&it));

    test_assert(ECS_BIT_IS_SET(it.flags, EcsIterIsValid) == false);
    ecs_fini(world);
}

void Cached_only_not_from_singleton(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t e = ecs_set_name(world, 0, "e");

    ecs_query_t *q = ecs_query(world, {
        .expr = "!e($)"
    });
    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_assert(ecs_field_src(&it, 1) == e);
    test_assert(ecs_field_id(&it, 1) == e);
    test_assert(!ecs_query_next(&it));

    ecs_add_id(world, e, e);

    it = ecs_query_iter(world, q);
    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_iter_valid(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ecs_new(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(it.flags & EcsIterIsValid, false);

    test_bool(ecs_query_next(&it), true);
    test_bool(it.flags & EcsIterIsValid, true);

    test_bool(ecs_query_next(&it), false);
    test_bool(it.flags & EcsIterIsValid, false);

    ecs_fini(world);
}

void Cached_query_optional_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    
    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_add_id(world, e2, TagB);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA, ?TagB"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {    
        test_uint(ecs_field_id(&it, 1), TagA);
        test_assert(ecs_field_id(&it, 2) == TagB);
        test_int(it.count, 1);

        if (it.entities[0] == e1) {
            test_bool(ecs_field_is_set(&it, 1), true);
            test_bool(ecs_field_is_set(&it, 2), false); 
        } else if (it.entities[0] == e2) {
            test_bool(ecs_field_is_set(&it, 1), true);
            test_bool(ecs_field_is_set(&it, 2), true); 
        }

        count ++;
    }

    test_int(count, 2);

    ecs_fini(world);
}

void Cached_query_optional_shared_tag(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    
    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_add_id(world, e2, TagB);
    
    ecs_entity_t e3 = ecs_new(world, TagA);
    ecs_add_pair(world, e3, EcsIsA, e2);

    ecs_query_t *q = ecs_query(world, {
        .expr = "TagA, ?TagB(self|up(IsA))"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    int32_t count = 0;
    
    while (ecs_query_next(&it)) {    
        test_uint(ecs_field_id(&it, 1), TagA);
        test_assert(ecs_field_id(&it, 2) == TagB);
        test_int(it.count, 1);

        if (it.entities[0] == e1) {
            test_bool(ecs_field_is_set(&it, 1), true);
            test_bool(ecs_field_is_set(&it, 2), false); 
        } else if (it.entities[0] == e2) {
            test_bool(ecs_field_is_set(&it, 1), true);
            test_bool(ecs_field_is_set(&it, 2), true); 
        } else if (it.entities[0] == e3) {
            test_bool(ecs_field_is_set(&it, 1), true);
            test_bool(ecs_field_is_set(&it, 2), true);
        }

        count ++;
    }

    test_int(count, 3);

    ecs_fini(world);
}

void Cached_query_iter_10_tags(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);
    ECS_TAG(world, TagD);
    ECS_TAG(world, TagE);
    ECS_TAG(world, TagF);
    ECS_TAG(world, TagG);
    ECS_TAG(world, TagH);
    ECS_TAG(world, TagI);
    ECS_TAG(world, TagJ);
    ECS_TAG(world, TagK);

    ecs_entity_t e_1 = ecs_new(world, TagA);
    ecs_add_id(world, e_1, TagB);
    ecs_add_id(world, e_1, TagC);
    ecs_add_id(world, e_1, TagD);
    ecs_add_id(world, e_1, TagE);
    ecs_add_id(world, e_1, TagF);
    ecs_add_id(world, e_1, TagG);
    ecs_add_id(world, e_1, TagH);
    ecs_add_id(world, e_1, TagI);
    ecs_add_id(world, e_1, TagJ);
    
    ecs_entity_t e_2 = ecs_new(world, TagA);
    ecs_add_id(world, e_2, TagB);
    ecs_add_id(world, e_2, TagC);
    ecs_add_id(world, e_2, TagD);
    ecs_add_id(world, e_2, TagE);
    ecs_add_id(world, e_2, TagF);
    ecs_add_id(world, e_2, TagG);
    ecs_add_id(world, e_2, TagH);
    ecs_add_id(world, e_2, TagI);
    ecs_add_id(world, e_2, TagJ);
    ecs_add_id(world, e_2, TagK); /* 2nd match in different table */

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {TagA}, {TagB}, {TagC}, {TagD}, {TagE}, {TagF}, {TagG}, {TagH}, 
            {TagI}, {TagJ}
        }
    });

    ecs_iter_t it = ecs_query_iter(world, q);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), TagA);
    test_int(ecs_field_id(&it, 2), TagB);
    test_int(ecs_field_id(&it, 3), TagC);
    test_int(ecs_field_id(&it, 4), TagD);
    test_int(ecs_field_id(&it, 5), TagE);
    test_int(ecs_field_id(&it, 6), TagF);
    test_int(ecs_field_id(&it, 7), TagG);
    test_int(ecs_field_id(&it, 8), TagH);
    test_int(ecs_field_id(&it, 9), TagI);
    test_int(ecs_field_id(&it, 10), TagJ);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_2);
    test_int(ecs_field_id(&it, 1), TagA);
    test_int(ecs_field_id(&it, 2), TagB);
    test_int(ecs_field_id(&it, 3), TagC);
    test_int(ecs_field_id(&it, 4), TagD);
    test_int(ecs_field_id(&it, 5), TagE);
    test_int(ecs_field_id(&it, 6), TagF);
    test_int(ecs_field_id(&it, 7), TagG);
    test_int(ecs_field_id(&it, 8), TagH);
    test_int(ecs_field_id(&it, 9), TagI);
    test_int(ecs_field_id(&it, 10), TagJ);

    test_assert(!ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

typedef struct {
    float v;
} CompA, CompB, CompC, CompD, CompE, CompF, CompG, CompH, CompI, CompJ, CompK,
  CompL, CompM, CompN, CompO, CompP, CompQ, CompR, CompS, CompT, CompU;

void Cached_query_iter_10_components(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, CompA);
    ECS_COMPONENT(world, CompB);
    ECS_COMPONENT(world, CompC);
    ECS_COMPONENT(world, CompD);
    ECS_COMPONENT(world, CompE);
    ECS_COMPONENT(world, CompF);
    ECS_COMPONENT(world, CompG);
    ECS_COMPONENT(world, CompH);
    ECS_COMPONENT(world, CompI);
    ECS_COMPONENT(world, CompJ);
    ECS_COMPONENT(world, CompK);

    ecs_entity_t e_1 = ecs_set(world, 0, CompA, {10});
    ecs_set(world, e_1, CompB, {10});
    ecs_set(world, e_1, CompC, {10});
    ecs_set(world, e_1, CompD, {10});
    ecs_set(world, e_1, CompE, {10});
    ecs_set(world, e_1, CompF, {10});
    ecs_set(world, e_1, CompG, {10});
    ecs_set(world, e_1, CompH, {10});
    ecs_set(world, e_1, CompI, {10});
    ecs_set(world, e_1, CompJ, {10});
    
    ecs_entity_t e_2 = ecs_set(world, 0, CompA, {10});
    ecs_set(world, e_2, CompB, {10});
    ecs_set(world, e_2, CompC, {10});
    ecs_set(world, e_2, CompD, {10});
    ecs_set(world, e_2, CompE, {10});
    ecs_set(world, e_2, CompF, {10});
    ecs_set(world, e_2, CompG, {10});
    ecs_set(world, e_2, CompH, {10});
    ecs_set(world, e_2, CompI, {10});
    ecs_set(world, e_2, CompJ, {10});
    ecs_set(world, e_2, CompK, {10});

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            {ecs_id(CompA)}, {ecs_id(CompB)}, {ecs_id(CompC)}, {ecs_id(CompD)}, 
            {ecs_id(CompE)}, {ecs_id(CompF)}, {ecs_id(CompG)}, {ecs_id(CompH)}, 
            {ecs_id(CompI)}, {ecs_id(CompJ)}
        }
    });

    ecs_iter_t it = ecs_query_iter(world, q);

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_1);
    test_int(ecs_field_id(&it, 1), ecs_id(CompA));
    test_int(ecs_field_id(&it, 2), ecs_id(CompB));
    test_int(ecs_field_id(&it, 3), ecs_id(CompC));
    test_int(ecs_field_id(&it, 4), ecs_id(CompD));
    test_int(ecs_field_id(&it, 5), ecs_id(CompE));
    test_int(ecs_field_id(&it, 6), ecs_id(CompF));
    test_int(ecs_field_id(&it, 7), ecs_id(CompG));
    test_int(ecs_field_id(&it, 8), ecs_id(CompH));
    test_int(ecs_field_id(&it, 9), ecs_id(CompI));
    test_int(ecs_field_id(&it, 10), ecs_id(CompJ));

    int i;
    for (i = 0; i < 10; i ++) {
        CompA *ptr = ecs_field_w_size(&it, 0, i + 1);
        test_assert(ptr != NULL);
        test_int(ptr[0].v, 10);
    }

    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e_2);
    test_int(ecs_field_id(&it, 1), ecs_id(CompA));
    test_int(ecs_field_id(&it, 2), ecs_id(CompB));
    test_int(ecs_field_id(&it, 3), ecs_id(CompC));
    test_int(ecs_field_id(&it, 4), ecs_id(CompD));
    test_int(ecs_field_id(&it, 5), ecs_id(CompE));
    test_int(ecs_field_id(&it, 6), ecs_id(CompF));
    test_int(ecs_field_id(&it, 7), ecs_id(CompG));
    test_int(ecs_field_id(&it, 8), ecs_id(CompH));
    test_int(ecs_field_id(&it, 9), ecs_id(CompI));
    test_int(ecs_field_id(&it, 10), ecs_id(CompJ));

    for (i = 0; i < 10; i ++) {
        CompA *ptr = ecs_field_w_size(&it, 0, i + 1);
        test_assert(ptr != NULL);
        test_int(ptr[0].v, 10);
    }

    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_iter_type_set(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    
    ecs_entity_t e = ecs_new(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e);
    test_assert(it.table != NULL);
    const ecs_type_t *type = ecs_table_get_type(it.table);
    test_int(type->count, 1);
    test_int(type->array[0], ecs_id(Position));

    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_filter_term(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ .id = ecs_id(Position), .inout = EcsInOutNone }}
    });

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});

    ecs_iter_t it = ecs_query_iter(world, q);

    test_bool(ecs_query_next(&it), true);
    test_assert(it.ids != NULL);
    test_assert(it.ids[0] == ecs_id(Position));

    test_int(it.count, 1);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e);

    test_assert(it.ptrs != NULL);
    test_assert(it.columns != NULL);

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_2_terms_1_filter(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), .inout = EcsInOutNone },
            { .id = ecs_id(Velocity) }
        }
    });

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    ecs_set(world, e, Velocity, {1, 1});

    ecs_iter_t it = ecs_query_iter(world, q);

    test_bool(ecs_query_next(&it), true);
    test_assert(it.ids != NULL);
    test_assert(it.ids[0] == ecs_id(Position));
    test_assert(it.ids[1] == ecs_id(Velocity));

    test_int(it.count, 1);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e);

    test_assert(it.ptrs != NULL);
    test_assert(it.sizes != NULL);
    test_assert(it.columns != NULL);

    test_assert(it.ptrs[0] == NULL);
    test_assert(it.ptrs[1] != NULL);

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_3_terms_2_filter(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), .inout = EcsInOutNone },
            { .id = ecs_id(Velocity), .inout = EcsInOutNone },
            { .id = ecs_id(Mass) }
        }
    });

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    ecs_set(world, e, Velocity, {1, 1});
    ecs_set(world, e, Mass, {1});

    ecs_iter_t it = ecs_query_iter(world, q);

    test_bool(ecs_query_next(&it), true);
    test_assert(it.ids != NULL);
    test_assert(it.ids[0] == ecs_id(Position));
    test_assert(it.ids[1] == ecs_id(Velocity));
    test_assert(it.ids[2] == ecs_id(Mass));

    test_int(it.count, 1);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e);

    test_assert(it.ptrs != NULL);
    test_assert(it.sizes != NULL);
    test_assert(it.columns != NULL);

    test_assert(it.ptrs[0] == NULL);
    test_assert(it.ptrs[1] == NULL);
    test_assert(it.ptrs[2] != NULL);

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_no_instancing_w_singleton(void) {
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

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position, Velocity($)"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e1);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e2);
        test_int(p->x, 20);
        test_int(p->y, 30);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e3);
        test_int(p->x, 30);
        test_int(p->y, 40);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e4);
        test_int(p->x, 40);
        test_int(p->y, 50);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(ecs_query_next(&it));
    {
        Position *p = ecs_field(&it, Position, 1);
        Velocity *v = ecs_field(&it, Velocity, 2);
        test_int(it.count, 1);
        test_int(it.entities[0], e5);
        test_int(p->x, 50);
        test_int(p->y, 60);
        test_int(v->x, 1);
        test_int(v->y, 2);
    }

    test_assert(!ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_no_instancing_w_shared(void) {

}

void Cached_query_iter_frame_offset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);
    ECS_TAG(world, TagC);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = TagA, }
        },
    });

    ecs_entity_t e1 = ecs_new(world, TagA);
    ecs_entity_t e2 = ecs_new(world, TagA);
    ecs_entity_t e3 = ecs_new(world, TagA);
    ecs_entity_t e4 = ecs_new(world, TagA);
    ecs_entity_t e5 = ecs_new(world, TagA);

    ecs_add(world, e3, TagB);
    ecs_add(world, e4, TagB);
    ecs_add(world, e5, TagC);

    ecs_iter_t it = ecs_query_iter(world, q);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 0);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e1);
    test_assert(it.entities[1] == e2);
    test_assert(it.ids[0] == TagA);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 2);
    test_int(it.frame_offset, 2);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e3);
    test_assert(it.entities[1] == e4);
    test_assert(it.ids[0] == TagA);

    test_bool(ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.frame_offset, 4);
    test_assert(it.entities != NULL);
    test_assert(it.entities[0] == e5);
    test_assert(it.ids[0] == TagA);

    test_bool(ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_add_singleton_after_query(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { TagA },
            { TagB, .src.id = TagB }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add(world, e, TagA);
    
    ecs_singleton_add(world, TagB);
    test_assert(ecs_has(world, TagB, TagB));

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool (ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e);
    test_bool (ecs_query_next(&it), false);

    ecs_singleton_remove(world, TagB);
    test_assert(!ecs_has(world, TagB, TagB));

    it = ecs_query_iter(world, q);
    test_bool (ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_query_w_component_from_parent_from_non_this(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t parent = ecs_new(world, TagB);
    ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, parent);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { TagA },
            { TagB, .src.id = child|EcsUp, .trav = EcsChildOf }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e = ecs_new_id(world);
    ecs_add(world, e, TagA);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool (ecs_query_next(&it), true);
    test_int(it.count, 1);
    test_int(it.entities[0], e);
    test_int(it.sources[0], 0);
    test_int(it.sources[1], parent);
    test_bool (ecs_query_next(&it), false);

    ecs_remove_pair(world, child, EcsChildOf, parent);
    it = ecs_query_iter(world, q);
    test_bool (ecs_query_next(&it), false);

    ecs_fini(world);
}

void Cached_create_query_while_pending(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_entity_t e = ecs_new(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ TagA }}
    });
    test_assert(q != NULL);

    ecs_add(world, e, TagB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert( ecs_query_next(&it));
    test_int(it.count, 1);
    test_int(it.entities[0], e);

    test_assert( !ecs_query_next(&it));
    
    ecs_fini(world);
}

void Cached_empty_query(void) {
    ecs_world_t *world = ecs_mini();

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ 0 }}
    });
    test_assert(q != NULL);

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_implicit_existing_isa_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_implicit_new_isa_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset_2_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, base);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], base);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset_3_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, base);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsIsA, e2);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], base);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset_2_lvls_owned(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, base);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);

    ecs_add(world, e1, Tag);
    ecs_add(world, e2, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset_3_lvls_owned(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, base);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsIsA, e2);

    ecs_add(world, e1, Tag);
    ecs_add(world, e2, Tag);
    ecs_add(world, e3, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e2);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_superset_owned_empty_table_after_match(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, base);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsIsA, e2);

    ecs_add(world, e1, Tag);
    ecs_add(world, e2, Tag);
    ecs_add(world, e3, Tag);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e2);

    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, e3, EcsIsA, e2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], base);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_self_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(self|up(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up)"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_superset_2_targets(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, R, EcsTraversable);
    ECS_COMPONENT(world, Position);

    ecs_entity_t e_0 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e_1 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t e_2 = ecs_set(world, 0, Position, {50, 60});
    ecs_entity_t e_3 = ecs_set(world, 0, Position, {70, 80});

    ecs_add_pair(world, e_3, R, e_2);
    ecs_add_pair(world, e_2, R, e_1);
    ecs_add_pair(world, e_1, R, e_0);

    ecs_entity_t t = ecs_new_id(world);
    ecs_add(world, t, Position);
    ecs_add_pair(world, t, R, e_2);
    ecs_add_pair(world, t, R, e_1);
    ecs_delete(world, t);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Position(up(R))"
    });

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_3);
    test_uint(it.sources[0], e_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_0);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_superset_2_relations(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = TagA, .trav = EcsChildOf, .src.id = EcsUp },
            { .id = TagA, .trav = EcsIsA, .src.id = EcsUp },
        }
    });

    ecs_entity_t base = ecs_new(world, TagA);
    ecs_entity_t parent = ecs_new(world, TagA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add_pair(world, e2, EcsIsA, base);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(e2, it.entities[1]);
    test_uint(parent, it.sources[0]);
    test_uint(base, it.sources[1]);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_superset_2_relations_instanced(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, TagA);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = TagA, .trav = EcsChildOf, .src.id = EcsUp },
            { .id = TagA, .trav = EcsIsA, .src.id = EcsUp },
        },
        .flags = EcsQueryIsInstanced
    });

    ecs_entity_t base = ecs_new(world, TagA);
    ecs_entity_t parent = ecs_new(world, TagA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add_pair(world, e2, EcsIsA, base);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(e2, it.entities[1]);
    test_uint(parent, it.sources[0]);
    test_uint(base, it.sources[1]);
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_superset_2_relations_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), .trav = EcsChildOf, .src.id = EcsUp },
            { .id = ecs_id(Position), .trav = EcsIsA, .src.id = EcsUp },
        }
    });

    ecs_entity_t base = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t parent = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add_pair(world, e2, EcsIsA, base);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    {
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(parent, it.sources[0]);
        test_uint(base, it.sources[1]);
        Position *p1 = ecs_field(&it, Position, 1);
        Position *p2 = ecs_field(&it, Position, 2);
        test_assert(p1 != NULL);
        test_assert(p2 != NULL);
        test_int(p1->x, 30);
        test_int(p1->y, 40);
        test_int(p2->x, 10);
        test_int(p2->y, 20);
    }
    {
        test_bool(true, ecs_query_next(&it));
        test_int(1, it.count);
        test_uint(e2, it.entities[0]);
        test_uint(parent, it.sources[0]);
        test_uint(base, it.sources[1]);
        Position *p1 = ecs_field(&it, Position, 1);
        Position *p2 = ecs_field(&it, Position, 2);
        test_assert(p1 != NULL);
        test_assert(p2 != NULL);
        test_int(p1->x, 30);
        test_int(p1->y, 40);
        test_int(p2->x, 10);
        test_int(p2->y, 20);
    }
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_superset_2_relations_instanced_w_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_id(Position), .trav = EcsChildOf, .src.id = EcsUp },
            { .id = ecs_id(Position), .trav = EcsIsA, .src.id = EcsUp },
        },
        .flags = EcsQueryIsInstanced
    });

    ecs_entity_t base = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t parent = ecs_set(world, 0, Position, {30, 40});

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_add_pair(world, e1, EcsIsA, base);
    ecs_add_pair(world, e1, EcsChildOf, parent);

    ecs_entity_t e2 = ecs_new_id(world);
    ecs_add_pair(world, e2, EcsIsA, base);
    ecs_add_pair(world, e2, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    {
        test_bool(true, ecs_query_next(&it));
        test_int(2, it.count);
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_uint(parent, it.sources[0]);
        test_uint(base, it.sources[1]);
        Position *p1 = ecs_field(&it, Position, 1);
        Position *p2 = ecs_field(&it, Position, 2);
        test_assert(p1 != NULL);
        test_assert(p2 != NULL);
        test_int(p1->x, 30);
        test_int(p1->y, 40);
        test_int(p2->x, 10);
        test_int(p2->y, 20);
    }
    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_parent(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(up)"
    });
    test_assert(q != NULL);

    ecs_entity_t base = ecs_new(world, Tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_existing_isa_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsIsA, e2);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(IsA))"
    });
    test_assert(q != NULL);

    ecs_add_id(world, e1, Bar); /* mix up order */
    ecs_add_id(world, e2, Foo);

    ecs_iter_t it = ecs_query_iter(world, q);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_new_isa_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(IsA))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsIsA, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsIsA, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsIsA, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade)"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsChildOf, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsChildOf, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsChildOf, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_parent_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade)"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, EcsChildOf, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsChildOf, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, EcsChildOf, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_existing_custom_rel_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, Rel, e2);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(Rel))"
    });
    test_assert(q != NULL);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_new_custom_rel_cascade(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(Rel))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new_w_pair(world, Rel, e0);
    ecs_entity_t e2 = ecs_new_w_pair(world, Rel, e1);
    ecs_entity_t e3 = ecs_new_w_pair(world, Rel, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_w_2_depths(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(Rel))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_add_pair(world, e1, Rel, e0);
    ecs_add_pair(world, e2, Rel, e1);
    ecs_add_pair(world, e3, Rel, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e1);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_w_3_depths(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade(Rel))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_add_pair(world, e1, Rel, e0);
    ecs_add_pair(world, e2, Rel, e1);
    ecs_add_pair(world, e3, Rel, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e2);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_w_2_depths_desc(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade|desc(Rel))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_add_pair(world, e1, Rel, e0);
    ecs_add_pair(world, e2, Rel, e1);
    ecs_add_pair(world, e3, Rel, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_w_3_depths_desc(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_ENTITY(world, Rel, EcsTraversable);
    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .expr = "Tag(cascade|desc(Rel))"
    });
    test_assert(q != NULL);

    ecs_entity_t e0 = ecs_new(world, Tag);
    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_add_pair(world, e1, Rel, e0);
    ecs_add_pair(world, e2, Rel, e1);
    ecs_add_pair(world, e3, Rel, e2);

    ecs_add_id(world, e2, Foo); /* mix up order */
    ecs_add_id(world, e1, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(it.sources[0], e2);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(it.sources[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e1);
    test_uint(it.sources[0], e0);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_not_pair_relation_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    
    ecs_query_t *q = ecs_query(world, {
        .expr = "Foo, !(*, ObjA)"
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add_pair(world, e1, RelA, ObjA);
    ecs_add_pair(world, e2, RelA, ObjB);
    ecs_add_pair(world, e3, RelB, ObjA);
    ecs_add_pair(world, e4, RelB, ObjB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(ecs_field_id(&it, 2), ecs_pair(EcsWildcard, ObjA));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 2), ecs_pair(EcsWildcard, ObjA));

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_not_pair_object_wildcard(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    
    ecs_query_t *q = ecs_query(world, {
    .expr = "Foo, !(RelA, *)"
});
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add_pair(world, e1, RelA, ObjA);
    ecs_add_pair(world, e2, RelA, ObjB);
    ecs_add_pair(world, e3, RelB, ObjA);
    ecs_add_pair(world, e4, RelB, ObjB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e3);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, EcsWildcard));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, EcsWildcard));

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_two_pair_wildcards_one_not(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    
    ecs_query_t *q = ecs_query(world, {
    .expr = "Foo, (RelA, *), !(RelB, *)"
});
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add_pair(world, e1, RelA, ObjA);
    ecs_add_pair(world, e1, RelB, ObjA);

    ecs_add_pair(world, e2, RelA, ObjA);

    ecs_add_pair(world, e3, RelA, ObjB);
    ecs_add_pair(world, e3, RelB, ObjB);

    ecs_add_pair(world, e4, RelA, ObjB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, ObjA));
    test_uint(ecs_field_id(&it, 3), ecs_pair(RelB, EcsWildcard));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, ObjB));
    test_uint(ecs_field_id(&it, 3), ecs_pair(RelB, EcsWildcard));

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_two_pair_wildcards_one_not_any(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, ObjA);
    ECS_TAG(world, ObjB);
    
    ecs_query_t *q = ecs_query(world, {
    .expr = "Foo, (RelA, *), !(RelB, _)"
});
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_new(world, Foo);
    ecs_entity_t e2 = ecs_new(world, Foo);
    ecs_entity_t e3 = ecs_new(world, Foo);
    ecs_entity_t e4 = ecs_new(world, Foo);

    ecs_add_pair(world, e1, RelA, ObjA);
    ecs_add_pair(world, e1, RelB, ObjA);

    ecs_add_pair(world, e2, RelA, ObjA);

    ecs_add_pair(world, e3, RelA, ObjB);
    ecs_add_pair(world, e3, RelB, ObjB);

    ecs_add_pair(world, e4, RelA, ObjB);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, ObjA));

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e4);
    test_uint(ecs_field_id(&it, 1), Foo);
    test_uint(ecs_field_id(&it, 2), ecs_pair(RelA, ObjB));

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_rematch(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base_1);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], base_1);
    test_uint(it.entities[1], base_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 30);
    test_int(p[1].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_uint(it.sources[0], base_1);
    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, inst, EcsIsA, base_1);
    ecs_add_pair(world, inst, EcsIsA, base_2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], base_1);
    test_uint(it.entities[1], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 30);
    test_int(p[1].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_uint(it.sources[0], base_2);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_rematch(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base_1);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(up)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_uint(it.sources[0], base_1);
    test_bool(false, ecs_query_next(&it));

    ecs_add_pair(world, inst, EcsChildOf, base_2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_uint(it.sources[0], base_2);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_unmatch(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base_1);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], base_1);
    test_uint(it.entities[1], base_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 30);
    test_int(p[1].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_uint(it.sources[0], base_1);
    test_bool(false, ecs_query_next(&it));

    ecs_remove(world, base_1, Position);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_unmatch(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base_1);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(up)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_uint(it.sources[0], base_1);
    test_bool(false, ecs_query_next(&it));

    ecs_remove(world, base_1, Position);

    it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_isa_rematch_2_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t base = ecs_new_w_pair(world, EcsIsA, base_1);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], base_1);
    test_uint(it.entities[1], base_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 30);
    test_int(p[1].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], base_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, base, EcsIsA, base_1);
    ecs_add_pair(world, base, EcsIsA, base_2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], base_1);
    test_uint(it.entities[1], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 30);
    test_int(p[1].y, 40);
    test_uint(it.sources[0], 0);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_rematch_2_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t base = ecs_new_w_pair(world, EcsChildOf, base_1);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(up)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], base_1);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_add_pair(world, base, EcsChildOf, base_2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], base);
    test_uint(it.sources[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_rematch_2_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_0 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e_1 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t e_2 = ecs_set(world, 0, Position, {50, 60});
    ecs_entity_t e_3 = ecs_set(world, 0, Position, {70, 80});
    ecs_add_pair(world, e_3, EcsChildOf, e_2);

    ecs_add_pair(world, e_2, EcsChildOf, e_1);
    ecs_add_pair(world, e_1, EcsChildOf, e_0);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(cascade)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_0);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_3);
    test_uint(it.sources[0], e_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);
    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, e_1, EcsChildOf, EcsWildcard);
    ecs_remove_pair(world, e_2, EcsChildOf, EcsWildcard);
    ecs_remove_pair(world, e_3, EcsChildOf, EcsWildcard);

    ecs_add_pair(world, e_0, EcsChildOf, e_1);
    ecs_add_pair(world, e_1, EcsChildOf, e_2);
    ecs_add_pair(world, e_2, EcsChildOf, e_3);


    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_3);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 70);
    test_int(p[0].y, 80);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_0);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_rematch_2_lvls_2_relations(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, R, EcsTraversable);
    ECS_COMPONENT(world, Position);

    ecs_entity_t e_0 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e_1 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t e_2 = ecs_set(world, 0, Position, {50, 60});
    ecs_entity_t e_3 = ecs_set(world, 0, Position, {70, 80});

    ecs_add_pair(world, e_3, R, e_2);
    ecs_add_pair(world, e_2, R, e_1);
    ecs_add_pair(world, e_1, R, e_0);

    ecs_entity_t t = ecs_new_id(world);
    ecs_add(world, t, Position);
    ecs_add_pair(world, t, R, e_2);
    ecs_add_pair(world, t, R, e_1);
    ecs_delete(world, t);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(cascade(R))"
});

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_0);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_3);
    test_uint(it.sources[0], e_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_topological(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, R, Traversable);
    ECS_TAG(world, Tag);

    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_entity_t e3 = ecs_new(world, Tag);
    ecs_entity_t e4 = ecs_new(world, Tag);
    ecs_entity_t e5 = ecs_new(world, Tag);
    ecs_entity_t e6 = ecs_new(world, Tag);

    ecs_add_pair(world, e3, R, e1);
    ecs_add_pair(world, e3, R, e2);
    ecs_add_pair(world, e3, R, e4);
    ecs_add_pair(world, e1, R, e5);
    ecs_add_pair(world, e2, R, e6);
    ecs_add_pair(world, e4, R, e1);
    ecs_add_pair(world, e4, R, e2);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Tag, ?Tag(cascade(R))"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(it.entities[0], e5);
    test_uint(it.entities[1], e6);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e2);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e4);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e3);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_desc_rematch_2_lvls(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_0 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e_1 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t e_2 = ecs_set(world, 0, Position, {50, 60});
    ecs_entity_t e_3 = ecs_set(world, 0, Position, {70, 80});
    
    ecs_add_pair(world, e_3, EcsChildOf, e_2);
    ecs_add_pair(world, e_2, EcsChildOf, e_1);
    ecs_add_pair(world, e_1, EcsChildOf, e_0);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(cascade|desc)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_3);
    test_uint(it.sources[0], e_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_0);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);

    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, e_1, EcsChildOf, EcsWildcard);
    ecs_remove_pair(world, e_2, EcsChildOf, EcsWildcard);
    ecs_remove_pair(world, e_3, EcsChildOf, EcsWildcard);

    ecs_add_pair(world, e_0, EcsChildOf, e_1);
    ecs_add_pair(world, e_1, EcsChildOf, e_2);
    ecs_add_pair(world, e_2, EcsChildOf, e_3);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_0);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_3);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 70);
    test_int(p[0].y, 80);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_desc_rematch_2_lvls_2_relations(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, R, EcsTraversable);
    ECS_COMPONENT(world, Position);

    ecs_entity_t e_0 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t e_1 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t e_2 = ecs_set(world, 0, Position, {50, 60});
    ecs_entity_t e_3 = ecs_set(world, 0, Position, {70, 80});

    ecs_add_pair(world, e_3, R, e_2);
    ecs_add_pair(world, e_2, R, e_1);
    ecs_add_pair(world, e_1, R, e_0);

    ecs_entity_t t = ecs_new_id(world);
    ecs_add(world, t, Position);
    ecs_add_pair(world, t, R, e_2);
    ecs_add_pair(world, t, R, e_1);
    ecs_delete(world, t);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(cascade|desc(R))"
});

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_3);
    test_uint(it.sources[0], e_2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 50);
    test_int(p[0].y, 60);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_2);
    test_uint(it.sources[0], e_1);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e_1);
    test_uint(it.sources[0], e_0);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_cascade_desc_topological(void) {
    ecs_world_t *world = ecs_mini();

    ECS_ENTITY(world, R, Traversable);
    ECS_TAG(world, Tag);

    ecs_entity_t e1 = ecs_new(world, Tag);
    ecs_entity_t e2 = ecs_new(world, Tag);
    ecs_entity_t e3 = ecs_new(world, Tag);
    ecs_entity_t e4 = ecs_new(world, Tag);
    ecs_entity_t e5 = ecs_new(world, Tag);
    ecs_entity_t e6 = ecs_new(world, Tag);

    ecs_add_pair(world, e3, R, e1);
    ecs_add_pair(world, e3, R, e2);
    ecs_add_pair(world, e3, R, e4);
    ecs_add_pair(world, e1, R, e5);
    ecs_add_pair(world, e2, R, e6);
    ecs_add_pair(world, e4, R, e1);
    ecs_add_pair(world, e4, R, e2);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Tag, ?Tag(cascade|desc(R))"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e3);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e4);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e1);

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(it.entities[0], e2);

    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(it.entities[0], e5);
    test_uint(it.entities[1], e6);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_childof_rematch_from_isa(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ecs_entity_t base_1 = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t base_2 = ecs_set(world, 0, Position, {30, 40});
    ecs_entity_t base = ecs_new_w_pair(world, EcsIsA, base_1);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsChildOf, base);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Position(up)"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_1);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_remove_pair(world, base, EcsIsA, base_1);
    ecs_add_pair(world, base, EcsIsA, base_2);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_uint(it.sources[0], base_2);
    p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 30);
    test_int(p[0].y, 40);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_optional_ref(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Position);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Tag, ?Position(up)"
});
    test_assert(q != NULL);

    ecs_entity_t parent = ecs_set(world, 0, Position, {10, 20});
    ecs_entity_t child = ecs_new(world, Tag);
    ecs_add_pair(world, child, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(ecs_id(Position), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_uint(0, it.sources[0]);
    test_uint(parent, it.sources[1]);
    Position *p = ecs_field(&it, Position, 2);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_remove(world, parent, Position);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(ecs_id(Position), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(false, ecs_field_is_set(&it, 2));
    test_uint(0, it.sources[0]);
    test_uint(0, it.sources[1]);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_optional_ref_w_2_refs(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Tag);
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Tag, Velocity(up), ?Position(up)"
});
    test_assert(q != NULL);

    ecs_entity_t parent = ecs_set(world, 0, Position, {10, 20});
    ecs_set(world, parent, Velocity, {1, 2});
    ecs_entity_t child = ecs_new(world, Tag);
    ecs_add_pair(world, child, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_uint(ecs_id(Position), ecs_field_id(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 3));
    test_uint(0, it.sources[0]);
    test_uint(parent, it.sources[1]);
    Velocity *v = ecs_field(&it, Velocity, 2);
    test_assert(v != NULL);
    test_int(v->x, 1);
    test_int(v->y, 2);
    Position *p = ecs_field(&it, Position, 3);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_remove(world, parent, Position);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    test_uint(ecs_id(Position), ecs_field_id(&it, 3));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(false, ecs_field_is_set(&it, 3));
    test_uint(0, it.sources[0]);
    test_uint(parent, it.sources[1]);
    test_uint(0, it.sources[2]);
    v = ecs_field(&it, Velocity, 2);
    test_assert(v != NULL);
    test_int(v->x, 1);
    test_int(v->y, 2);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_optional_ref_tag_w_ref_component(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TagA);
    ECS_TAG(world, TagB);

    ecs_query_t *q = ecs_query(world, {
    .expr = "TagA, ?Position(up), TagB(up)"
});
    test_assert(q != NULL);

    ecs_entity_t parent = ecs_set(world, 0, Position, {10, 20});
    ecs_add(world, parent, TagB);

    ecs_entity_t child = ecs_new(world, TagA);
    ecs_add_pair(world, child, EcsChildOf, parent);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_uint(ecs_id(Position), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(true, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 3));
    test_uint(0, it.sources[0]);
    test_uint(parent, it.sources[1]);
    test_uint(parent, it.sources[2]);
    Position *p = ecs_field(&it, Position, 2);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_bool(false, ecs_query_next(&it));

    ecs_remove(world, parent, Position);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(child, it.entities[0]);
    test_uint(TagA, ecs_field_id(&it, 1));
    test_uint(ecs_id(Position), ecs_field_id(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 1));
    test_bool(false, ecs_field_is_set(&it, 2));
    test_bool(true, ecs_field_is_set(&it, 3));
    test_uint(0, it.sources[0]);
    test_uint(0, it.sources[1]);
    test_uint(parent, it.sources[2]);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_match_query_expr_from_scope(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t foo = ecs_entity_init(world, &(ecs_entity_desc_t){
        .name = "Foo"
    });

    ecs_entity_t bar = ecs_entity_init(world, &(ecs_entity_desc_t){
        .name = "Foo.Bar"
    });

    ecs_set_scope(world, foo);

    ecs_query_t *q = ecs_query(world, {
    .expr = "Bar"
});
    test_assert(q != NULL);

    ecs_set_scope(world, 0);

    ecs_entity_t e = ecs_new_w_id(world, bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(bar, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_long_or_w_ref(void) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    ECS_TAG(world, A);
    ECS_TAG(world, B);
    ECS_TAG(world, C);
    ECS_TAG(world, D);
    ECS_TAG(world, E);
    ECS_TAG(world, F);
    ECS_TAG(world, G);
    ECS_TAG(world, H);
    ECS_TAG(world, I);
    ECS_TAG(world, J);
    ECS_TAG(world, K);
    ECS_TAG(world, L);
    ECS_TAG(world, M);
    ECS_TAG(world, N);

    ecs_entity_t e = ecs_new_entity(world, "e");
    ecs_set(world, e, Position, {10, 20});

    ecs_entity_t e2 = ecs_new(world, A);

    ecs_query_t *q = ecs_query(world, {
       .expr = 
        "Position(e), A || B || C || D || E || F || G || H || I || J || K || L ||"
        "M || N"
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(A, ecs_field_id(&it, 2));
    test_uint(e2, it.entities[0]);
    test_uint(e, it.sources[0]);
    test_uint(0, it.sources[1]);

    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_0_query(void) {
    ecs_world_t *world = ecs_mini();

    ecs_query_t *q = ecs_query(world, {
    .expr = "0"
});
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_w_pair_id_and_subj(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Rel);
    ECS_TAG(world, Obj);
    ECS_TAG(world, Subj);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{
            .id = ecs_pair(Rel, Obj), .src.id = Subj
        }}
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_add_pair(world, Subj, Rel, Obj);

    it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 0);
    test_uint(it.sources[0], Subj);
    test_uint(it.ids[0], ecs_pair(Rel, Obj));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_after_delete_inherited_tag(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t tag = ecs_new_id(world);
    ecs_entity_t base = ecs_new_w_id(world, tag);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = tag }
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(base, it.entities[0]);
    test_uint(tag, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(inst, it.entities[0]);
    test_uint(tag, ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_delete_with(world, tag);

    it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_after_delete_rel_of_inherited_pair(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t rel = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);
    ecs_entity_t base = ecs_new_w_pair(world, rel, obj);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_pair(rel, obj) }
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(base, it.entities[0]);
    test_uint(ecs_pair(rel, obj), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(inst, it.entities[0]);
    test_uint(ecs_pair(rel, obj), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_delete_with(world, ecs_pair(rel, EcsWildcard));

    it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_after_delete_obj_of_inherited_pair(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t rel = ecs_new_id(world);
    ecs_entity_t obj = ecs_new_id(world);
    ecs_entity_t base = ecs_new_w_pair(world, rel, obj);
    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);

    ecs_query_t *q = ecs_query(world, {
        .terms = {
            { .id = ecs_pair(rel, obj) }
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(base, it.entities[0]);
    test_uint(ecs_pair(rel, obj), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(inst, it.entities[0]);
    test_uint(ecs_pair(rel, obj), ecs_field_id(&it, 1));
    test_bool(false, ecs_query_next(&it));

    ecs_delete_with(world, ecs_pair(EcsWildcard, obj));

    it = ecs_query_iter(world, q);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_rematch_empty_table_w_superset(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{ Foo }, { Bar, .oper = EcsNot }}
    });

    ecs_entity_t base = ecs_new_w_id(world, EcsPrefab);
    ecs_add(world, base, Foo);
    test_assert( ecs_is_alive(world, base));

    ecs_delete_with(world, Foo);
    test_assert( !ecs_is_alive(world, base));

    base = ecs_new_w_id(world, EcsPrefab);
    ecs_add(world, base, Foo);

    ecs_entity_t inst = ecs_new_w_pair(world, EcsIsA, base);
    ecs_add(world, inst, Bar);

    ecs_run_aperiodic(world, 0); // force table (IsA, base) to empty list

    ecs_remove(world, inst, Bar);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], inst);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_w_short_notation(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);

    ecs_query_t *q = ecs_query(world, {
        .terms = {{
            .id = Foo
        }}
    });

    test_assert(q != NULL);

    ecs_entity_t e = ecs_new(world, Foo);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_assert(ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e);
    test_uint(it.ids[0], ecs_field_id(&it, 1));
    test_assert(!ecs_query_next(&it));

    ecs_query_fini(q);

    ecs_fini(world);
}

void Cached_query_w_invalid_filter_flag(void) {
    install_test_abort();

    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, Position);

    test_expect_abort();
    ecs_query(world, {
        .terms = {
            { .inout = EcsInOutFilter, .id = ecs_id(Position) }
        }
    });
}

void Cached_create_query_existing_query_entity(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *q_1 = ecs_query(world, {
        .entity = ecs_entity(world, { .name = "q" }),
        .terms = {
            { .id = Foo },
            { .id = Bar }
        },
    });

    test_assert(q_1 != NULL);

    ecs_query_t *q_2 = ecs_query(world, {
        .entity = ecs_entity(world, { .name = "q" }),
        .terms = {
            { .id = Foo },
            { .id = Bar }
        },
    });

    test_assert(q_2 != NULL);

    ecs_fini(world);
}

void Cached_query_for_recycled_pair(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t rel = ecs_new_entity(world, "Rel");
    ecs_entity_t tgt = ecs_new_entity(world, "Tgt");
    ecs_delete(world, rel);
    ecs_delete(world, tgt);
    rel = ecs_new_entity(world, "Rel");
    tgt = ecs_new_entity(world, "Tgt");

    ecs_entity_t e = ecs_new_w_pair(world, rel, tgt);

    ecs_query_t *q = ecs_query(world, {
        .terms[0] = {
            .first.id = rel,
            .second.id = tgt
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(world, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e);
    test_uint(ecs_field_id(&it, 1), ecs_pair(rel, tgt));
    test_bool(false, ecs_query_next(&it));

    ecs_fini(world);
}

void Cached_query_w_singleton_w_rule_iter(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_TAG(ecs, Tag);
    ECS_TAG(ecs, Singleton);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            {Singleton, .src.id = Singleton}, {Tag}
        }
    });

    ecs_query_t *r = ecs_query(ecs, {
        .terms = {{Tag}}
    });

    ecs_singleton_add(ecs, Singleton);
    ecs_entity_t e = ecs_new(ecs, Tag);

    ecs_iter_t qit = ecs_query_iter(ecs, q);
    test_bool(true, ecs_query_next(&qit));
    test_int(1, qit.count);
    test_uint(e, qit.entities[0]);

    ecs_id_t id = qit.ids[0];
    ecs_iter_t rit = ecs_query_iter(ecs, r);
    test_bool(true, ecs_query_next(&rit));
    test_int(1, rit.count);
    test_uint(e, rit.entities[0]);
    test_bool(false, ecs_query_next(&rit));
    test_assert(id == qit.ids[0]);
    test_bool(false, ecs_query_next(&qit));

    ecs_query_fini(r);

    ecs_fini(ecs);
}

void Cached_query_w_singleton_nested_iter(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_TAG(ecs, TagA);
    ECS_TAG(ecs, TagB);
    ECS_TAG(ecs, Singleton);

    ecs_query_t *qa = ecs_query(ecs, {
        .terms = {
            {TagA}, {Singleton, .src.id = Singleton}
        }
    });

    ecs_query_t *qb = ecs_query(ecs, {
        .terms = {
            {TagB}, {Singleton, .src.id = Singleton}
        }
    });

    ecs_singleton_add(ecs, Singleton);

    ecs_entity_t ea = ecs_new(ecs, TagA);
    ecs_entity_t eb = ecs_new(ecs, TagB);

    ecs_iter_t qita = ecs_query_iter(ecs, qa);
    ecs_iter_t qitb = ecs_query_iter(ecs, qb);

    test_bool(ecs_query_next(&qita), true);
    test_int(1, qita.count);
    test_uint(ea, qita.entities[0]);

    test_bool(ecs_query_next(&qitb), true);
    test_int(1, qitb.count);
    test_uint(eb, qitb.entities[0]);

    test_uint(TagA, qita.ids[0]);
    test_uint(TagB, qitb.ids[0]);

    test_bool(ecs_query_next(&qita), false);
    test_bool(ecs_query_next(&qitb), false);

    ecs_fini(ecs);
}

void Cached_query_w_singleton_interleaved_iter(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_TAG(ecs, TagA);
    ECS_TAG(ecs, TagB);
    ECS_TAG(ecs, TagC);
    ECS_TAG(ecs, Singleton);

    ecs_query_t *qa = ecs_query(ecs, {
        .terms = {
            {TagA}, {Singleton, .src.id = Singleton}
        }
    });

    ecs_query_t *qb = ecs_query(ecs, {
        .terms = {
            {TagB}, {Singleton, .src.id = Singleton}
        }
    });

    ecs_query_t *qc = ecs_query(ecs, {
        .terms = {
            {TagC}, {Singleton, .src.id = Singleton}
        }
    });

    ecs_singleton_add(ecs, Singleton);

    ecs_entity_t ea = ecs_new(ecs, TagA);
    ecs_entity_t eb = ecs_new(ecs, TagB);
    ecs_entity_t ec = ecs_new(ecs, TagC);

    ecs_iter_t qita = ecs_query_iter(ecs, qa);
    ecs_iter_t qitb = ecs_query_iter(ecs, qb);

    test_bool(ecs_query_next(&qita), true);
    test_int(1, qita.count);
    test_uint(ea, qita.entities[0]);

    test_bool(ecs_query_next(&qitb), true);
    test_int(1, qitb.count);
    test_uint(eb, qitb.entities[0]);

    test_uint(TagA, qita.ids[0]);
    test_uint(TagB, qitb.ids[0]);

    test_bool(ecs_query_next(&qita), false);

    ecs_iter_t qitc = ecs_query_iter(ecs, qc);
    test_bool(ecs_query_next(&qitc), true);
    test_int(1, qitc.count);
    test_uint(ec, qitc.entities[0]);

    test_uint(TagB, qitb.ids[0]);
    test_uint(TagC, qitc.ids[0]);

    test_bool(ecs_query_next(&qitb), false);
    test_bool(ecs_query_next(&qitc), false);

    ecs_fini(ecs);
}

void Cached_recycled_component_id(void) {
    ecs_world_t* ecs = ecs_mini();

    for (int i = 0; i < FLECS_HI_COMPONENT_ID; i ++) {
        ecs_new_low_id(ecs);
    }

    ecs_entity_t e = ecs_new_id(ecs);
    ecs_delete(ecs, e);

    ECS_COMPONENT(ecs, Position);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(ecs, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(ecs, 0, Position, {20, 30});

    ecs_iter_t it = ecs_query_iter(ecs, q);
    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 2);
    test_uint(it.entities[0], e1);
    test_uint(it.entities[1], e2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 10);
    test_int(p[0].y, 20);
    test_int(p[1].x, 20);
    test_int(p[1].y, 30);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_set_get_context(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);

    int ctx = 0;

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        },
        .ctx = &ctx
    });
    test_assert(q != NULL);

    test_assert(q->ctx == &ctx);
    test_assert(q->binding_ctx == NULL);

    ecs_fini(ecs);
}

void Cached_set_get_binding_context(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);

    int ctx = 0;

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        },
        .binding_ctx = &ctx
    });
    test_assert(q != NULL);

    test_assert(q->binding_ctx == &ctx);
    test_assert(q->ctx == NULL);

    ecs_fini(ecs);
}

static void ctx_free(void *ptr) {
    *(int*)ptr = 10;
}

void Cached_set_get_context_w_free(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);

    int ctx = 0;

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        },
        .ctx = &ctx,
        .ctx_free = ctx_free
    });
    test_assert(q != NULL);

    test_assert(q->ctx == &ctx);
    test_assert(q->binding_ctx == NULL);
    test_int(ctx, 0);

    ecs_query_fini(q);

    test_int(ctx, 10);

    ecs_fini(ecs);
}

void Cached_set_get_binding_context_w_free(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);

    int ctx = 0;

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        },
        .binding_ctx = &ctx,
        .binding_ctx_free = ctx_free
    });
    test_assert(q != NULL);

    test_assert(q->binding_ctx == &ctx);
    test_assert(q->ctx == NULL);
    test_int(ctx, 0);

    ecs_query_fini(q);

    test_int(ctx, 10);

    ecs_fini(ecs);
}

void Cached_set_this(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        }
    });
    test_assert(q != NULL);

    /* ecs_entity_t e1 = */ ecs_set(ecs, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(ecs, 0, Position, {20, 30});
    /* ecs_entity_t e3 = */ ecs_set(ecs, 0, Position, {30, 40});

    ecs_iter_t it = ecs_query_iter(ecs, q);
    ecs_iter_set_var(&it, 0, e2);

    test_bool(true, ecs_query_next(&it));
    test_int(it.count, 1);
    test_uint(it.entities[0], e2);
    Position *p = ecs_field(&it, Position, 1);
    test_int(p[0].x, 20);
    test_int(p[0].y, 30);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_set_this_no_match(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        }
    });
    test_assert(q != NULL);

    /* ecs_entity_t e1 = */ ecs_set(ecs, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(ecs, 0, Velocity, {20, 30});
    /* ecs_entity_t e3 = */ ecs_set(ecs, 0, Position, {30, 40});

    ecs_iter_t it = ecs_query_iter(ecs, q);
    ecs_iter_set_var(&it, 0, e2);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_set_this_is_true(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) }
        }
    });
    test_assert(q != NULL);

    /* ecs_entity_t e1 = */ ecs_set(ecs, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(ecs, 0, Position, {20, 30});
    /* ecs_entity_t e3 = */ ecs_set(ecs, 0, Position, {30, 40});
    ecs_entity_t e4 = ecs_set(ecs, 0, Velocity, {20, 30});

    ecs_iter_t it = ecs_query_iter(ecs, q);
    ecs_iter_set_var(&it, 0, e2);
    test_bool(true, ecs_iter_is_true(&it));

    it = ecs_query_iter(ecs, q);
    ecs_iter_set_var(&it, 0, e4);
    test_bool(false, ecs_iter_is_true(&it));

    ecs_fini(ecs);
}

void Cached_set_this_w_wildcard(void) {
    ecs_world_t* ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_TAG(ecs, Likes);
    ECS_TAG(ecs, Apples);
    ECS_TAG(ecs, Pears);

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) },
            { .id = ecs_pair(Likes, EcsWildcard) }
        }
    });
    test_assert(q != NULL);

    ecs_entity_t e1 = ecs_set(ecs, 0, Position, {10, 20});
    ecs_entity_t e2 = ecs_set(ecs, 0, Position, {20, 30});
    ecs_entity_t e3 = ecs_set(ecs, 0, Position, {30, 40});

    ecs_add_pair(ecs, e1, Likes, Apples);
    ecs_add_pair(ecs, e2, Likes, Apples);
    ecs_add_pair(ecs, e3, Likes, Apples);

    ecs_add_pair(ecs, e1, Likes, Pears);
    ecs_add_pair(ecs, e2, Likes, Pears);
    ecs_add_pair(ecs, e3, Likes, Pears);

    ecs_iter_t it = ecs_query_iter(ecs, q);
    ecs_iter_set_var(&it, 0, e2);

    {
        test_bool(true, ecs_query_next(&it));
        test_int(it.count, 1);
        test_uint(it.entities[0], e2);
        Position *p = ecs_field(&it, Position, 1);
        test_int(p[0].x, 20);
        test_int(p[0].y, 30);
        test_uint(ecs_pair(Likes, Apples), ecs_field_id(&it, 2));
    }
    {
        test_bool(true, ecs_query_next(&it));
        test_int(it.count, 1);
        test_uint(it.entities[0], e2);
        Position *p = ecs_field(&it, Position, 1);
        test_int(p[0].x, 20);
        test_int(p[0].y, 30);
        test_uint(ecs_pair(Likes, Pears), ecs_field_id(&it, 2));
    }

    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_singleton_w_inout_none(void) {
    ecs_world_t *ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);
    
    ecs_singleton_set(ecs, Position, {10, 20});

    ecs_entity_t e = ecs_set(ecs, 0, Velocity, {20, 30});

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position), .src.id = EcsVariable },
            { .id = ecs_id(Velocity), .inout = EcsInOutNone },
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(ecs, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    Position *p = ecs_field(&it, Position, 1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_assert(ecs_field(&it, Velocity, 2) == NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_singleton_w_inout_none_or(void) {
    ecs_world_t *ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);
    ECS_COMPONENT(ecs, Mass);

    ecs_singleton_set(ecs, Position, {10, 20});

    ecs_entity_t e = ecs_set(ecs, 0, Velocity, {20, 30});

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position), .src.id = EcsVariable },
            { .id = ecs_id(Velocity), .inout = EcsInOutNone, .oper = EcsOr },
            { .id = ecs_id(Mass), .inout = EcsInOutNone },
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(ecs, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    Position *p = ecs_field(&it, Position, 1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_assert(ecs_field(&it, Velocity, 2) == NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_component_w_inout_none_or(void) {
    ecs_world_t *ecs = ecs_mini();

    ECS_COMPONENT(ecs, Position);
    ECS_COMPONENT(ecs, Velocity);
    ECS_COMPONENT(ecs, Mass);

    ecs_entity_t e = ecs_set(ecs, 0, Velocity, {20, 30});
    ecs_set(ecs, e, Position, {10, 20});

    ecs_query_t *q = ecs_query(ecs, {
        .terms = {
            { .id = ecs_id(Position) },
            { .id = ecs_id(Velocity), .inout = EcsInOutNone, .oper = EcsOr },
            { .id = ecs_id(Mass), .inout = EcsInOutNone },
        }
    });
    test_assert(q != NULL);

    ecs_iter_t it = ecs_query_iter(ecs, q);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e, it.entities[0]);
    test_uint(ecs_id(Position), ecs_field_id(&it, 1));
    test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
    Position *p = ecs_field(&it, Position, 1);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);
    test_assert(ecs_field(&it, Velocity, 2) == NULL);
    test_bool(false, ecs_query_next(&it));

    ecs_fini(ecs);
}

void Cached_2_self_up_terms_new_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Tag, Foo(self|up(IsA))",
        .cache_kind = EcsQueryCacheAuto
    });

    test_assert(r != NULL);

    ecs_set_with(world, Tag);
    ecs_entity_t parent_a = ecs_new_id(world);
    ecs_entity_t parent_b = ecs_new(world, Foo);
    ecs_new_w_pair(world, EcsIsA, parent_a);
    ecs_entity_t e_2 = ecs_new_w_pair(world, EcsIsA, parent_b);
    ecs_entity_t e_3 = ecs_new_w_pair(world, EcsIsA, e_2);
    ecs_set_with(world, 0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(parent_b, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e_2, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(parent_b, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e_3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(parent_b, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cached_this_self_up_childof_pair_new_tables(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Bar);
    ECS_TAG(world, Rel);
    ECS_TAG(world, Tgt);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Rel(self|up, Tgt)",
        .cache_kind = EcsQueryCacheAuto
    });

    test_assert(r != NULL);

    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new_w_pair(world, Rel, Tgt);
    ecs_entity_t p2 = ecs_new_w_pair(world, Rel, Tgt);
    ecs_entity_t p3 = ecs_new_w_pair(world, Rel, Tgt);
    ecs_add(world, p3, Bar);

    ecs_entity_t e1 = ecs_new_w_pair(world, EcsChildOf, p1);
    ecs_entity_t e2 = ecs_new_w_pair(world, EcsChildOf, p1);
    ecs_add(world, e2, Bar);

    ecs_entity_t e3 = ecs_new_w_pair(world, EcsChildOf, p2);
    ecs_entity_t e4 = ecs_new_w_pair(world, EcsChildOf, p2);
    ecs_add(world, e4, Bar);

    ecs_entity_t e5 = ecs_new_w_pair(world, EcsChildOf, e2);
    ecs_entity_t e6 = ecs_new_w_pair(world, EcsChildOf, e2);
    ecs_add(world, e6, Bar);

    ecs_entity_t e7 = ecs_new_w_pair(world, EcsChildOf, p3);

    ecs_new_w_pair(world, EcsChildOf, p0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(p1, it.entities[0]);
    test_uint(p2, it.entities[1]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(p3, ecs_field_src(&it, 1));
    test_uint(ecs_pair(Rel, Tgt), ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cached_query_from_entity_or_change(void) {
    // Implement testcase
}

void Cached_query_2_or(void) {
    // Implement testcase
}

void Cached_query_single_pairs(void) {
    // Implement testcase
}

void Cached_query_optional_owned(void) {
    // Implement testcase
}

void Cached_query_optional_shared(void) {
    // Implement testcase
}

void Cached_query_optional_shared_nested(void) {
    // Implement testcase
}

void Cached_query_optional_any(void) {
    // Implement testcase
}

void Cached_query_w_from_nothing(void) {
    // Implement testcase
}

void Cached_query_only_2_or(void) {
    // Implement testcase
}

void Cached_query_only_3_or(void) {
    // Implement testcase
}

void Cached_query_3_or(void) {
    // Implement testcase
}
