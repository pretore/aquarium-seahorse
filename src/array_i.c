#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>
#include <sea-turtle.h>

#include "test/cmocka.h"

static void on_destroy(void *a) {
    seagrass_required_true(sea_turtle_integer_invalidate(a));
}

bool seahorse_array_i_invalidate(struct seahorse_array_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_invalidate(
            &object->array, on_destroy));
    *object = (struct seahorse_array_i) {0};
    return true;
}

bool seahorse_array_i_init(struct seahorse_array_i *const object,
                           const uintmax_t capacity) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_array_i) {0};
    const bool result = rock_array_init(&object->array,
                                        sizeof(struct sea_turtle_integer),
                                        capacity);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_i_capacity(const struct seahorse_array_i *const object,
                               uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_capacity(
            &object->array, out));
    return true;
}

bool seahorse_array_i_get_length(const struct seahorse_array_i *const object,
                                 uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_get_length(
            &object->array, out));
    return true;
}

bool seahorse_array_i_set_length(struct seahorse_array_i *const object,
                                 const uintmax_t length) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    uintmax_t count;
    seagrass_required_true(rock_array_get_length(
            &object->array, &count));
    if (count > length) { /* destroy integers before they have been removed */
        for (uintmax_t i = length; i < count; i++) {
            void *item;
            seagrass_required_true(rock_array_get(
                    &object->array, i, &item));
            on_destroy(item);
        }
    }
    if (!rock_array_set_length(&object->array, length)) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (count < length) { /* zero initialize the newly added integers */
        for (uintmax_t i = count; i < length; i++) {
            struct sea_turtle_integer *item;
            seagrass_required_true(rock_array_get(
                    &object->array, i, (void **) &item));
            seagrass_required_true(sea_turtle_integer_init_with_uintmax_t(
                    item, 0));
        }
    }
    return true;
}

bool seahorse_array_i_shrink(struct seahorse_array_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(rock_array_shrink(&object->array));
    return true;
}

bool seahorse_array_i_add(struct seahorse_array_i *const object,
                          const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_integer i;
    seagrass_required_true(sea_turtle_integer_init_with_integer(
            &i, value));
    const bool result = rock_array_add(&object->array, &i);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        seagrass_required_true(sea_turtle_integer_invalidate(&i));
    }
    return result;
}

bool seahorse_array_i_add_all(struct seahorse_array_i *const object,
                              const uintmax_t count,
                              const struct sea_turtle_integer *const values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count,
                                     sizeof(struct sea_turtle_integer),
                                     &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct sea_turtle_integer *integers = malloc(size);
    if (!integers) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        seagrass_required_true(sea_turtle_integer_init_with_integer(
                &integers[i], &values[i]));
        items[i] = &integers[i];
    }
    const bool result = rock_array_add_all(&object->array, count, items);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        for (uintmax_t i = 0; i < count; i++) {
            seagrass_required_true(sea_turtle_integer_invalidate(&integers[i]));
        }
    }
    free(items);
    free(integers);
    return result;
}

bool seahorse_array_i_remove_last(struct seahorse_array_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    struct sea_turtle_integer *i;
    if (!rock_array_last(&object->array, (void **) &i)) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_ARRAY_IS_EMPTY;
        return false;
    }
    on_destroy(i);
    seagrass_required_true(rock_array_remove_last(&object->array));
    return true;
}

bool seahorse_array_i_insert(struct seahorse_array_i *const object,
                             const uintmax_t at,
                             const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_integer i;
    seagrass_required_true(sea_turtle_integer_init_with_integer(
            &i, value));
    const bool result = rock_array_insert(&object->array, at, &i);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(sea_turtle_integer_invalidate(&i));
    }
    return result;
}

bool seahorse_array_i_insert_all(struct seahorse_array_i *const object,
                                 const uintmax_t at,
                                 const uintmax_t count,
                                 const struct sea_turtle_integer *values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count,
                                     sizeof(struct sea_turtle_integer),
                                     &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct sea_turtle_integer *integers = malloc(size);
    if (!integers) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        seagrass_required_true(sea_turtle_integer_init_with_integer(
                &integers[i], &values[i]));
        items[i] = &integers[i];
    }
    const bool result = rock_array_insert_all(&object->array, at, count, items);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_I_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        for (uintmax_t i = 0; i < count; i++) {
            seagrass_required_true(sea_turtle_integer_invalidate(&integers[i]));
        }
    }
    free(items);
    free(integers);
    return result;
}

bool seahorse_array_i_remove(struct seahorse_array_i *const object,
                             const uintmax_t at) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    struct sea_turtle_integer *i;
    if (!rock_array_get(&object->array, at, (void **) &i)) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
        return false;
    }
    on_destroy(i);
    seagrass_required_true(rock_array_remove_last(&object->array));
    return true;
}

bool seahorse_array_i_remove_all(struct seahorse_array_i *const object,
                                 const uintmax_t at,
                                 const uintmax_t count) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    const bool result = rock_array_remove_all(&object->array, at, count);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_i_get(const struct seahorse_array_i *const object,
                          const uintmax_t at,
                          struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = rock_array_get(&object->array, at, (void **) out);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

static bool seahorse_array_i_fl(const struct seahorse_array_i *const object,
                                struct sea_turtle_integer **const out,
                                bool (*const func)(const struct rock_array *,
                                                   void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = rock_array_first(&object->array, (void **) out);
    if (!result) {
        seagrass_required_true(ROCK_ARRAY_ERROR_ARRAY_IS_EMPTY
                               == rock_error);
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_ARRAY_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_i_first(const struct seahorse_array_i *const object,
                            struct sea_turtle_integer **const out) {
    return seahorse_array_i_fl(object, out, rock_array_first);
}

bool seahorse_array_i_last(const struct seahorse_array_i *const object,
                           struct sea_turtle_integer **const out) {
    return seahorse_array_i_fl(object, out, rock_array_last);
}

static bool seahorse_array_i_np(const struct seahorse_array_i *const object,
                                const struct sea_turtle_integer *const item,
                                struct sea_turtle_integer **const out,
                                bool (*const func)(const struct rock_array *,
                                                   const void *,
                                                   void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->array, item, (void **) out);
    if (!result) {
        switch (rock_error) {
            default: {
                seagrass_required_true(false);
            }
            case ROCK_ARRAY_ERROR_ITEM_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_I_ERROR_ITEM_IS_OUT_OF_BOUNDS;
                break;
            }
            case ROCK_ARRAY_ERROR_END_OF_SEQUENCE: {
                seahorse_error = SEAHORSE_ARRAY_I_ERROR_END_OF_SEQUENCE;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_i_next(const struct seahorse_array_i *const object,
                           const struct sea_turtle_integer *const item,
                           struct sea_turtle_integer **const out) {
    return seahorse_array_i_np(object, item, out, rock_array_next);
}

bool seahorse_array_i_prev(const struct seahorse_array_i *const object,
                           const struct sea_turtle_integer *const item,
                           struct sea_turtle_integer **const out) {
    return seahorse_array_i_np(object, item, out, rock_array_prev);
}
