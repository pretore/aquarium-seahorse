#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

static int compare(const void *const a, const void *const b) {
    return seagrass_uintmax_t_compare(*(uintmax_t *) a,
                                      *(uintmax_t *) b);
}

bool seahorse_linked_red_black_tree_set_ni_init(
        struct seahorse_linked_red_black_tree_set_ni *const object) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_linked_red_black_tree_set_ni) {0};
    seagrass_required_true(coral_linked_red_black_tree_set_init(
            &object->set,
            sizeof(uintmax_t),
            compare));
    return true;
}

bool seahorse_linked_red_black_tree_set_ni_invalidate(
        struct seahorse_linked_red_black_tree_set_ni *const object) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_red_black_tree_set_invalidate(
            &object->set, NULL));
    *object = (struct seahorse_linked_red_black_tree_set_ni) {0};
    return true;
}

bool seahorse_linked_red_black_tree_set_ni_count(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_red_black_tree_set_count(
            &object->set, out));
    return true;
}

bool seahorse_linked_red_black_tree_set_ni_add(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_red_black_tree_set_add(
            &object->set, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS;
                break;
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_remove(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_red_black_tree_set_remove(
            &object->set, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_NOT_FOUND;
                break;
            }
            case
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_contains(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        bool *const out) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_red_black_tree_set_contains(
            &object->set, &value, out);
    if (!result) {
        seagrass_required_true(
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

static bool retrieve(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_linked_red_black_tree_set *const,
                           const void *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, &value, (const void **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_ITEM_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND;
                break;
            }
            case
            CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_get(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_linked_red_black_tree_set_get);
}

bool seahorse_linked_red_black_tree_set_ni_ceiling(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out,
                    coral_linked_red_black_tree_set_ceiling);
}

bool seahorse_linked_red_black_tree_set_ni_floor(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_linked_red_black_tree_set_floor);
}

bool seahorse_linked_red_black_tree_set_ni_higher(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_linked_red_black_tree_set_higher);
}

bool seahorse_linked_red_black_tree_set_ni_lower(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        const uintmax_t **const out) {
    return retrieve(object, value, out, coral_linked_red_black_tree_set_lower);
}

static bool retrieve_hl(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_linked_red_black_tree_set *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, (const void **) out);
    if (!result) {
        seagrass_required_true(
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_SET_IS_EMPTY
                == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY;
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_highest(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_hl(object, out, coral_linked_red_black_tree_set_highest);
}

bool seahorse_linked_red_black_tree_set_ni_lowest(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_hl(object, out, coral_linked_red_black_tree_set_lowest);
}

static bool retrieve_fl(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_linked_red_black_tree_set *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_SET_ERROR_SET_IS_EMPTY
                               == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY;
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_first(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_linked_red_black_tree_set_first);
}

bool seahorse_linked_red_black_tree_set_ni_last(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_linked_red_black_tree_set_last);
}

bool seahorse_linked_red_black_tree_set_ni_remove_item(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item) {
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_red_black_tree_set_remove_item(
            &object->set, item));
    return true;
}

static bool retrieve_np(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t **const out,
        bool (*const func)(
                const struct coral_linked_red_black_tree_set *const,
                const void *const,
                const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, item, (const void **) out);
    if (!result) {
        seagrass_required_true(
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_END_OF_SEQUENCE
                == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_next(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t **const out) {
    return retrieve_np(object, item, out, coral_linked_red_black_tree_set_next);
}

bool seahorse_linked_red_black_tree_set_ni_prev(
        const struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t **const out) {
    return retrieve_np(object, item, out, coral_linked_red_black_tree_set_prev);
}

static bool insert_item_ab(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t value,
        bool (*const func)(struct coral_linked_red_black_tree_set *const,
                           const void *const,
                           const void *const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, item, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS;
                break;
            }
            case
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_insert_after(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t value) {
    return insert_item_ab(object, item, value,
                          coral_linked_red_black_tree_set_insert_after);
}

bool seahorse_linked_red_black_tree_set_ni_insert_before(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t *const item,
        const uintmax_t value) {
    return insert_item_ab(object, item, value,
                          coral_linked_red_black_tree_set_insert_before);
}

static bool insert_value_ab(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value,
        bool (*const func)(struct coral_linked_red_black_tree_set *const,
                           const void *const)) {
    assert(func);
    if (!object) {
        seahorse_error =
                SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = func(&object->set, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS;
                break;
            }
            case
                CORAL_LINKED_RED_BLACK_TREE_SET_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_linked_red_black_tree_set_ni_append(
        struct seahorse_linked_red_black_tree_set_ni *const object,
        const uintmax_t value) {
    return insert_value_ab(object, value,
                           coral_linked_red_black_tree_set_append);
}

bool seahorse_linked_red_black_tree_set_ni_prepend(
        struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value) {
    return insert_value_ab(object, value,
                           coral_linked_red_black_tree_set_prepend);
}
