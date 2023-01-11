#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <triggerfish.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

struct seahorse_red_black_tree_map_sr_sr_entry {
    void *data;
};

bool seahorse_red_black_tree_map_sr_sr_init(
        struct seahorse_red_black_tree_map_sr_sr *const object,
        int (*const compare)(const struct triggerfish_strong **first,
                             const struct triggerfish_strong **second)) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!compare) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_COMPARE_IS_NULL;
        return false;
    }
    *object = (struct seahorse_red_black_tree_map_sr_sr) {0};
    seagrass_required_true(coral_red_black_tree_map_init(
            &object->map,
            sizeof(struct triggerfish_strong *),
            sizeof(struct triggerfish_strong *),
            (int (*)(const void *, const void *)) compare));
    return true;
}

static void on_destroy(void *k, void *v) {
    struct triggerfish_strong *const K = *(struct triggerfish_strong **) k;
    seagrass_required_true(triggerfish_strong_release(K));
    struct triggerfish_strong *const V = *(struct triggerfish_strong **) v;
    if (!V) {
        return;
    }
    seagrass_required_true(triggerfish_strong_release(V));
}

bool seahorse_red_black_tree_map_sr_sr_invalidate(
        struct seahorse_red_black_tree_map_sr_sr *const object) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_invalidate(
            &object->map, on_destroy));
    *object = (struct seahorse_red_black_tree_map_sr_sr) {0};
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_count(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_count(
            &object->map, out));
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_add(
        struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong *const value) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
        return false;
    }
    if (value && !triggerfish_strong_retain(value)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seagrass_required_true(triggerfish_strong_release(key));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID;
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
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_ALREADY_EXISTS;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(triggerfish_strong_release(key));
        if (value) {
            seagrass_required_true(triggerfish_strong_release(value));
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_sr_sr_remove(
        struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
        return false;
    }
    const struct coral_red_black_tree_map_entry *entry;
    if (!coral_red_black_tree_map_get_entry(&object->map, &key, &entry)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(triggerfish_strong_release(key));
        return false;
    }
    struct {
        struct triggerfish_strong **key;
        struct triggerfish_strong **value;
    } pair;
    seagrass_required_true(coral_red_black_tree_map_entry_key(
            &object->map, entry, (const void **) &pair.key));
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map, entry, (const void **) &pair.value));
    on_destroy(pair.key, pair.value);
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map, entry));
    seagrass_required_true(triggerfish_strong_release(key));
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_contains(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        bool *const out) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
        return false;
    }
    const bool result = coral_red_black_tree_map_contains(&object->map, &key,
                                                          out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    seagrass_required_true(triggerfish_strong_release(key));
    return result;
}

bool seahorse_red_black_tree_map_sr_sr_set(
        struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong *const value) {
    if (!object) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
        return false;
    }
    if (value && !triggerfish_strong_retain(value)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seagrass_required_true(triggerfish_strong_release(key));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID;
        return false;
    }
    const struct coral_red_black_tree_map_entry *entry;
    if (!coral_red_black_tree_map_get_entry(&object->map, &key, &entry)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(triggerfish_strong_release(key));
        if (value) {
            seagrass_required_true(triggerfish_strong_release(value));
        }
        return false;
    }
    struct triggerfish_strong **strong;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map, entry, (const void **) &strong));
    if (*strong) {
        seagrass_required_true(triggerfish_strong_release(*strong));
    }
    seagrass_required_true(coral_red_black_tree_map_entry_set_value(
            &object->map, entry, &value));
    seagrass_required_true(triggerfish_strong_release(key));
    return true;
}

static bool retrieve(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const void **const out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
        return false;
    }
    struct triggerfish_strong **value;
    if (!func(&object->map, &key, (const void **) &value)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(triggerfish_strong_release(key));
        return false;
    }
    if (*value) {
        seagrass_required_true(triggerfish_strong_retain(*value));
    }
    *out = *value;
    seagrass_required_true(triggerfish_strong_release(key));
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_get(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_get);
}

bool seahorse_red_black_tree_map_sr_sr_ceiling(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_ceiling);
}

bool seahorse_red_black_tree_map_sr_sr_floor(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_floor);
}

bool seahorse_red_black_tree_map_sr_sr_higher(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_higher);
}

bool seahorse_red_black_tree_map_sr_sr_lower(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        struct triggerfish_strong *const key,
        struct triggerfish_strong **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    struct triggerfish_strong **value;
    if (!func(&object->map, (const void **) &value)) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY;
        return false;
    }
    if (*value) {
        seagrass_required_true(triggerfish_strong_retain(*value));
    }
    *out = *value;
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_first(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_first);
}

bool seahorse_red_black_tree_map_sr_sr_last(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_last);
}

static bool retrieve_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(key)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID;
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
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    seagrass_required_true(triggerfish_strong_release(key));
    return result;
}

bool seahorse_red_black_tree_map_sr_sr_get_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out) {
    return retrieve_entry(object, key, out, coral_red_black_tree_map_get_entry);
}

bool seahorse_red_black_tree_map_sr_sr_ceiling_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_ceiling_entry);
}

bool seahorse_red_black_tree_map_sr_sr_floor_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_floor_entry);
}

bool seahorse_red_black_tree_map_sr_sr_higher_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_higher_entry);
}

bool seahorse_red_black_tree_map_sr_sr_lower_entry(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        struct triggerfish_strong *const key,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_lower_entry);
}

static bool retrieve_entry_fl(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            &object->map,
            (const struct coral_red_black_tree_map_entry **const) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_sr_sr_first_entry(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        const struct seahorse_red_black_tree_map_sr_sr_entry **out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_first_entry);
}

bool seahorse_red_black_tree_map_sr_sr_last_entry(
        const struct seahorse_red_black_tree_map_sr_sr *object,
        const struct seahorse_red_black_tree_map_sr_sr_entry **out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_last_entry);
}

bool seahorse_red_black_tree_map_sr_sr_remove_entry(
        struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    struct {
        struct triggerfish_strong **key;
        struct triggerfish_strong **value;
    } pair;
    const struct coral_red_black_tree_map_entry *e
            = (const struct coral_red_black_tree_map_entry *) entry;
    seagrass_required_true(coral_red_black_tree_map_entry_key(
            &object->map, e, (const void **) &pair.key));
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map, e, (const void **) &pair.value));
    on_destroy(pair.key, pair.value);
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map, e));
    return true;
}

static bool retrieve_entry_np(
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry,
        const struct seahorse_red_black_tree_map_sr_sr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map_entry *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            (const struct coral_red_black_tree_map_entry *) entry,
            (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_map_sr_sr_next_entry(
        const struct seahorse_red_black_tree_map_sr_sr_entry *entry,
        const struct seahorse_red_black_tree_map_sr_sr_entry **out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_next_entry);
}

bool seahorse_red_black_tree_map_sr_sr_prev_entry(
        const struct seahorse_red_black_tree_map_sr_sr_entry *entry,
        const struct seahorse_red_black_tree_map_sr_sr_entry **out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_prev_entry);
}

static bool entry_retrieve(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry,
        struct triggerfish_strong **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    struct triggerfish_strong **value;
    seagrass_required_true(func(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) &value));
    if (*value) {
        seagrass_required_true(triggerfish_strong_retain(*value));
    }
    *out = *value;
    return true;
}

bool seahorse_red_black_tree_map_sr_sr_entry_key(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry,
        struct triggerfish_strong **const out) {
    return entry_retrieve(object, entry, out,
                          coral_red_black_tree_map_entry_key);
}

bool seahorse_red_black_tree_map_sr_sr_entry_get_value(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry,
        struct triggerfish_strong **const out) {
    return entry_retrieve(object, entry, out,
                          coral_red_black_tree_map_entry_get_value);
}

bool seahorse_red_black_tree_map_sr_sr_entry_set_value(
        const struct seahorse_red_black_tree_map_sr_sr *const object,
        const struct seahorse_red_black_tree_map_sr_sr_entry *const entry,
        struct triggerfish_strong *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (value && !triggerfish_strong_retain(value)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID;
        return false;
    }
    struct triggerfish_strong **out;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map,
            (struct coral_red_black_tree_map_entry *) entry,
            (const void **) &out));
    if (*out) {
        seagrass_required_true(triggerfish_strong_release(*out));
    }
    seagrass_required_true(coral_red_black_tree_map_entry_set_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
                    &value));
    return true;
}

