#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

static int compare(const void *const a, const void *const b) {
    const struct sea_turtle_string *const A
            = (const struct sea_turtle_string *) a;
    const struct sea_turtle_string *const B
            = (const struct sea_turtle_string *) b;
    return sea_turtle_string_compare(A, B);
}

static void init(struct seahorse_red_black_tree_set_s *const object) {
    assert(object);
    *object = (struct seahorse_red_black_tree_set_s) {0};
    seagrass_required_true(coral_red_black_tree_set_init(
            &object->set,
            sizeof(struct sea_turtle_string),
            compare));
}

bool seahorse_red_black_tree_set_s_init(
        struct seahorse_red_black_tree_set_s *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    init(object);
    return true;
}

static void on_destroy(void *a) {
    seagrass_required_true(sea_turtle_string_invalidate(a));
}

static void invalidate(struct seahorse_red_black_tree_set_s *const object) {
    assert(object);
    seagrass_required_true(coral_red_black_tree_set_invalidate(
            &object->set, on_destroy));
    *object = (struct seahorse_red_black_tree_set_s) {0};
}

bool seahorse_red_black_tree_set_s_invalidate(
        struct seahorse_red_black_tree_set_s *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    invalidate(object);
    return true;
}

bool seahorse_red_black_tree_set_s_init_red_black_tree_set_s(
        struct seahorse_red_black_tree_set_s *const object,
        const struct seahorse_red_black_tree_set_s *const other) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OTHER_IS_NULL;
        return false;
    }
    init(object);
    const struct sea_turtle_string *item;
    if (!seahorse_red_black_tree_set_s_first(other, &item)) {
        seagrass_required_true(
                SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY
                == seahorse_error);
        return true;
    }
    do {
        if (!seahorse_red_black_tree_set_s_add(object, item)) {
            seagrass_required_true(
                    SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED
                    == seahorse_error);
            invalidate(object);
            return false;
        }
    } while (seahorse_red_black_tree_set_s_next(item, &item));
    seagrass_required_true(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE
            == seahorse_error);
    return true;
}

bool seahorse_red_black_tree_set_s_count(
        const struct seahorse_red_black_tree_set_s *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_set_count(
            &object->set, out));
    return true;
}

bool seahorse_red_black_tree_set_s_add(
        struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    bool result;
    if (!coral_red_black_tree_set_contains(&object->set, value, &result)) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    } else if (result) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_ALREADY_EXISTS;
        return false;
    }
    struct sea_turtle_string copy;
    if (!sea_turtle_string_init_string(&copy, value)
        || !coral_red_black_tree_set_add(&object->set, &copy)) {
        seagrass_required_true(
                SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                == sea_turtle_error
                || CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                   == coral_error);
        seagrass_required_true(sea_turtle_string_invalidate(&copy));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    return true;
}

bool seahorse_red_black_tree_set_s_remove(
        struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_string *out;
    if (!coral_red_black_tree_set_get(&object->set, value,
                                      (const void **) &out)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        return false;
    }
    on_destroy(out);
    seagrass_required_true(coral_red_black_tree_set_remove_item(
            &object->set, out));
    return true;
}

bool seahorse_red_black_tree_set_s_contains(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_set_contains(
            &object->set, value, out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

static bool retrieve(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, value, (const void **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_set_s_get(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_get);
}

bool seahorse_red_black_tree_set_s_ceiling(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_ceiling);
}

bool seahorse_red_black_tree_set_s_floor(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_floor);
}

bool seahorse_red_black_tree_set_s_higher(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_higher);
}

bool seahorse_red_black_tree_set_s_lower(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string *const value,
        const struct sea_turtle_string **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_SET_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_set_s_first(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_first);
}

bool seahorse_red_black_tree_set_s_last(
        const struct seahorse_red_black_tree_set_s *const object,
        const struct sea_turtle_string **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_last);
}

bool seahorse_red_black_tree_set_s_remove_item(
        struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *item) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL;
        return false;
    }
    on_destroy((void *)item);
    seagrass_required_true(coral_red_black_tree_set_remove_item(
            &object->set, item));
    return true;
}

static bool retrieve_np(const struct sea_turtle_string *const item,
                        const struct sea_turtle_string **const out,
                        bool (*const func)(const void *, const void **)) {
    assert(func);
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(item, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_set_s_next(
        const struct sea_turtle_string *const item,
        const struct sea_turtle_string **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_next);
}

bool seahorse_red_black_tree_set_s_prev(
        const struct sea_turtle_string *const item,
        const struct sea_turtle_string **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_prev);
}

