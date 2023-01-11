#include <stdlib.h>
#include <assert.h>
#include <seagrass.h>
#include <seahorse.h>
#include <sea-turtle.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

static void on_destroy(void *a) {
    seagrass_required_true(sea_turtle_integer_invalidate(a));
}

bool seahorse_array_list_i_invalidate(
        struct seahorse_array_list_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_invalidate(
            &object->list, on_destroy));
    *object = (struct seahorse_array_list_i) {0};
    return true;
}

bool seahorse_array_list_i_init(struct seahorse_array_list_i *const object,
                                const uintmax_t capacity) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_array_list_i) {0};
    const bool result = coral_array_list_init(&object->list,
                                              sizeof(struct sea_turtle_integer),
                                              capacity);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_array_list_i_capacity(
        const struct seahorse_array_list_i *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_capacity(
            &object->list, out));
    return true;
}

bool seahorse_array_list_i_get_length(
        const struct seahorse_array_list_i *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_get_length(
            &object->list, out));
    return true;
}

bool seahorse_array_list_i_set_length(
        struct seahorse_array_list_i *const object,
        const uintmax_t length) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    uintmax_t count;
    seagrass_required_true(coral_array_list_get_length(
            &object->list, &count));
    if (count > length) { /* destroy integers before they have been removed */
        for (uintmax_t i = length; i < count; i++) {
            void *item;
            seagrass_required_true(coral_array_list_get(
                    &object->list, i, &item));
            on_destroy(item);
        }
    }
    if (!coral_array_list_set_length(&object->list, length)) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (count < length) { /* zero initialize the newly added integers */
        for (uintmax_t i = count; i < length; i++) {
            struct sea_turtle_integer *item;
            seagrass_required_true(coral_array_list_get(
                    &object->list, i, (void **) &item));
            seagrass_required_true(sea_turtle_integer_init_with_uintmax_t(
                    item, 0));
        }
    }
    return true;
}

bool seahorse_array_list_i_shrink(struct seahorse_array_list_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_array_list_shrink(&object->list));
    return true;
}

bool seahorse_array_list_i_add(struct seahorse_array_list_i *const object,
                               const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_integer i;
    seagrass_required_true(sea_turtle_integer_init_with_integer(
            &i, value));
    const bool result = coral_array_list_add(&object->list, &i);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        seagrass_required_true(sea_turtle_integer_invalidate(&i));
    }
    return result;
}

bool seahorse_array_list_i_add_all(
        struct seahorse_array_list_i *const object,
        const uintmax_t count,
        const struct sea_turtle_integer *const values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count,
                                     sizeof(struct sea_turtle_integer),
                                     &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct sea_turtle_integer *integers = malloc(size);
    if (!integers) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        seagrass_required_true(sea_turtle_integer_init_with_integer(
                &integers[i], &values[i]));
        items[i] = &integers[i];
    }
    const bool result = coral_array_list_add_all(&object->list, count, items);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        for (uintmax_t i = 0; i < count; i++) {
            seagrass_required_true(sea_turtle_integer_invalidate(&integers[i]));
        }
    }
    free(items);
    free(integers);
    return result;
}

bool seahorse_array_list_i_remove_last(
        struct seahorse_array_list_i *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    struct sea_turtle_integer *i;
    if (!coral_array_list_last(&object->list, (void **) &i)) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_LIST_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_LIST_IS_EMPTY;
        return false;
    }
    on_destroy(i);
    seagrass_required_true(coral_array_list_remove_last(&object->list));
    return true;
}

bool seahorse_array_list_i_insert(
        struct seahorse_array_list_i *const object,
        const uintmax_t at,
        const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    struct sea_turtle_integer i;
    seagrass_required_true(sea_turtle_integer_init_with_integer(
            &i, value));
    const bool result = coral_array_list_insert(&object->list, at, &i);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_ARRAY_LIST_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
                break;
            }
        }
        seagrass_required_true(sea_turtle_integer_invalidate(&i));
    }
    return result;
}

bool seahorse_array_list_i_insert_all(
        struct seahorse_array_list_i *const object,
        const uintmax_t at,
        const uintmax_t count,
        const struct sea_turtle_integer *values) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    if (!values) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_VALUES_IS_NULL;
        return false;
    }
    uintmax_t size;
    if (!seagrass_uintmax_t_multiply(count,
                                     sizeof(struct sea_turtle_integer),
                                     &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    struct sea_turtle_integer *integers = malloc(size);
    if (!integers) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        return false;
    }
    if (!seagrass_uintmax_t_multiply(count, sizeof(void *), &size)
        || size > SIZE_MAX) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seahorse_error || size > SIZE_MAX);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    const void **items = malloc(size);
    if (!items) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
        free(integers);
        return false;
    }
    for (uintmax_t i = 0; i < count; i++) {
        seagrass_required_true(sea_turtle_integer_init_with_integer(
                &integers[i], &values[i]));
        items[i] = &integers[i];
    }
    const bool result = coral_array_list_insert_all(&object->list, at, count,
                                                    items);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_ARRAY_LIST_ERROR_INDEX_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
                break;
            }
            case CORAL_ARRAY_LIST_ERROR_MEMORY_ALLOCATION_FAILED: {
                seahorse_error =
                        SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED;
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

bool seahorse_array_list_i_remove(struct seahorse_array_list_i *const object,
                                  const uintmax_t at) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    struct sea_turtle_integer *i;
    if (!coral_array_list_get(&object->list, at, (void **) &i)) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
        return false;
    }
    on_destroy(i);
    seagrass_required_true(coral_array_list_remove_last(&object->list));
    return true;
}

bool seahorse_array_list_i_remove_all(
        struct seahorse_array_list_i *const object,
        const uintmax_t at,
        const uintmax_t count) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!count) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO;
        return false;
    }
    uintmax_t length;
    seagrass_required_true(coral_array_list_get_length(
            &object->list, &length));
    if (at >= length) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
        return false;
    }
    struct sea_turtle_integer *i;
    for (uintmax_t o = at, p = 0; o < length && p < count; o++, p++) {
        seagrass_required_true(coral_array_list_get(
                &object->list, o, (void **) &i));
        seagrass_required_true(sea_turtle_integer_invalidate(i));
    }
    const bool result = coral_array_list_remove_all(&object->list, at, count);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

bool seahorse_array_list_i_get(const struct seahorse_array_list_i *const object,
                               const uintmax_t at,
                               struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_get(&object->list, at, (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_INDEX_IS_OUT_OF_BOUNDS
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS;
    }
    return result;
}

static bool
seahorse_array_list_i_fl(const struct seahorse_array_list_i *const object,
                         struct sea_turtle_integer **const out,
                         bool (*const func)(const struct coral_array_list *,
                                            void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_array_list_first(&object->list, (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_ARRAY_LIST_ERROR_LIST_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_LIST_IS_EMPTY;
    }
    return result;
}

bool seahorse_array_list_i_first(
        const struct seahorse_array_list_i *const object,
        struct sea_turtle_integer **const out) {
    return seahorse_array_list_i_fl(object, out, coral_array_list_first);
}

bool seahorse_array_list_i_last(
        const struct seahorse_array_list_i *const object,
        struct sea_turtle_integer **const out) {
    return seahorse_array_list_i_fl(object, out, coral_array_list_last);
}

static bool
seahorse_array_list_i_np(const struct seahorse_array_list_i *const object,
                         const struct sea_turtle_integer *const item,
                         struct sea_turtle_integer **const out,
                         bool (*const func)(const struct coral_array_list *,
                                            const void *,
                                            void **)) {
    assert(func);
    if (!object) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = func(&object->list, item, (void **) out);
    if (!result) {
        switch (coral_error) {
            default: {
                seagrass_required_true(false);
            }
            case CORAL_ARRAY_LIST_ERROR_ITEM_IS_OUT_OF_BOUNDS: {
                seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_OUT_OF_BOUNDS;
                break;
            }
            case CORAL_ARRAY_LIST_ERROR_END_OF_SEQUENCE: {
                seahorse_error = SEAHORSE_ARRAY_LIST_I_ERROR_END_OF_SEQUENCE;
                break;
            }
        }
    }
    return result;
}

bool seahorse_array_list_i_next(
        const struct seahorse_array_list_i *const object,
        const struct sea_turtle_integer *const item,
        struct sea_turtle_integer **const out) {
    return seahorse_array_list_i_np(object, item, out, coral_array_list_next);
}

bool seahorse_array_list_i_prev(
        const struct seahorse_array_list_i *const object,
        const struct sea_turtle_integer *const item,
        struct sea_turtle_integer **const out) {
    return seahorse_array_list_i_np(object, item, out, coral_array_list_prev);
}
