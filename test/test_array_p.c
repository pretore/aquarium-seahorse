#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seahorse.h>
#include <time.h>

#include "test/cmocka.h"

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_invalidate(NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object = {};
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_init(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    calloc_is_overridden = true;
    assert_false(seahorse_array_p_init(&object, 10));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 10));
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_capacity(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_capacity((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.array.capacity = check;
    uintmax_t out;
    assert_true(seahorse_array_p_capacity(&object, &out));
    assert_int_equal(out, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_get_length(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_get_length((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.array.length = check;
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_set_length(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    calloc_is_overridden = true;
    assert_false(seahorse_array_p_set_length(&object, 1));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 1));
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_shrink_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_shrink(NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_shrink(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 10));
    assert_int_equal(object.array.capacity, 10);
    assert_true(seahorse_array_p_shrink(&object));
    assert_int_equal(object.array.capacity, 0);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_add(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    calloc_is_overridden = true;
    assert_false(seahorse_array_p_add(&object, 0));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object, (void *) (rand() % UINTPTR_MAX)));
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_add_all(NULL, 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_add_all((void *) 1, 0, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_values_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_add_all((void *) 1, 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *values[] = {0, (void *) 1};
    const uintmax_t count = sizeof(values) / sizeof(void *);
    calloc_is_overridden = true;
    assert_false(seahorse_array_p_add_all(&object, count, values));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *values[] = {(void *)2, (void *)1, 0};
    const uintmax_t count = sizeof(values) / sizeof(void *);
    assert_true(seahorse_array_p_add_all(&object, count, values));
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, count);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_remove_last(NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last_error_on_array_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_false(seahorse_array_p_remove_last(&object));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *values[] = {(void *)2, (void *)1, 0};
    const uintmax_t count = sizeof(values) / sizeof(void *);
    assert_true(seahorse_array_p_add_all(&object, count, values));
    assert_true(seahorse_array_p_remove_last(&object));
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, count - 1);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_insert(NULL, 0, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_index_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_false(seahorse_array_p_insert(&object, 0, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object, (const void *) (rand() % UINTPTR_MAX)));
    assert_true(seahorse_array_p_shrink(&object));
    realloc_is_overridden = true;
    assert_false(seahorse_array_p_insert(&object, 0, 0));
    realloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object, (const void *) (rand() % UINTPTR_MAX)));
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(seahorse_array_p_insert(&object, 0, 0));
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 2);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}





static void check_insert_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_insert_all(NULL, 0, 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_insert_all((void *) 1, 0, 0, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_values_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_insert_all((void *) 1, 0, 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_index_out_of_bounds(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *values[] = {0, (void *)1};
    const uintmax_t count = sizeof(values) / sizeof(uintmax_t);
    assert_false(seahorse_array_p_insert_all(&object, 0, count, values));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object,(void *) (rand() % UINTPTR_MAX)));
    assert_true(seahorse_array_p_shrink(&object));
    const void *values[] = {0, (void *) 1};
    const uintmax_t count = sizeof(values) / sizeof(uintmax_t);
    realloc_is_overridden = true;
    assert_false(seahorse_array_p_insert_all(&object, 0, count, values));
    realloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object, (void *) (rand() % UINTPTR_MAX)));
    const void *values[] = {0, (void *) 1};
    const uintmax_t count = sizeof(values) / sizeof(uintmax_t);
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(seahorse_array_p_insert_all(&object, 0, count, values));
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 3);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_remove(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_false(seahorse_array_p_remove(&object, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_add(
            &object, (void *) (rand() % UINTPTR_MAX)));
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(seahorse_array_p_remove(&object, 0));
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_remove_all(NULL, 0, 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_remove_all((void *) 1, 0, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_false(seahorse_array_p_remove_all(&object, 0, 10));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *values[] = {(void *)2, (void *)1, 0, (void *)5, (void *)5};
    uintmax_t count = sizeof(values) / sizeof(uintmax_t);
    assert_true(seahorse_array_p_add_all(&object, count, values));
    uintmax_t out;
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, count);
    assert_true(seahorse_array_p_remove_all(&object, 1, 3));
    assert_true(seahorse_array_p_get_length(&object, &out));
    assert_int_equal(out, count - 3);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_get(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_get((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    void *out;
    assert_false(seahorse_array_p_get(&object, 0, &out));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *check = (void *)(rand() % UINTPTR_MAX);
    assert_true(seahorse_array_p_add(&object, check));
    void *out;
    assert_true(seahorse_array_p_get(&object, 0, &out));
    assert_ptr_equal(out, check);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_set(NULL, 0, 0));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_false(seahorse_array_p_set(&object, 10, (void *)21));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    void *check = (void *) (rand() % UINTPTR_MAX);
    assert_true(seahorse_array_p_add(&object, check));
    void *out;
    assert_true(seahorse_array_p_get(&object, 0, &out));
    check += rand() % UINTPTR_MAX;
    assert_ptr_not_equal(out, check);
    assert_true(seahorse_array_p_set(&object, 0, check));
    assert_true(seahorse_array_p_get(&object, 0, &out));
    assert_ptr_equal(out, check);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_array_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    void **out;
    assert_false(seahorse_array_p_first(&object, &out));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *check = (void *)(rand() % UINTPTR_MAX);
    assert_true(seahorse_array_p_add(&object, check));
    void **out;
    assert_true(seahorse_array_p_first(&object, &out));
    assert_ptr_equal(*out, check);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_array_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    void **out;
    assert_false(seahorse_array_p_last(&object, &out));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    const void *check = (void *) (rand() % UINTPTR_MAX);
    assert_true(seahorse_array_p_add(&object, check));
    void **out;
    assert_true(seahorse_array_p_last(&object, &out));
    assert_ptr_equal(*out, check);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_next(NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_next((void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_next((void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 1));
    void **item = (void **) 1;
    assert_false(seahorse_array_p_next(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 1));
    void **item;
    assert_true(seahorse_array_p_first(&object, &item));
    assert_false(seahorse_array_p_next(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE, seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 2));
    void **item;
    assert_true(seahorse_array_p_first(&object, &item));
    assert_true(seahorse_array_p_next(&object, item, &item));
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_prev(NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_prev((void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_p_prev((void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 1));
    void **item = (void **) 1;
    assert_false(seahorse_array_p_prev(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 1));
    void **item;
    assert_true(seahorse_array_p_last(&object, &item));
    assert_false(seahorse_array_p_prev(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE, seahorse_error);
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_p object;
    assert_true(seahorse_array_p_init(&object, 0));
    assert_true(seahorse_array_p_set_length(&object, 2));
    void **item;
    assert_true(seahorse_array_p_last(&object, &item));
    assert_true(seahorse_array_p_prev(&object, item, &item));
    assert_true(seahorse_array_p_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_invalidate_error_on_object_is_null),
            cmocka_unit_test(check_invalidate),
            cmocka_unit_test(check_init_error_on_object_is_null),
            cmocka_unit_test(check_init_error_on_memory_allocation_failed),
            cmocka_unit_test(check_init),
            cmocka_unit_test(check_capacity_error_on_object_is_null),
            cmocka_unit_test(check_capacity_error_on_out_is_null),
            cmocka_unit_test(check_capacity),
            cmocka_unit_test(check_get_length_error_on_object_is_null),
            cmocka_unit_test(check_get_length_error_on_out_is_null),
            cmocka_unit_test(check_get_length),
            cmocka_unit_test(check_set_length_error_on_object_is_null),
            cmocka_unit_test(check_set_length_error_on_memory_allocation_failed),
            cmocka_unit_test(check_set_length),
            cmocka_unit_test(check_shrink_error_on_object_is_null),
            cmocka_unit_test(check_shrink),
            cmocka_unit_test(check_add_error_on_object_is_null),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_all_error_on_object_is_null),
            cmocka_unit_test(check_add_all_error_on_count_is_zero),
            cmocka_unit_test(check_add_all_error_on_values_is_null),
            cmocka_unit_test(check_add_all_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add_all),
            cmocka_unit_test(check_remove_last_error_on_object_is_null),
            cmocka_unit_test(check_remove_last_error_on_array_is_null),
            cmocka_unit_test(check_remove_last),
            cmocka_unit_test(check_insert_error_on_object_is_null),
            cmocka_unit_test(check_insert_error_on_index_out_of_bounds),
            cmocka_unit_test(check_insert_error_on_memory_allocation_failed),
            cmocka_unit_test(check_insert),
            cmocka_unit_test(check_insert_all_error_on_object_is_null),
            cmocka_unit_test(check_insert_all_error_on_count_is_zero),
            cmocka_unit_test(check_insert_all_error_on_values_is_null),
            cmocka_unit_test(check_insert_all_error_on_index_out_of_bounds),
            cmocka_unit_test(check_insert_all_error_on_memory_allocation_failed),
            cmocka_unit_test(check_insert_all),
            cmocka_unit_test(check_remove_all_error_on_object_is_null),
            cmocka_unit_test(check_remove_all_error_on_count_is_zero),
            cmocka_unit_test(check_remove_all_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_remove_all),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_first_error_on_object_is_null),
            cmocka_unit_test(check_first_error_on_out_is_null),
            cmocka_unit_test(check_first_error_on_array_is_empty),
            cmocka_unit_test(check_first),
            cmocka_unit_test(check_last_error_on_object_is_null),
            cmocka_unit_test(check_last_error_on_out_is_null),
            cmocka_unit_test(check_last_error_on_array_is_empty),
            cmocka_unit_test(check_last),
            cmocka_unit_test(check_next_error_on_object_is_null),
            cmocka_unit_test(check_next_error_on_item_is_null),
            cmocka_unit_test(check_next_error_on_out_is_null),
            cmocka_unit_test(check_next_error_on_item_is_out_of_bounds),
            cmocka_unit_test(check_next_error_on_item_end_of_sequence),
            cmocka_unit_test(check_next),
            cmocka_unit_test(check_prev_error_on_object_is_null),
            cmocka_unit_test(check_prev_error_on_item_is_null),
            cmocka_unit_test(check_prev_error_on_out_is_null),
            cmocka_unit_test(check_prev_error_on_item_is_out_of_bounds),
            cmocka_unit_test(check_prev_error_on_item_end_of_sequence),
            cmocka_unit_test(check_prev),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
