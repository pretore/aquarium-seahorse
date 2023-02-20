#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include "private/sorted_set_i.h"

#ifdef TEST
#include <test/cmocka.h>
#endif

#pragma mark stream_i -

static bool first(const void *const object,
                  const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_first(object, out);
}

static bool remove_item(void *const object,
                        const struct sea_turtle_integer *const item) {
    return seahorse_red_black_tree_set_i_remove_item(object, item);
}

static bool next(const void *const object,
                 const struct sea_turtle_integer *const item,
                 const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_next(item, out);
}

#pragma mark collection_i -

static bool count(const void *const object,
                  uintmax_t *const out) {
    return seahorse_red_black_tree_set_i_count(object, out);
}

static bool last(const void *const object,
                 const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_last(object, out);
}

static bool prev(const void *const object,
                 const struct sea_turtle_integer *const item,
                 const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_prev(item, out);
}

#pragma mark set_i -

static bool add(void *const object,
                const struct sea_turtle_integer *const value) {
    return seahorse_red_black_tree_set_i_add(object, value);
}

static bool remove(void *const object,
                   const struct sea_turtle_integer *const value) {
    return seahorse_red_black_tree_set_i_remove(object, value);
}

static bool contains(const void *const object,
                     const struct sea_turtle_integer *const value,
                     bool *const out) {
    return seahorse_red_black_tree_set_i_contains(object, value, out);
}

static bool get(const void *const object,
                const struct sea_turtle_integer *const value,
                const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_get(object, value, out);
}

#pragma mark ordered_set_i -
#pragma mark sorted_set_i -

static bool ceiling(const void *const object,
                    const struct sea_turtle_integer *const value,
                    const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_ceiling(object, value, out);
}

static bool floor(const void *const object,
                  const struct sea_turtle_integer *const value,
                  const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_floor(object, value, out);
}

static bool higher(const void *const object,
                   const struct sea_turtle_integer *const value,
                   const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_higher(object, value, out);
}

static bool lower(const void *const object,
                  const struct sea_turtle_integer *const value,
                  const struct sea_turtle_integer **const out) {
    return seahorse_red_black_tree_set_i_lower(object, value, out);
}

#pragma mark seahorse_red_black_tree_set_i -

static const struct seahorse_sorted_set_i sorted_set_i = {
        .ordered_set_i = {
                .set_i = {
                        .collection_i = {
                                .stream_i = {
                                        .first = first,
                                        .remove_item = remove_item,
                                        .next = next,
                                },
                                .count = count,
                                .last = last,
                                .prev = prev
                        },
                        .add = add,
                        .remove = remove,
                        .contains = contains,
                        .get = get,
                },
        },
        .ceiling = ceiling,
        .floor = floor,
        .higher = higher,
        .lower = lower,
};

static int compare(const void *const a, const void *const b) {
    const struct sea_turtle_integer *const A
            = (const struct sea_turtle_integer *) a;
    const struct sea_turtle_integer *const B
            = (const struct sea_turtle_integer *) b;
    return sea_turtle_integer_compare(A, B);
}

static void init(struct seahorse_red_black_tree_set_i *const object) {
    assert(object);
    *object = (struct seahorse_red_black_tree_set_i) {
            .sorted_set_i = &sorted_set_i
    };
    seagrass_required_true(coral_red_black_tree_set_init(
            &object->set,
            sizeof(struct sea_turtle_integer),
            compare));
}

bool seahorse_red_black_tree_set_i_init(
        struct seahorse_red_black_tree_set_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    init(object);
    return true;
}

static void on_destroy(void *a) {
    seagrass_required_true(sea_turtle_integer_invalidate(a));
}

static void invalidate(struct seahorse_red_black_tree_set_i *const object) {
    assert(object);
    seagrass_required_true(coral_red_black_tree_set_invalidate(
            &object->set, on_destroy));
    *object = (struct seahorse_red_black_tree_set_i) {0};
}

bool seahorse_red_black_tree_set_i_init_set_i(
        struct seahorse_red_black_tree_set_i *const object,
        const struct seahorse_stream_i *const other) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OTHER_IS_NULL;
        return false;
    }
    init(object);
    const struct sea_turtle_integer *integer;
    if (!seahorse_stream_i_first(other, &integer)) {
        seagrass_required_true(SEAHORSE_STREAM_I_ERROR_STREAM_IS_EMPTY
                               == seahorse_error);
        return true;
    }
    do {
        if (seahorse_red_black_tree_set_i_add(object, integer)) {
            continue;
        }
        switch (seahorse_error) {
            default: {
                seagrass_required_true(false);
            }
            case SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS: {
                continue;
            }
            case SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED: {
                return false;
            }
        }
    } while (seahorse_stream_i_next(other, integer, &integer));
    seagrass_required_true(SEAHORSE_STREAM_I_ERROR_END_OF_SEQUENCE
                           == seahorse_error);
    return true;
}

bool seahorse_red_black_tree_set_i_invalidate(
        struct seahorse_red_black_tree_set_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    invalidate(object);
    return true;
}

bool seahorse_red_black_tree_set_i_count(
        const struct seahorse_red_black_tree_set_i *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_set_count(
            &object->set, out));
    return true;
}

bool seahorse_red_black_tree_set_i_add(
        struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    bool result;
    if (!coral_red_black_tree_set_contains(&object->set, value, &result)) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    } else if (result) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS;
        return false;
    }
    struct sea_turtle_integer copy;
    result = sea_turtle_integer_init_integer(&copy, value)
             && coral_red_black_tree_set_add(&object->set, &copy);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seagrass_required_true(sea_turtle_integer_invalidate(&copy));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_red_black_tree_set_i_remove(
        struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_integer *out;
    if (!coral_red_black_tree_set_get(&object->set, value,
                                      (const void **) &out)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED;
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

bool seahorse_red_black_tree_set_i_contains(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_set_contains(
            &object->set, value, out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

static bool retrieve(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    if (func(&object->set, value, (const void **) out)) {
        return true;
    }
    switch (coral_error) {
        default: {
            seagrass_required_true(false);
        }
        case CORAL_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
            seahorse_error =
                    SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND;
            break;
        }
        case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
            seahorse_error =
                    SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED;
            break;
        }
    }
    return false;
}

bool seahorse_red_black_tree_set_i_get(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_get);
}

bool seahorse_red_black_tree_set_i_ceiling(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_ceiling);
}

bool seahorse_red_black_tree_set_i_floor(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_floor);
}

bool seahorse_red_black_tree_set_i_higher(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_higher);
}

bool seahorse_red_black_tree_set_i_lower(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_SET_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_set_i_first(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_first);
}

bool seahorse_red_black_tree_set_i_last(
        const struct seahorse_red_black_tree_set_i *const object,
        const struct sea_turtle_integer **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_last);
}

bool seahorse_red_black_tree_set_i_remove_item(
        struct seahorse_red_black_tree_set_i *object,
        const struct sea_turtle_integer *item) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    on_destroy((void *) item);
    seagrass_required_true(coral_red_black_tree_set_remove_item(
            &object->set, item));
    return true;
}

static bool retrieve_np(const struct sea_turtle_integer *const item,
                        const struct sea_turtle_integer **const out,
                        bool (*const func)(const void *, const void **)) {
    assert(func);
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(item, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_set_i_next(
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_next);
}

bool seahorse_red_black_tree_set_i_prev(
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_prev);
}

