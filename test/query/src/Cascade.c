#include <query.h>

void Cascade_this_self_cascade_childof_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self|cascade)",
    });

    test_assert(r != NULL);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(p1, it.entities[0]);
    test_uint(p2, it.entities[1]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(p3, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_cascade_childof_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(cascade)",
    });

    test_assert(r != NULL);

    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(p3, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_written_self_cascade_childof_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Tag(self), Foo(self|cascade)",
    });

    test_assert(r != NULL);

    ecs_set_with(world, Tag);
    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    ecs_set_with(world, 0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(p1, it.entities[0]);
    test_uint(p2, it.entities[1]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(0, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(0, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p3, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_written_cascade_childof_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Tag(self), Foo(cascade)",
    });

    test_assert(r != NULL);

    ecs_set_with(world, Tag);
    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    ecs_set_with(world, 0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p3, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_self_cascade_childof_w_parent_flag_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(self|cascade)",
    });

    test_assert(r != NULL);

    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(p3, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_cascade_childof_w_parent_flag_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Foo(cascade)",
    });

    test_assert(r != NULL);

    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(p1, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(p2, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(p3, ecs_field_src(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 1));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_written_self_cascade_childof_w_parent_flag_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Tag(self), Foo(self|cascade)",
    });

    test_assert(r != NULL);

    ecs_set_with(world, Tag);
    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    ecs_set_with(world, 0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(2, it.count);
    test_uint(p1, it.entities[0]);
    test_uint(p2, it.entities[1]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(0, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(p3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(0, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p3, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}

void Cascade_this_written_cascade_childof_w_parent_flag_uncached(void) {
    ecs_world_t *world = ecs_mini();

    ECS_TAG(world, Foo);
    ECS_TAG(world, Bar);
    ECS_TAG(world, Tag);

    ecs_query_t *r = ecs_query(world, {
        .expr = "Tag(self), Foo(cascade)",
    });

    test_assert(r != NULL);

    ecs_set_with(world, Tag);
    ecs_entity_t p0 = ecs_new_id(world);
    ecs_entity_t p1 = ecs_new(world, Foo);
    ecs_entity_t p2 = ecs_new(world, Foo);
    ecs_entity_t p3 = ecs_new(world, Foo);
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
    ecs_set_with(world, 0);

    ecs_iter_t it = ecs_query_iter(world, r);
    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e1, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e2, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e3, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e4, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p2, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e5, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e6, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p1, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(true, ecs_query_next(&it));
    test_int(1, it.count);
    test_uint(e7, it.entities[0]);
    test_uint(0, ecs_field_src(&it, 1));
    test_uint(p3, ecs_field_src(&it, 2));
    test_uint(Tag, ecs_field_id(&it, 1));
    test_uint(Foo, ecs_field_id(&it, 2));

    test_bool(false, ecs_query_next(&it));

    ecs_query_fini(r);

    ecs_fini(world);
}
