#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <triggerfish.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

struct seahorse_red_black_tree_map_s_wr_entry {
    void *data;
};

static int compare(const void *const a, const void *const b) {
    const struct sea_turtle_string *const A
            = (const struct sea_turtle_string *) a;
    const struct sea_turtle_string *const B
            = (const struct sea_turtle_string *) b;
    return sea_turtle_string_compare(A, B);
}

static void init(struct seahorse_red_black_tree_map_s_wr *const object) {
    assert(object);
    *object = (struct seahorse_red_black_tree_map_s_wr) {0};
    seagrass_required_true(coral_red_black_tree_map_init(
            &object->map,
            sizeof(struct sea_turtle_string),
            sizeof(struct triggerfish_weak *),
            compare));
}

bool seahorse_red_black_tree_map_s_wr_init(
        struct seahorse_red_black_tree_map_s_wr *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    init(object);
    return true;
}

static void on_destroy(void *const key, void *const value) {
    seagrass_required_true(sea_turtle_string_invalidate(key));
    struct triggerfish_weak **const V = value;
    seagrass_required_true(triggerfish_weak_destroy(*V));
}

static void invalidate(struct seahorse_red_black_tree_map_s_wr *const object) {
    assert(object);
    seagrass_required_true(coral_red_black_tree_map_invalidate(
            &object->map, on_destroy));
    *object = (struct seahorse_red_black_tree_map_s_wr) {0};
}

bool seahorse_red_black_tree_map_s_wr_invalidate(
        struct seahorse_red_black_tree_map_s_wr *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    invalidate(object);
    return true;
}

bool seahorse_red_black_tree_map_s_wr_init_red_black_tree_map_s_wr(
        struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr *const other) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OTHER_IS_NULL;
        return false;
    }
    init(object);
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    if (!seahorse_red_black_tree_map_s_wr_first_entry(other, &entry)) {
        seagrass_required_true(
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY
                == seahorse_error);
        return true;
    }
    do {
        const struct sea_turtle_string *key;
        seagrass_required_true(seahorse_red_black_tree_map_s_wr_entry_key(
                other, entry, &key));
        const struct triggerfish_weak *value;
        seagrass_required_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
                other, entry, &value));
        if (!seahorse_red_black_tree_map_s_wr_add(object, key, value)) {
            seagrass_required_true(
                    SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED
                    == seahorse_error);
            invalidate(object);
            return false;
        }
    } while (seahorse_red_black_tree_map_s_wr_next_entry(entry, &entry));
    seagrass_required_true(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE
            == seahorse_error);
    return true;
}

bool seahorse_red_black_tree_map_s_wr_count(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_count(
            &object->map, out));
    return true;
}

bool seahorse_red_black_tree_map_s_wr_add(
        struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL;
        return false;
    }
    bool result;
    if (!coral_red_black_tree_map_contains(&object->map, key, &result)) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    } else if (result) {
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_ALREADY_EXISTS;
        return false;
    }
    struct sea_turtle_string k;
    if (!sea_turtle_string_init_string(&k, key)) {
        seagrass_required_true(
                SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                == sea_turtle_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct triggerfish_weak *out;
    if (!triggerfish_weak_copy_of(value, &out)) {
        seagrass_required_true(sea_turtle_string_invalidate(&k));
        seagrass_required_true(
                TRIGGERFISH_WEAK_ERROR_MEMORY_ALLOCATION_FAILED
                == triggerfish_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (!coral_red_black_tree_map_add(&object->map, &k, &out)) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seagrass_required_true(sea_turtle_string_invalidate(&k));
        seagrass_required_true(triggerfish_weak_destroy(out));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    return true;
}

bool seahorse_red_black_tree_map_s_wr_remove(
        struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    const struct coral_red_black_tree_map_entry *entry;
    if (!coral_red_black_tree_map_get_entry(&object->map, key, &entry)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        return false;
    }
    struct sea_turtle_string *k;
    seagrass_required_true(coral_red_black_tree_map_entry_key(
            &object->map, entry, (const void **) &k));
    struct triggerfish_weak **v;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map, entry, (const void **) &v));
    on_destroy(k, v);
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map, entry));
    return true;
}

bool seahorse_red_black_tree_map_s_wr_contains(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_red_black_tree_map_contains(&object->map, key,
                                                          out);
    if (!result) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_wr_set(
        struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL;
        return false;
    }
    const struct coral_red_black_tree_map_entry *entry;
    if (!coral_red_black_tree_map_get_entry(&object->map, key, &entry)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        return false;
    }
    struct triggerfish_weak *copy;
    if (!triggerfish_weak_copy_of(value, &copy)) {
        seagrass_required_true(
                TRIGGERFISH_WEAK_ERROR_MEMORY_ALLOCATION_FAILED
                == triggerfish_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct triggerfish_weak **out;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map, entry, (const void **) &out));
    struct triggerfish_weak *const weak = *out;
    if (!coral_red_black_tree_map_set(&object->map, key, &copy)) {
        seagrass_required_true(
                CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                == coral_error);
        seagrass_required_true(triggerfish_weak_destroy(copy));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    seagrass_required_true(triggerfish_weak_destroy(weak));
    return true;
}

static bool retrieve(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const void **const out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    struct triggerfish_weak **value;
    if (!func(&object->map, key, (const void **) &value)) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        return false;
    }
    *out = *value;
    return true;
}

bool seahorse_red_black_tree_map_s_wr_get(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_get);
}

bool seahorse_red_black_tree_map_s_wr_ceiling(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_ceiling);
}

bool seahorse_red_black_tree_map_s_wr_floor(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_floor);
}

bool seahorse_red_black_tree_map_s_wr_higher(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_higher);
}

bool seahorse_red_black_tree_map_s_wr_lower(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct triggerfish_weak **const out) {
    return retrieve(object, key, out, coral_red_black_tree_map_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct triggerfish_weak **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    struct triggerfish_weak **value;
    if (!func(&object->map, (const void **) &value)) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY;
        return false;
    }
    *out = *value;
    return true;
}

bool seahorse_red_black_tree_map_s_wr_first(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct triggerfish_weak **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_first);
}

bool seahorse_red_black_tree_map_s_wr_last(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct triggerfish_weak **const out) {
    return retrieve_fl(object, out, coral_red_black_tree_map_last);
}

static bool retrieve_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const void *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, key,
                             (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND;
                break;
            }
            case CORAL_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_red_black_tree_map_s_wr_get_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry(object, key, out, coral_red_black_tree_map_get_entry);
}

bool seahorse_red_black_tree_map_s_wr_ceiling_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_ceiling_entry);
}

bool seahorse_red_black_tree_map_s_wr_floor_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_floor_entry);
}

bool seahorse_red_black_tree_map_s_wr_higher_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_higher_entry);
}

bool seahorse_red_black_tree_map_s_wr_lower_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry(object, key, out,
                          coral_red_black_tree_map_lower_entry);
}

static bool retrieve_entry_fl(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            &object->map,
            (const struct coral_red_black_tree_map_entry **const) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_wr_first_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_first_entry);
}

bool seahorse_red_black_tree_map_s_wr_last_entry(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry_fl(object, out, coral_red_black_tree_map_last_entry);
}

bool seahorse_red_black_tree_map_s_wr_remove_entry(
        struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    struct sea_turtle_string *key;
    seagrass_required_true(seahorse_red_black_tree_map_s_wr_entry_key(
            object, entry, (const struct sea_turtle_string **) &key));
    const struct triggerfish_weak **value;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) &value));
    on_destroy(key, value);
    seagrass_required_true(coral_red_black_tree_map_remove_entry(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry));
    return true;
}

static bool retrieve_entry_np(
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out,
        bool (*const func)(const struct coral_red_black_tree_map_entry *const,
                           const struct coral_red_black_tree_map_entry **const)) {
    assert(func);
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            (const struct coral_red_black_tree_map_entry *) entry,
            (const struct coral_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(CORAL_RED_BLACK_TREE_MAP_ERROR_END_OF_SEQUENCE
                               == coral_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_wr_next_entry(
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_next_entry);
}

bool seahorse_red_black_tree_map_s_wr_prev_entry(
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct seahorse_red_black_tree_map_s_wr_entry **const out) {
    return retrieve_entry_np(entry, out, coral_red_black_tree_map_prev_entry);
}

bool seahorse_red_black_tree_map_s_wr_entry_key(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct sea_turtle_string **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_red_black_tree_map_entry_key(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) out));
    return true;
}

bool seahorse_red_black_tree_map_s_wr_entry_get_value(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct triggerfish_weak **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL;
        return false;
    }
    const struct triggerfish_weak **value;
    seagrass_required_true(coral_red_black_tree_map_entry_get_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            (const void **) &value));
    *out = *value;
    return true;
}

bool seahorse_red_black_tree_map_s_wr_entry_set_value(
        const struct seahorse_red_black_tree_map_s_wr *const object,
        const struct seahorse_red_black_tree_map_s_wr_entry *const entry,
        const struct triggerfish_weak *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct triggerfish_weak *copy;
    if (!triggerfish_weak_copy_of(value, &copy)) {
        seagrass_required_true(
                TRIGGERFISH_WEAK_ERROR_MEMORY_ALLOCATION_FAILED
                == triggerfish_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct triggerfish_weak *out;
    seagrass_required_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            object, entry, (const struct triggerfish_weak **) &out));
    seagrass_required_true(triggerfish_weak_destroy(out));
    seagrass_required_true(coral_red_black_tree_map_entry_set_value(
            &object->map,
            (const struct coral_red_black_tree_map_entry *) entry,
            &copy));
    return true;
}
