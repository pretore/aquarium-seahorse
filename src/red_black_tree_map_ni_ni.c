#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

struct seahorse_red_black_tree_map_ni_ni_entry {
    void *data;
};

static int compare(const void *const a, const void *const b) {
    return seagrass_uintmax_t_compare(*(uintmax_t *) a,
                                      *(uintmax_t *) b);
}

bool seahorse_red_black_tree_map_ni_ni_init(
        struct seahorse_red_black_tree_map_ni_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_red_black_tree_map_ni_ni) {0};
    seagrass_required_true(coral_red_black_tree_map_init(
            &object->map,
            sizeof(uintmax_t),
            sizeof(uintmax_t),
            compare));
    return true;
}

bool seahorse_red_black_tree_map_ni_ni_invalidate(
        struct seahorse_red_black_tree_map_ni_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_invalidate(
            &object->map, NULL));
    *object = (struct seahorse_red_black_tree_map_ni_ni) {0};
    return true;
}

bool seahorse_red_black_tree_map_ni_ni_count(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_count(
            &object->map, out));
    return true;
}

bool seahorse_red_black_tree_map_ni_ni_add(
        struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_add(&object->map, &key,
                                                     &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_ALREADY_EXISTS;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_remove(
        struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_remove(&object->map, &key);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_contains(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_contains(&object->map, &key,
                                                          out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_set(
        struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_set(&object->map, &key,
                                                     &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

static bool retrieve(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const void **const out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, &key, (const void **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_get(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_get);
}

bool seahorse_red_black_tree_map_ni_ni_ceiling(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_ceiling);
}

bool seahorse_red_black_tree_map_ni_ni_floor(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_floor);
}

bool seahorse_red_black_tree_map_ni_ni_higher(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_higher);
}

bool seahorse_red_black_tree_map_ni_ni_lower(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const uintmax_t **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, (const void **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_first(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_first);
}

bool seahorse_red_black_tree_map_ni_ni_last(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_last);
}

static bool retrieve_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, &key,
                             (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_get_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry(object, key, out, coral_red_black_tree_map_get_entry);
}

bool seahorse_red_black_tree_map_ni_ni_ceiling_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_ceiling_entry);
}

bool seahorse_red_black_tree_map_ni_ni_floor_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_floor_entry);
}

bool seahorse_red_black_tree_map_ni_ni_higher_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_higher_entry);
}

bool seahorse_red_black_tree_map_ni_ni_lower_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_lower_entry);
}

static bool retrieve_entry_fl(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            &object->map,
            (const struct coral_red_black_tree_map_entry **const) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_first_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_first_entry);
}

bool seahorse_red_black_tree_map_ni_ni_last_entry(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_last_entry);
}

bool seahorse_red_black_tree_map_ni_ni_remove_entry(
        struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry));
    return true;
}

static bool retrieve_entry_np(
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map_entry *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            (const struct coral_red_black_tree_map_entry *) entry,
            (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_ni_next_entry(
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_next_entry);
}

bool seahorse_red_black_tree_map_ni_ni_prev_entry(
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_ni_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_prev_entry);
}

static bool entry_retrieve(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const uintmax_t **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(func(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) out));
    return true;
}

bool seahorse_red_black_tree_map_ni_ni_entry_key(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const uintmax_t **const out) {
    return entry_retrieve(object, entry, out,
                          coral_red_black_tree_map_entry_key);
}

bool seahorse_red_black_tree_map_ni_ni_entry_get_value(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        const uintmax_t **const out) {
    return entry_retrieve(object, entry, out,
                          coral_red_black_tree_map_entry_get_value);
}

bool seahorse_red_black_tree_map_ni_ni_entry_set_value(
        const struct seahorse_red_black_tree_map_ni_ni *const object,
        const struct seahorse_red_black_tree_map_ni_ni_entry *const entry,
        uintmax_t value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_ENTRY_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_entry_set_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            &value));
    return true;
}
