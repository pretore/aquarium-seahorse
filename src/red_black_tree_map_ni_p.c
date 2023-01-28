#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

struct seahorse_red_black_tree_map_ni_p_entry {
    void *data;
};

static int compare(const void *const a, const void *const b) {
    return seagrass_uintmax_t_compare(*(uintmax_t *) a,
                                      *(uintmax_t *) b);
}

bool seahorse_red_black_tree_map_ni_p_init(
        struct seahorse_red_black_tree_map_ni_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_red_black_tree_map_ni_p) {0};
    seagrass_required_true(coral_red_black_tree_map_init(
            &object->map,
            sizeof(uintmax_t),
            sizeof(void *),
            compare));
    return true;
}

static _Thread_local void (*on_destroy_callback)(void *value);

static void on_destroy_entity(void *key, void *value) {
    if (!on_destroy_callback) {
        return;
    }
    on_destroy_callback(*(void **) value);
}

bool seahorse_red_black_tree_map_ni_p_invalidate(
        struct seahorse_red_black_tree_map_ni_p *const object,
        void (*on_destroy)(void *value)) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    on_destroy_callback = on_destroy;
    seagrass_required_true(coral_red_black_tree_map_invalidate(
            &object->map, on_destroy_entity));
    *object = (struct seahorse_red_black_tree_map_ni_p) {0};
    return true;
}

bool seahorse_red_black_tree_map_ni_p_count(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_count(
            &object->map, out));
    return true;
}

bool seahorse_red_black_tree_map_ni_p_add(
        struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_add(&object->map, &key,
                                                     &value);
    if (!result) {
        switch (coral_error) {
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_ALREADY_EXISTS: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_ALREADY_EXISTS;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
            default: {
                seagrass_required_true(false);
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_remove(
        struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
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
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_contains(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_contains(&object->map, &key,
                                                          out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_set(
        struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
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
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

static bool retrieve(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const void **const out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    void *value;
    const bool result = func(&object->map, &key, (const void **const) &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    } else {
        *out = *(void **) value;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_get(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_get);
}

bool seahorse_red_black_tree_map_ni_p_ceiling(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_ceiling);
}

bool seahorse_red_black_tree_map_ni_p_floor(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_floor);
}

bool seahorse_red_black_tree_map_ni_p_higher(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_higher);
}

bool seahorse_red_black_tree_map_ni_p_lower(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const void **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const void **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    void *value;
    const bool result = func(&object->map, (const void **const) &value);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY;
    } else {
        *out = *(void **) value;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_first(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const void **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_first);
}

bool seahorse_red_black_tree_map_ni_p_last(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const void **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_last);
}

static bool retrieve_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
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
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_get_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry(object, key, out, coral_red_black_tree_map_get_entry);
}

bool seahorse_red_black_tree_map_ni_p_ceiling_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_ceiling_entry);
}

bool seahorse_red_black_tree_map_ni_p_floor_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_floor_entry);
}

bool seahorse_red_black_tree_map_ni_p_higher_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_higher_entry);
}

bool seahorse_red_black_tree_map_ni_p_lower_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const uintmax_t key,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_lower_entry);
}

static bool retrieve_entry_fl(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            &object->map,
            (const struct coral_red_black_tree_map_entry **const) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_first_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_first_entry);
}

bool seahorse_red_black_tree_map_ni_p_last_entry(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_last_entry);
}

bool seahorse_red_black_tree_map_ni_p_remove_entry(
        struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry));
    return true;
}

static bool retrieve_entry_np(
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map_entry *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            (const struct coral_red_black_tree_map_entry *) entry,
            (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_next_entry(
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_next_entry);
}

bool seahorse_red_black_tree_map_ni_p_prev_entry(
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const struct seahorse_red_black_tree_map_ni_p_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_prev_entry);
}

static bool entry_retrieve(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const void **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(func(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) out));
    return true;
}

bool seahorse_red_black_tree_map_ni_p_entry_key(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const uintmax_t **const out) {
    return entry_retrieve(object, entry, (const void **) out,
                          coral_red_black_tree_map_entry_key);
}

bool seahorse_red_black_tree_map_ni_p_entry_get_value(
        const struct seahorse_red_black_tree_map_ni_p *const object,
        const struct seahorse_red_black_tree_map_ni_p_entry *const entry,
        const void **const out) {
    const void *address;
    const bool result = entry_retrieve(object, entry, &address,
                                       coral_red_black_tree_map_entry_get_value);
    if (result) {
        *out = *(void **) address;
    }
    return result;
}

bool seahorse_red_black_tree_map_ni_p_entry_set_value(
        const struct seahorse_red_black_tree_map_ni_p *object,
        const struct seahorse_red_black_tree_map_ni_p_entry *entry,
        const void *value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_entry_set_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            &value));
    return true;
}
