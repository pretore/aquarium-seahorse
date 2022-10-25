#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>

#include "test/cmocka.h"

bool seahorse_array_p_invalidate(struct seahorse_array_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_invalidate(
            &object->array, NULL));
    *object = (struct seahorse_array_p) {0};
    return true;
}

bool seahorse_array_p_init(struct seahorse_array_p *const object,
                           const uintmax_t capacity) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_array_p) {0};
    const bool result = rock_array_init(&object->array,
                                        sizeof(void *),
                                        capacity);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_p_capacity(const struct seahorse_array_p *const object,
                               uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_capacity(
            &object->array, out));
    return true;
}

bool seahorse_array_p_get_length(const struct seahorse_array_p *const object,
                                 uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_get_length(
            &object->array, out));
    return true;
}

bool seahorse_array_p_set_length(struct seahorse_array_p *const object,
                                 const uintmax_t length) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_set_length(&object->array, length);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_p_shrink(struct seahorse_array_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_shrink(&object->array));
    return true;
}

bool seahorse_array_p_add(struct seahorse_array_p *const object,
                          const void *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_add(&object->array, &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_p_add_all(struct seahorse_array_p *const object,
                              const uintmax_t count,
                              const void **const values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        items[i] = &values[i];
    }
    const bool result = rock_array_add_all(&object->array, count, items);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    free(items);
    return result;
}

bool seahorse_array_p_remove_last(struct seahorse_array_p *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_remove_last(&object->array);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_p_insert(struct seahorse_array_p *const object,
                             const uintmax_t at,
                             const void *value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_insert(&object->array, at, &value);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_p_insert_all(struct seahorse_array_p *const object,
                                 const uintmax_t at,
                                 const uintmax_t count,
                                 const void **values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        items[i] = &values[i];
    }
    const bool result = rock_array_insert_all(&object->array, at, count, items);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
    }
    free(items);
    return result;
}

bool seahorse_array_p_remove(struct seahorse_array_p *const object,
                             const uintmax_t at) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_remove(&object->array, at);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_p_remove_all(struct seahorse_array_p *const object,
                                 const uintmax_t at,
                                 const uintmax_t count) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO;
        return false;
    }
    const bool result = rock_array_remove_all(&object->array, at, count);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_p_get(const struct seahorse_array_p *const object,
                          const uintmax_t at,
                          void **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL;
        return false;
    }
    void **value;
    const bool result = rock_array_get(&object->array, at, (void **) &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    } else {
        *out = *value;
    }
    return result;
}

bool seahorse_array_p_set(struct seahorse_array_p *const object,
                          const uintmax_t at,
                          const void *value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = rock_array_set(&object->array, at, &value);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

static bool seahorse_array_p_fl(const struct seahorse_array_p *const object,
                                void ***const out,
                                bool (*const func)(const struct rock_array *,
                                                   void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->array, (void **) out);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_p_first(const struct seahorse_array_p *const object,
                            void ***const out) {
    return seahorse_array_p_fl(object, out, rock_array_first);
}

bool seahorse_array_p_last(const struct seahorse_array_p *const object,
                           void ***const out) {
    return seahorse_array_p_fl(object, out, rock_array_last);
}

static bool seahorse_array_p_np(const struct seahorse_array_p *const object,
                                void **const item,
                                void ***const out,
                                bool (*const func)(const struct rock_array *,
                                                   const void *,
                                                   void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->array, item, (void **) out);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_ITEM_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_END_OF_SEQUENCE: {
                seahorse_error = SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_p_next(const struct seahorse_array_p *const object,
                           void **const item,
                           void ***const out) {
    return seahorse_array_p_np(object, item, out, rock_array_next);
}

bool seahorse_array_p_prev(const struct seahorse_array_p *object,
                           void **const item,
                           void ***const out) {
    return seahorse_array_p_np(object, item, out, rock_array_prev);
}
