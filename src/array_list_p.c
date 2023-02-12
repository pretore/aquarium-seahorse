#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

static bool init(struct seahorse_array_list_p *const object,
                 const uintmax_t capacity) {
    assert(object);
    *object = (struct seahorse_array_list_p) {0};
    const bool result = coral_array_list_init(&object->list,
                                              sizeof(void *),
                                              capacity);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

static void invalidate(struct seahorse_array_list_p *const object) {
    assert(object);
    seagrass_required_true(coral_array_list_invalidate(
            &object->list, NULL));
    *object = (struct seahorse_array_list_p) {0};
}

bool seahorse_array_list_p_invalidate(
        struct seahorse_array_list_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    invalidate(object);
    return true;
}

bool seahorse_array_list_p_init(struct seahorse_array_list_p *const object,
                                const uintmax_t capacity) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    return init(object, capacity);
}

bool seahorse_array_list_p_init_array_list_p(
        struct seahorse_array_list_p *const object,
        const struct seahorse_array_list_p *const other) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!other) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OTHER_IS_NULL;
        return false;
    }
    uintmax_t capacity;
    seagrass_required_true(seahorse_array_list_p_capacity(
            other, &capacity));
    if (!init(object, capacity)) {
        return false;
    }
    uintmax_t count;
    seagrass_required_true(seahorse_array_list_p_get_length(
            other, &count));
    for (uintmax_t i = 0; i < count; i++) {
        void *value;
        seagrass_required_true(seahorse_array_list_p_get(
                other, i, &value));
        seagrass_required_true(seahorse_array_list_p_add(
                object, value));
    }
    return true;
}

bool seahorse_array_list_p_capacity(
        const struct seahorse_array_list_p *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_capacity(
            &object->list, out));
    return true;
}

bool seahorse_array_list_p_get_length(
        const struct seahorse_array_list_p *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_get_length(
            &object->list, out));
    return true;
}

bool seahorse_array_list_p_set_length(
        struct seahorse_array_list_p *const object,
        const uintmax_t length) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_set_length(&object->list, length);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_list_p_shrink(struct seahorse_array_list_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_shrink(&object->list));
    return true;
}

bool seahorse_array_list_p_add(struct seahorse_array_list_p *const object,
                               const void *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_add(&object->list, &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_list_p_add_all(struct seahorse_array_list_p *const object,
                                   const uintmax_t count,
                                   const void **const values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        items[i] = &values[i];
    }
    const bool result = coral_array_list_add_all(&object->list, count, items);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    free(items);
    return result;
}

bool seahorse_array_list_p_remove_last(
        struct seahorse_array_list_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_remove_last(&object->list);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_LIST_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_list_p_insert(struct seahorse_array_list_p *const object,
                                  const uintmax_t at,
                                  const void *value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_insert(&object->list, at, &value);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_list_p_insert_all(
        struct seahorse_array_list_p *const object,
        const uintmax_t at,
        const uintmax_t count,
        const void **values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        items[i] = &values[i];
    }
    const bool result = coral_array_list_insert_all(&object->list, at, count,
                                                    items);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_LIST_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    free(items);
    return result;
}

bool seahorse_array_list_p_remove(struct seahorse_array_list_p *const object,
                                  const uintmax_t at) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_remove(&object->list, at);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_list_p_remove_all(
        struct seahorse_array_list_p *const object,
        const uintmax_t at,
        const uintmax_t count) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    const bool result = coral_array_list_remove_all(&object->list, at, count);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_list_p_get(const struct seahorse_array_list_p *const object,
                               const uintmax_t at,
                               void **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OUT_IS_NULL;
        return false;
    }
    void **value;
    const bool result = coral_array_list_get(&object->list, at,
                                             (void **) &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    } else {
        *out = *value;
    }
    return result;
}

bool seahorse_array_list_p_set(struct seahorse_array_list_p *const object,
                               const uintmax_t at,
                               const void *value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_set(&object->list, at, &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

static bool seahorse_array_list_p_fl(
        const struct seahorse_array_list_p *const object,
        void ***const out,
        bool (*const func)(const struct coral_array_list *,
                           void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->list, (void **) out);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_LIST_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_list_p_first(
        const struct seahorse_array_list_p *const object,
        void ***const out) {
    return seahorse_array_list_p_fl(object, out, coral_array_list_first);
}

bool seahorse_array_list_p_last(
        const struct seahorse_array_list_p *const object,
        void ***const out) {
    return seahorse_array_list_p_fl(object, out, coral_array_list_last);
}

static bool seahorse_array_list_p_np(
        const struct seahorse_array_list_p *const object,
        void **const item,
        void ***const out,
        bool (*const func)(const struct coral_array_list *,
                           const void *,
                           void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->list, item, (void **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_ITEM_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_ITEM_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_END_OF_SEQUENCE: {
                seahorse_error = SEAHORSE_ARRAY_LIST_P_ERROR_END_OF_SEQUENCE;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_list_p_next(
        const struct seahorse_array_list_p *const object,
        void **const item,
        void ***const out) {
    return seahorse_array_list_p_np(object, item, out, coral_array_list_next);
}

bool seahorse_array_list_p_prev(
        const struct seahorse_array_list_p *object,
        void **const item,
        void ***const out) {
    return seahorse_array_list_p_np(object, item, out, coral_array_list_prev);
}
