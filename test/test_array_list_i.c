#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <seahorse.h>
#include <sea-turtle.h>
#include <time.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_invalidate(NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object = {};
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_init(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    calloc_is_overridden = true;
    assert_false(seahorse_array_list_i_init(&object, 10));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 10));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_capacity(NULL, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_capacity((void *)1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_capacity(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.list.array.capacity = check;
    uintmax_t out;
    assert_true(seahorse_array_list_i_capacity(&object, &out));
    assert_int_equal(out, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_get_length(NULL, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_get_length((void *)1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_length(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.list.array.length = check;
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_set_length(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    calloc_is_overridden = true;
    assert_false(seahorse_array_list_i_set_length(&object, 1));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_length(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 10));
    assert_true(seahorse_array_list_i_set_length(&object, 1));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_shrink_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_shrink(NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_shrink(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 10));
    assert_int_equal(object.list.array.capacity, 10);
    assert_true(seahorse_array_list_i_shrink(&object));
    assert_int_equal(object.list.array.capacity, 0);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_add(NULL, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_add((void *)1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_VALUE_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init(&i));
    calloc_is_overridden = true;
    assert_false(seahorse_array_list_i_add(&object, &i));
    calloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_list_i_add(&object, &i));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_add_all(NULL, 1, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_add_all((void *)1, 0, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_values_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_add_all((void *)1, 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_VALUES_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer values[] = {
            {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    calloc_is_overridden = realloc_is_overridden = true;
    assert_false(seahorse_array_list_i_add_all(&object, count, values));
    calloc_is_overridden = realloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_all(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer values[] = {
            {0}, {0}, {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(sea_turtle_integer_init_with_uintmax_t(&values[i], i));
    }
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_list_i_add_all(&object, count, values));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, count);
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(sea_turtle_integer_invalidate(&values[i]));
    }
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_remove_last(NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last_error_on_array_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_false(seahorse_array_list_i_remove_last(&object));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_LIST_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_list_i_add(&object, &i));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_remove_last(&object));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_insert(NULL, 0, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_insert((void *)1, 0, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_VALUE_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_index_out_of_bounds(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_false(seahorse_array_list_i_insert(&object, 0, &i));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &i));
    assert_true(seahorse_array_list_i_shrink(&object));
    realloc_is_overridden = true;
    assert_false(seahorse_array_list_i_insert(&object, 0, &i));
    realloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object,&i));
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(seahorse_array_list_i_insert(&object, 0, &i));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 2);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_insert_all(NULL, 0, 1, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_insert_all((void *)1, 0, 0, (void *)1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_values_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_insert_all((void *)1, 0, 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_VALUES_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_index_out_of_bounds(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer values[] = {
            {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    assert_false(seahorse_array_list_i_insert_all(&object, 0, count, values));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &i));
    assert_true(seahorse_array_list_i_shrink(&object));
    struct sea_turtle_integer values[] = {
            {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    calloc_is_overridden = realloc_is_overridden = true;
    assert_false(seahorse_array_list_i_insert_all(&object, 0, count, values));
    calloc_is_overridden = realloc_is_overridden = false;
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_insert_all(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &i));
    struct sea_turtle_integer values[] = {
            {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    assert_true(seahorse_array_list_i_insert_all(&object, 0, count, values));
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_remove(NULL, 0));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_false(seahorse_array_list_i_remove(&object, 0));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer i;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &i, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &i));
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 1);
    assert_true(seahorse_array_list_i_remove(&object, 0));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(sea_turtle_integer_invalidate(&i));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_remove_all(NULL, 0, 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_count_is_zero(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_remove_all((void *) 1, 0, 0));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_COUNT_IS_ZERO, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_false(seahorse_array_list_i_remove_all(&object, 0, 10));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_all(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer values[] = {
            {0}, {0}, {0}, {0}, {0}
    };
    const uintmax_t count = sizeof(values) / sizeof(struct sea_turtle_integer);
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(sea_turtle_integer_init_with_uintmax_t(&values[i], i));
    }
    uintmax_t out;
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, 0);
    assert_true(seahorse_array_list_i_add_all(&object, count, values));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, count);
    assert_true(seahorse_array_list_i_remove_all(&object, 1, 3));
    assert_true(seahorse_array_list_i_get_length(&object, &out));
    assert_int_equal(out, count - 3);
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(sea_turtle_integer_invalidate(&values[i]));
    }
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_get(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_get((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_index_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer *out;
    assert_false(seahorse_array_list_i_get(&object, 0, &out));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_INDEX_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer check;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &check, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &check));
    struct sea_turtle_integer *out;
    assert_true(seahorse_array_list_i_get(&object, 0, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &check), 0);
    assert_true(sea_turtle_integer_invalidate(&check));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_array_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer *out;
    assert_false(seahorse_array_list_i_first(&object, &out));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_LIST_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer check;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &check, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &check));
    struct sea_turtle_integer *out;
    assert_true(seahorse_array_list_i_first(&object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &check), 0);
    assert_true(sea_turtle_integer_invalidate(&check));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_array_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer *out;
    assert_false(seahorse_array_list_i_last(&object, &out));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_LIST_IS_EMPTY, seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    struct sea_turtle_integer check;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &check, rand() % UINTMAX_MAX));
    assert_true(seahorse_array_list_i_add(&object, &check));
    struct sea_turtle_integer *out;
    assert_true(seahorse_array_list_i_last(&object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &check), 0);
    assert_true(sea_turtle_integer_invalidate(&check));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_next(NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_next((void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_next((void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 1));
    struct sea_turtle_integer *item = (struct sea_turtle_integer *) 1;
    assert_false(seahorse_array_list_i_next(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 1));
    struct sea_turtle_integer *item;
    assert_true(seahorse_array_list_i_first(&object, &item));
    assert_false(seahorse_array_list_i_next(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_END_OF_SEQUENCE, seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 2));
    struct sea_turtle_integer *item;
    assert_true(seahorse_array_list_i_first(&object, &item));
    assert_true(seahorse_array_list_i_next(&object, item, &item));
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_prev(NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OBJECT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_prev((void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_array_list_i_prev((void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_OUT_IS_NULL, seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_out_of_bounds(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 1));
    struct sea_turtle_integer *item = (struct sea_turtle_integer *) 1;
    assert_false(seahorse_array_list_i_prev(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_ITEM_IS_OUT_OF_BOUNDS,
                     seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 1));
    struct sea_turtle_integer *item;
    assert_true(seahorse_array_list_i_last(&object, &item));
    assert_false(seahorse_array_list_i_prev(&object, item, &item));
    assert_int_equal(SEAHORSE_ARRAY_LIST_I_ERROR_END_OF_SEQUENCE, seahorse_error);
    assert_true(seahorse_array_list_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_array_list_i object;
    assert_true(seahorse_array_list_i_init(&object, 0));
    assert_true(seahorse_array_list_i_set_length(&object, 2));
    struct sea_turtle_integer *item;
    assert_true(seahorse_array_list_i_last(&object, &item));
    assert_true(seahorse_array_list_i_prev(&object, item, &item));
    assert_true(seahorse_array_list_i_invalidate(&object));
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
            cmocka_unit_test(check_add_error_on_value_is_null),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_all_error_on_object_is_null),
            cmocka_unit_test(check_add_all_error_on_count_is_zero),
            cmocka_unit_test(check_add_all_error_on_values_is_null),
            cmocka_unit_test(check_add_all_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add_all),
            cmocka_unit_test(check_remove_last_error_on_object_is_null),
            cmocka_unit_test(check_remove_last_error_on_array_is_empty),
            cmocka_unit_test(check_remove_last),
            cmocka_unit_test(check_insert_error_on_object_is_null),
            cmocka_unit_test(check_insert_error_on_value_is_null),
            cmocka_unit_test(check_insert_error_on_index_out_of_bounds),
            cmocka_unit_test(check_insert_error_on_memory_allocation_failed),
            cmocka_unit_test(check_insert),
            cmocka_unit_test(check_insert_all_error_on_object_is_null),
            cmocka_unit_test(check_insert_all_error_on_count_is_zero),
            cmocka_unit_test(check_insert_all_error_on_values_is_null),
            cmocka_unit_test(check_insert_all_error_on_index_out_of_bounds),
            cmocka_unit_test(check_insert_all_error_on_memory_allocation_failed),
            cmocka_unit_test(check_insert_all),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_remove_all_error_on_object_is_null),
            cmocka_unit_test(check_remove_all_error_on_count_is_zero),
            cmocka_unit_test(check_remove_all_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_remove_all),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_index_is_out_of_bounds),
            cmocka_unit_test(check_get),
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
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
