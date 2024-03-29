#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

static int compare(const void *const a, const void *const b) {
    return seagrass_uintmax_t_compare(*(uintmax_t *) a,
                                      *(uintmax_t *) b);
}

static void init(struct seahorse_red_black_tree_set_ni *const object) {
    assert(object);
    *object = (struct seahorse_red_black_tree_set_ni) {0};
    seagrass_required_true(coral_red_black_tree_set_init(
            &object->set,
            sizeof(uintmax_t),
            compare));
}

bool seahorse_red_black_tree_set_ni_init(
        struct seahorse_red_black_tree_set_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    init(object);
    return true;
}

static void invalidate(struct seahorse_red_black_tree_set_ni *const object) {
    assert(object);
    seagrass_required_true(coral_red_black_tree_set_invalidate(
            &object->set,
            NULL));
    *object = (struct seahorse_red_black_tree_set_ni) {0};
}

bool seahorse_red_black_tree_set_ni_invalidate(
        struct seahorse_red_black_tree_set_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    invalidate(object);
    return true;
}

bool seahorse_red_black_tree_set_ni_init_red_black_tree_set_ni(
        struct seahorse_red_black_tree_set_ni *const object,
        const struct seahorse_red_black_tree_set_ni *const other) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OTHER_IS_NULL;
        return false;
    }
    init(object);
    const uintmax_t *item;
    if (!seahorse_red_black_tree_set_ni_first(other, &item)) {
        seagrass_required_true(
                SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY
                == seahorse_error);
        return true;
    }
    do {
        if (!seahorse_red_black_tree_set_ni_add(object, *item)) {
            seagrass_required_true(
                    SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
                    == seahorse_error);
            invalidate(object);
            return false;
        }
    } while (seahorse_red_black_tree_set_ni_next(item, &item));
    seagrass_required_true(
            SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE
            == seahorse_error);
    return true;
}

bool seahorse_red_black_tree_set_ni_count(
        const struct seahorse_red_black_tree_set_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_set_count(
            &object->set, out));
    return true;
}

bool seahorse_red_black_tree_set_ni_add(
        struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_set_add(&object->set, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_set_ni_remove(
        struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_set_remove(&object->set, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_VALUE_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_VALUE_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_set_ni_contains(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_set_contains(&object->set, &value,
                                                          out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

static bool retrieve(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    if (func(&object->set, &value, (const void **) out)) {
        return true;
    }
    switch (coral_error) {
        default: {
            seagrass_required_true(false);
        }
        case CORAL_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
            seahorse_error =
                    SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND;
            break;
        }
        case CORAL_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
            seahorse_error =
                    SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
            break;
        }
    }
    return false;
}

bool seahorse_red_black_tree_set_ni_get(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_get);
}

bool seahorse_red_black_tree_set_ni_ceiling(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_ceiling);
}

bool seahorse_red_black_tree_set_ni_floor(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_floor);
}

bool seahorse_red_black_tree_set_ni_higher(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_higher);
}

bool seahorse_red_black_tree_set_ni_lower(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_red_black_tree_set_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_red_black_tree_set *,
                           const void **out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_SET_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_set_ni_first(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_first);
}

bool seahorse_red_black_tree_set_ni_last(
        const struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_set_last);
}

bool seahorse_red_black_tree_set_ni_remove_item(
        struct seahorse_red_black_tree_set_ni *const object,
        const uintmax_t *const item) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_set_remove_item(
            &object->set, item));
    return true;
}

static bool retrieve_np(const uintmax_t *const item,
                        const uintmax_t **const out,
                        bool (*const func)(const void *, const void **)) {
    assert(func);
    if (!item) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(item, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_set_ni_next(const uintmax_t *const item,
                                         const uintmax_t **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_next);
}

bool seahorse_red_black_tree_set_ni_prev(const uintmax_t *const item,
                                         const uintmax_t **const out) {
    return retrieve_np(item, out, coral_red_black_tree_set_prev);
}

