#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <time.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object = {};
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t check = (rand() % UINTMAX_MAX);
    struct seahorse_red_black_tree_set_i object = {
            .set.tree.count = check
    };
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_add(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_add((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_already_exists(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_false(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_add(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}


static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_value_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_false(seahorse_red_black_tree_set_i_remove(&object, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_remove(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    bool result;
    assert_true(seahorse_red_black_tree_set_i_contains(
            &object, &value, &result));
    assert_false(result);
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_contains(
            &object, &value, &result));
    assert_true(result);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    bool result;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_contains(
            &object, &value, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_get(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &item));
    assert_ptr_not_equal(item, &value);
    assert_int_equal(sea_turtle_integer_compare(item, &value), 0);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    const struct sea_turtle_integer *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_get(&object, &value, &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_ceiling(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_ceiling(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    assert_true(seahorse_red_black_tree_set_i_ceiling(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    const struct sea_turtle_integer *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_ceiling(
            &object, &value[0], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_floor(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_floor(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    assert_true(seahorse_red_black_tree_set_i_floor(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    const struct sea_turtle_integer *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_floor(
            &object, &value[1], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_higher(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_higher(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    assert_true(seahorse_red_black_tree_set_i_higher(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    const struct sea_turtle_integer *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_higher(
            &object, &value[0], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_lower(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_lower(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    assert_true(seahorse_red_black_tree_set_i_lower(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    const struct sea_turtle_integer *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_lower(
            &object, &value[1], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_first(&object, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *item;
    assert_false(seahorse_red_black_tree_set_i_last(&object, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_remove_item(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_remove_item((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &item));
    assert_true(seahorse_red_black_tree_set_i_remove_item(&object, item));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_next(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_next((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &item));
    assert_true(seahorse_red_black_tree_set_i_next(item, &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &item));
    assert_false(seahorse_red_black_tree_set_i_next(item, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_prev(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_prev((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &item));
    assert_true(seahorse_red_black_tree_set_i_prev(item, &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_integer_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *item;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &item));
    assert_false(seahorse_red_black_tree_set_i_prev(item, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_set_i_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_init_set_i(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_set_i_error_on_other_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_init_set_i(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OTHER_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_set_i_case_empty_set(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct seahorse_red_black_tree_set_i copy;
    assert_true(seahorse_red_black_tree_set_i_init_set_i(
            &copy, (const struct seahorse_stream_i *) &object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&copy, &count));
    assert_int_equal(count, 0);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&copy));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_set_i(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    struct seahorse_red_black_tree_set_i copy;
    assert_true(seahorse_red_black_tree_set_i_init_set_i(
            &copy, (const struct seahorse_stream_i *) &object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&copy, &count));
    assert_int_equal(count, limit);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&copy));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_set_i_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    struct seahorse_red_black_tree_set_i copy;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_init_set_i(
            &copy, (const struct seahorse_stream_i *) &object));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_count(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    uintmax_t count;
    // as collection
    assert_true(seahorse_collection_i_count(
            (const struct seahorse_collection_i *) &object, &count));
    assert_int_equal(count, limit);
    count = 0;
    // as set
    assert_true(seahorse_set_i_count(
            (const struct seahorse_set_i *) &object, &count));
    assert_int_equal(count, limit);
    count = 0;
    // as ordered set
    assert_true(seahorse_ordered_set_i_count(
            (const struct seahorse_ordered_set_i *) &object, &count));
    assert_int_equal(count, limit);
    count = 0;
    // as sorted set
    assert_true(seahorse_sorted_set_i_count(
            (const struct seahorse_sorted_set_i *) &object, &count));
    assert_int_equal(count, limit);
    count = 0;
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer integer;
    assert_true(sea_turtle_integer_init_intmax_t(
            &integer, rand() % INTMAX_MAX));
    const struct sea_turtle_integer *out = NULL;
    // as set
    assert_true(seahorse_set_i_add(
            (struct seahorse_set_i *) &object, &integer));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &integer));
    out = NULL;
    // as ordered set
    assert_true(seahorse_ordered_set_i_add(
            (struct seahorse_ordered_set_i *) &object, &integer));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &integer));
    out = NULL;
    // as sorted set
    assert_true(seahorse_sorted_set_i_add(
            (struct seahorse_sorted_set_i *) &object, &integer));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &integer));
    assert_true(sea_turtle_integer_invalidate(&integer));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer integer;
    assert_true(sea_turtle_integer_init_intmax_t(
            &integer, rand() % INTMAX_MAX));
    const struct sea_turtle_integer *out = NULL;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as set
    assert_true(seahorse_set_i_remove(
            (struct seahorse_set_i *) &object, &integer));
    assert_false(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as ordered set
    assert_true(seahorse_ordered_set_i_remove(
            (struct seahorse_ordered_set_i *) &object, &integer));
    assert_false(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as sorted set
    assert_true(seahorse_sorted_set_i_remove(
            (struct seahorse_sorted_set_i *) &object, &integer));
    assert_false(seahorse_red_black_tree_set_i_get(&object, &integer, &out));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_true(sea_turtle_integer_invalidate(&integer));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer integer;
    assert_true(sea_turtle_integer_init_intmax_t(
            &integer, rand() % INTMAX_MAX));
    bool result;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as set
    assert_true(seahorse_set_i_contains(
            (struct seahorse_set_i *) &object, &integer, &result));
    assert_true(result);
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &integer));
    result = false;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as ordered set
    assert_true(seahorse_ordered_set_i_contains(
            (struct seahorse_ordered_set_i *) &object, &integer, &result));
    assert_true(result);
    assert_true(seahorse_red_black_tree_set_i_remove(&object, &integer));
    result = false;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    // as sorted set
    assert_true(seahorse_sorted_set_i_contains(
            (struct seahorse_sorted_set_i *) &object, &integer, &result));
    assert_true(result);
    assert_true(sea_turtle_integer_invalidate(&integer));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    struct sea_turtle_integer integer;
    assert_true(sea_turtle_integer_init_intmax_t(
            &integer, rand() % INTMAX_MAX));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &integer));
    const struct sea_turtle_integer *out = NULL;
    // as set
    assert_true(seahorse_set_i_get(
            (struct seahorse_set_i *) &object, &integer, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &integer), 0);
    out = NULL;
    // ordered set
    assert_true(seahorse_ordered_set_i_get(
            (struct seahorse_ordered_set_i *) &object, &integer, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &integer), 0);
    out = NULL;
    // sorted set
    assert_true(seahorse_sorted_set_i_get(
            (struct seahorse_sorted_set_i *) &object, &integer, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &integer), 0);
    out = NULL;
    assert_true(sea_turtle_integer_invalidate(&integer));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    // as sorted set
    assert_true(seahorse_sorted_set_i_ceiling(
            (struct seahorse_sorted_set_i *) &object, &value[0], &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    // as sorted set
    assert_true(seahorse_sorted_set_i_floor(
            (struct seahorse_sorted_set_i *) &object, &value[1], &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[1]));
    // as sorted set
    assert_true(seahorse_sorted_set_i_higher(
            (const struct seahorse_sorted_set_i *) &object, &value[0], &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
    }
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value[0]));
    // as sorted set
    assert_true(seahorse_sorted_set_i_lower(
            (const struct seahorse_sorted_set_i *) &object, &value[1], &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *out = NULL;
    // as stream
    assert_true(seahorse_stream_i_first(
            (const struct seahorse_stream_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // as collection
    assert_true(seahorse_collection_i_first(
            (const struct seahorse_collection_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // as set
    assert_true(seahorse_set_i_first(
            (const struct seahorse_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // ordered set
    assert_true(seahorse_ordered_set_i_first(
            (const struct seahorse_ordered_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // sorted set
    assert_true(seahorse_sorted_set_i_first(
            (const struct seahorse_sorted_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *out = NULL;
    // as collection
    assert_true(seahorse_collection_i_last(
            (const struct seahorse_collection_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // as set
    assert_true(seahorse_set_i_last(
            (const struct seahorse_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // ordered set
    assert_true(seahorse_ordered_set_i_last(
            (const struct seahorse_ordered_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // sorted set
    assert_true(seahorse_sorted_set_i_last(
            (const struct seahorse_sorted_set_i *) &object, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_remove_item(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_intmax_t(
            &value, rand() % INTMAX_MAX));
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &out));
    // as stream
    assert_true(seahorse_stream_i_remove_item(
            (struct seahorse_stream_i *) &object, out));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &out));
    // as collection
    assert_true(seahorse_collection_i_remove_item(
            (struct seahorse_collection_i *) &object, out));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &out));
    // as set
    assert_true(seahorse_set_i_remove_item(
            (struct seahorse_set_i *) &object, out));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &out));
    // as ordered set
    assert_true(seahorse_ordered_set_i_remove_item(
            (struct seahorse_ordered_set_i *) &object, out));
    assert_true(seahorse_red_black_tree_set_i_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_i_get(&object, &value, &out));
    // as sorted set
    assert_true(seahorse_sorted_set_i_remove_item(
            (struct seahorse_sorted_set_i *) &object, out));
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    assert_true(sea_turtle_integer_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *first;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &first));
    const struct sea_turtle_integer *out = NULL;
    // as stream
    assert_true(seahorse_stream_i_next(
            (const struct seahorse_stream_i *) &object, first, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // as collection
    assert_true(seahorse_collection_i_next(
            (const struct seahorse_collection_i *) &object, first, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // as set
    assert_true(seahorse_set_i_next(
            (const struct seahorse_set_i *) &object, first, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    // as ordered set
    out = NULL;
    assert_true(seahorse_ordered_set_i_next(
            (const struct seahorse_ordered_set_i *) &object, first, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    // as sorted set
    assert_true(seahorse_sorted_set_i_next(
            (const struct seahorse_sorted_set_i *) &object, first, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[1]), 0);
    out = NULL;
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_as_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const intmax_t values[] = {736, 8912};
    const uintmax_t limit = sizeof(values) / sizeof(intmax_t);
    struct sea_turtle_integer value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_init_intmax_t(&value[i], values[i]));
        assert_true(seahorse_red_black_tree_set_i_add(&object, &value[i]));
    }
    const struct sea_turtle_integer *last;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &last));
    const struct sea_turtle_integer *out = NULL;
    // as collection
    assert_true(seahorse_collection_i_prev(
            (const struct seahorse_collection_i *) &object, last, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // as set
    assert_true(seahorse_set_i_prev(
            (const struct seahorse_set_i *) &object, last, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // as ordered set
    assert_true(seahorse_ordered_set_i_prev(
            (const struct seahorse_ordered_set_i *) &object, last, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    out = NULL;
    // as sorted set
    assert_true(seahorse_sorted_set_i_prev(
            (const struct seahorse_sorted_set_i *) &object, last, &out));
    assert_int_equal(sea_turtle_integer_compare(out, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_integer_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_invalidate_error_on_object_is_null),
            cmocka_unit_test(check_invalidate),
            cmocka_unit_test(check_init_error_on_object_is_null),
            cmocka_unit_test(check_init),
            cmocka_unit_test(check_count_error_on_object_is_null),
            cmocka_unit_test(check_count_error_on_out_is_null),
            cmocka_unit_test(check_count),
            cmocka_unit_test(check_add_error_on_object_is_null),
            cmocka_unit_test(check_add_error_on_value_is_null),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_value_already_exists),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_value_is_null),
            cmocka_unit_test(check_remove_error_on_value_not_found),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_remove_error_on_memory_allocation_failed),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_value_is_null),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_contains_error_on_memory_allocation_failed),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_value_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_item_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_get_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_value_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_on_item_not_found),
            cmocka_unit_test(check_ceiling),
            cmocka_unit_test(check_ceiling_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_error_on_object_is_null),
            cmocka_unit_test(check_floor_error_on_value_is_null),
            cmocka_unit_test(check_floor_error_on_out_is_null),
            cmocka_unit_test(check_floor_error_on_item_not_found),
            cmocka_unit_test(check_floor),
            cmocka_unit_test(check_floor_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_error_on_object_is_null),
            cmocka_unit_test(check_higher_error_on_value_is_null),
            cmocka_unit_test(check_higher_error_on_out_is_null),
            cmocka_unit_test(check_higher_error_on_item_not_found),
            cmocka_unit_test(check_higher),
            cmocka_unit_test(check_higher_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_error_on_object_is_null),
            cmocka_unit_test(check_lower_error_on_value_is_null),
            cmocka_unit_test(check_lower_error_on_out_is_null),
            cmocka_unit_test(check_lower_error_on_item_not_found),
            cmocka_unit_test(check_lower),
            cmocka_unit_test(check_lower_error_on_memory_allocation_failed),
            cmocka_unit_test(check_first_error_on_object_is_null),
            cmocka_unit_test(check_first_error_on_out_is_null),
            cmocka_unit_test(check_first_error_on_set_is_empty),
            cmocka_unit_test(check_first),
            cmocka_unit_test(check_last_error_on_object_is_null),
            cmocka_unit_test(check_last_error_on_out_is_null),
            cmocka_unit_test(check_last_error_on_set_is_empty),
            cmocka_unit_test(check_last),
            cmocka_unit_test(check_remove_item_error_on_object_is_null),
            cmocka_unit_test(check_remove_item_error_on_item_is_null),
            cmocka_unit_test(check_remove_item),
            cmocka_unit_test(check_next_error_on_item_is_null),
            cmocka_unit_test(check_next_error_on_out_is_null),
            cmocka_unit_test(check_next),
            cmocka_unit_test(check_next_error_on_end_of_sequence),
            cmocka_unit_test(check_prev_error_on_item_is_null),
            cmocka_unit_test(check_prev_error_on_out_is_null),
            cmocka_unit_test(check_prev),
            cmocka_unit_test(check_prev_error_on_end_of_sequence),
            cmocka_unit_test(check_init_set_i_error_on_object_is_null),
            cmocka_unit_test(check_init_set_i_error_on_other_is_null),
            cmocka_unit_test(check_init_set_i_case_empty_set),
            cmocka_unit_test(check_init_set_i),
            cmocka_unit_test(check_init_set_i_error_on_memory_allocation_failed),
            cmocka_unit_test(check_as_count),
            cmocka_unit_test(check_as_add),
            cmocka_unit_test(check_as_remove),
            cmocka_unit_test(check_as_contains),
            cmocka_unit_test(check_as_get),
            cmocka_unit_test(check_as_ceiling),
            cmocka_unit_test(check_as_floor),
            cmocka_unit_test(check_as_higher),
            cmocka_unit_test(check_as_lower),
            cmocka_unit_test(check_as_first),
            cmocka_unit_test(check_as_last),
            cmocka_unit_test(check_as_remove_item),
            cmocka_unit_test(check_as_next),
            cmocka_unit_test(check_as_prev),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
