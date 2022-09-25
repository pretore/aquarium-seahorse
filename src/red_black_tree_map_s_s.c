#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <seahorse.h>

struct seahorse_red_black_tree_map_s_s_entry {
    void *data;
};

static int compare(const void *const a, const void *const b) {
    const struct sea_turtle_string *A = (const struct sea_turtle_string *) a;
    const struct sea_turtle_string *B = (const struct sea_turtle_string *) b;
    return sea_turtle_string_compare(A, B);
}

bool seahorse_red_black_tree_map_s_s_init(
        struct seahorse_red_black_tree_map_s_s *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_red_black_tree_map_s_s) {0};
    seagrass_required_true(rock_red_black_tree_map_init(
            &object->map,
            sizeof(struct sea_turtle_string),
            sizeof(struct sea_turtle_string),
            compare));
    return true;
}

static void on_destroy(void *key, void *value) {
    seagrass_required_true(sea_turtle_string_invalidate(key));
    seagrass_required_true(sea_turtle_string_invalidate(value));
}

bool seahorse_red_black_tree_map_s_s_invalidate(
        struct seahorse_red_black_tree_map_s_s *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_red_black_tree_map_invalidate(
            &object->map, on_destroy));
    *object = (struct seahorse_red_black_tree_map_s_s) {0};
    return true;
}

bool seahorse_red_black_tree_map_s_s_count(
        const struct seahorse_red_black_tree_map_s_s *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_red_black_tree_map_count(
            &object->map, out));
    return true;
}

bool seahorse_red_black_tree_map_s_s_add(
        struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct sea_turtle_string *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    bool result;
    seagrass_required_true(rock_red_black_tree_map_contains(
            &object->map, key, &result));
    if (result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_KEY_ALREADY_EXISTS
                               != rock_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_ALREADY_EXISTS;
        return false;
    }
    struct {
        struct sea_turtle_string key;
        struct sea_turtle_string value;
    } copy = {};
    if (!sea_turtle_string_init_with_string(&copy.key, key)
        || !sea_turtle_string_init_with_string(&copy.value, value)
        || !rock_red_black_tree_map_add(&object->map, &copy.key, &copy.value)) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                               == sea_turtle_error
                               ||
                               ROCK_RED_BLACK_TREE_MAP_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seagrass_required_true(sea_turtle_string_invalidate(&copy.key));
        seagrass_required_true(sea_turtle_string_invalidate(&copy.value));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    return true;
}

bool seahorse_red_black_tree_map_s_s_remove(
        struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    const struct rock_red_black_tree_map_entry *entry;
    if (!rock_red_black_tree_map_get_entry(&object->map, key,
                                           &entry)) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND;
        return false;
    }
    struct {
        struct sea_turtle_string key;
        struct sea_turtle_string value;
    } copy;
    const struct sea_turtle_string *out;
    seagrass_required_true(rock_red_black_tree_map_entry_key(
            &object->map, entry, (const void **) &out));
    memcpy(&copy.key, out, sizeof(*out));
    seagrass_required_true(rock_red_black_tree_map_entry_get_value(
            &object->map, entry, (const void **) &out));
    memcpy(&copy.value, out, sizeof(*out));
    seagrass_required_true(rock_red_black_tree_map_remove_entry(
            &object->map, entry));
    seagrass_required_true(sea_turtle_string_invalidate(&copy.key));
    seagrass_required_true(sea_turtle_string_invalidate(&copy.value));
    return true;
}

bool seahorse_red_black_tree_map_s_s_contains(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_red_black_tree_map_contains(
            &object->map, key, out));
    return true;
}

bool seahorse_red_black_tree_map_s_s_set(
        struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct sea_turtle_string *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    const struct rock_red_black_tree_map_entry *entry;
    if (!rock_red_black_tree_map_get_entry(&object->map, key,
                                           &entry)) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND;
        return false;
    }
    const void *out;
    seagrass_required_true(rock_red_black_tree_map_entry_get_value(
            &object->map, entry, &out));
    struct sea_turtle_string old;
    memcpy(&old, out, sizeof(old));
    struct sea_turtle_string new = {};
    if (!sea_turtle_string_init_with_string(&new, value)) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                               == sea_turtle_error);
        seagrass_required_true(sea_turtle_string_invalidate(&new));
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    seagrass_required_true(rock_red_black_tree_map_set(
            &object->map, key, &new));
    seagrass_required_true(sea_turtle_string_invalidate(&old));
    return true;
}

static bool retrieve(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out,
        bool (func)(const struct rock_red_black_tree_map *const,
                    const void *const,
                    const void **const out)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, key, (const void **) out);
    if (!result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_s_get(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out) {
    return retrieve(object, key, out, rock_red_black_tree_map_get);
}

bool seahorse_red_black_tree_map_s_s_ceiling(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out) {
    return retrieve(object, key, out, rock_red_black_tree_map_ceiling);
}

bool seahorse_red_black_tree_map_s_s_floor(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out) {
    return retrieve(object, key, out, rock_red_black_tree_map_floor);
}

bool seahorse_red_black_tree_map_s_s_higher(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out) {
    return retrieve(object, key, out, rock_red_black_tree_map_higher);
}

bool seahorse_red_black_tree_map_s_s_lower(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        struct sea_turtle_string **const out) {
    return retrieve(object, key, out, rock_red_black_tree_map_lower);
}

static bool retrieve_fl(
        const struct seahorse_red_black_tree_map_s_s *const object,
        struct sea_turtle_string **const out,
        bool (func)(const struct rock_red_black_tree_map *const,
                    const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, (const void **) out);
    if (!result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_s_first(
        const struct seahorse_red_black_tree_map_s_s *const object,
        struct sea_turtle_string **const out) {
    return retrieve_fl(object, out, rock_red_black_tree_map_first);
}

bool seahorse_red_black_tree_map_s_s_last(
        const struct seahorse_red_black_tree_map_s_s *const object,
        struct sea_turtle_string **const out) {
    return retrieve_fl(object, out, rock_red_black_tree_map_last);
}

static bool retrieve_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out,
        bool (func)(const struct rock_red_black_tree_map *const,
                    const void *const,
                    const struct rock_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!key) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->map, key,
                             (const struct rock_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_KEY_NOT_FOUND
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_s_get_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry(object, key, out, rock_red_black_tree_map_get_entry);
}

bool seahorse_red_black_tree_map_s_s_ceiling_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry(object, key, out,
                          rock_red_black_tree_map_ceiling_entry);
}

bool seahorse_red_black_tree_map_s_s_floor_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry(object, key, out,
                          rock_red_black_tree_map_floor_entry);
}

bool seahorse_red_black_tree_map_s_s_higher_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry(object, key, out,
                          rock_red_black_tree_map_higher_entry);
}

bool seahorse_red_black_tree_map_s_s_lower_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct sea_turtle_string *const key,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry(object, key, out,
                          rock_red_black_tree_map_lower_entry);
}

static bool retrieve_entry_fl(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry **const out,
        bool (func)(const struct rock_red_black_tree_map *const,
                    const struct rock_red_black_tree_map_entry **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            &object->map,
            (const struct rock_red_black_tree_map_entry **const) out);
    if (!result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_MAP_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_s_first_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry_fl(object, out, rock_red_black_tree_map_first_entry);
}

bool seahorse_red_black_tree_map_s_s_last_entry(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry_fl(object, out, rock_red_black_tree_map_last_entry);
}

bool seahorse_red_black_tree_map_s_s_remove_entry(
        struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry *const entry) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL;
        return false;
    }
    struct sea_turtle_string *out;
    seagrass_required_true(seahorse_red_black_tree_map_s_s_entry_key(
            object, entry, (const struct sea_turtle_string **) &out));
    seagrass_required_true(sea_turtle_string_invalidate(out));
    seagrass_required_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            object, entry, (const struct sea_turtle_string **) &out));
    seagrass_required_true(sea_turtle_string_invalidate(out));
    seagrass_required_true(rock_red_black_tree_map_remove_entry(
            &object->map,
            (const struct rock_red_black_tree_map_entry *) entry));
    return true;
}

static bool retrieve_entry_np(
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct seahorse_red_black_tree_map_s_s_entry **const out,
        bool (func)(const struct rock_red_black_tree_map_entry *const,
                    const struct rock_red_black_tree_map_entry **const)) {
    assert(func);
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(
            (const struct rock_red_black_tree_map_entry *) entry,
            (const struct rock_red_black_tree_map_entry **) out);
    if (!result) {
        seagrass_required_true(ROCK_RED_BLACK_TREE_MAP_ERROR_END_OF_SEQUENCE
                               == rock_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_END_OF_SEQUENCE;
    }
    return result;
}

bool seahorse_red_black_tree_map_s_s_next_entry(
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry_np(entry, out, rock_red_black_tree_map_next_entry);
}

bool seahorse_red_black_tree_map_s_s_prev_entry(
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct seahorse_red_black_tree_map_s_s_entry **const out) {
    return retrieve_entry_np(entry, out, rock_red_black_tree_map_prev_entry);
}

static bool entry_retrieve(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct sea_turtle_string **const out,
        bool (func)(const struct rock_red_black_tree_map *const,
                    const struct rock_red_black_tree_map_entry *const,
                    const void **const)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(func(
            &object->map,
            (const struct rock_red_black_tree_map_entry *) entry,
            (const void **) out));
    return true;
}

bool seahorse_red_black_tree_map_s_s_entry_key(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct sea_turtle_string **const out) {
    return entry_retrieve(object, entry, out,
                          rock_red_black_tree_map_entry_key);
}

bool seahorse_red_black_tree_map_s_s_entry_get_value(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct sea_turtle_string **const out) {
    return entry_retrieve(object, entry, out,
                          rock_red_black_tree_map_entry_get_value);
}

bool seahorse_red_black_tree_map_s_s_entry_set_value(
        const struct seahorse_red_black_tree_map_s_s *const object,
        const struct seahorse_red_black_tree_map_s_s_entry *const entry,
        const struct sea_turtle_string *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!entry) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_string copy;
    if (!sea_turtle_string_init_with_string(&copy, value)) {
        seagrass_required_true(SEA_TURTLE_STRING_ERROR_MEMORY_ALLOCATION_FAILED
                               == sea_turtle_error);
        seahorse_error =
                SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct sea_turtle_string *out;
    seagrass_required_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            object, entry, (const struct sea_turtle_string **) &out));
    seagrass_required_true(sea_turtle_string_invalidate(out));
    seagrass_required_true(rock_red_black_tree_map_entry_set_value(
            &object->map,
            (const struct rock_red_black_tree_map_entry *) entry,
            &copy));
    return true;
}
