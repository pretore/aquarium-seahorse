#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <seahorse.h>

#include "test/cmocka.h"

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
    assert_false(seahorse_red_black_tree_set_i_count(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_count((void *)1, NULL));
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
    assert_false(seahorse_red_black_tree_set_i_add(NULL, 0));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
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
    assert_true(seahorse_red_black_tree_set_i_add(
            &object, rand() & UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_already_exists(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t check = rand() & UINTMAX_MAX;
    assert_true(seahorse_red_black_tree_set_i_add(&object, check));
    assert_false(seahorse_red_black_tree_set_i_add(&object, check));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_i_add(
            &object, rand() & UINTMAX_MAX));
    posix_memalign_is_overridden = false;
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_remove(NULL, 0));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_value_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_false(seahorse_red_black_tree_set_i_remove(
            &object, rand() % UINTMAX_MAX));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t value = rand() % UINTMAX_MAX;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_i_remove(&object, value));
    assert_true(seahorse_red_black_tree_set_i_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_count(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_count((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t value = rand() % UINTMAX_MAX;
    bool out;
    assert_true(seahorse_red_black_tree_set_i_contains(&object, value, &out));
    assert_false(out);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    assert_true(seahorse_red_black_tree_set_i_contains(&object, value, &out));
    assert_true(out);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_get(NULL, 0, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_get((void *)1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_item_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_get(
            &object, rand() % UINTMAX_MAX, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t value = rand() % UINTMAX_MAX;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_get(&object, value, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_ceiling(NULL, 1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_ceiling((void *)1, 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 100;
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_ceiling(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    value++;
    assert_false(seahorse_red_black_tree_set_i_ceiling(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 100;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_ceiling(&object, value, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    value = 1873;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    assert_true(seahorse_red_black_tree_set_i_ceiling(&object, 101, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_floor(NULL, 1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_floor((void *)1, 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 100;
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_floor(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    value--;
    assert_false(seahorse_red_black_tree_set_i_floor(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 1873;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_floor(&object, value, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    value = 123;
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    assert_true(seahorse_red_black_tree_set_i_floor(&object, 231, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_higher(NULL, 1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_higher((void *)1, 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 100;
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_higher(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    assert_false(seahorse_red_black_tree_set_i_higher(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t value = 1 + (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_higher(&object, value - 1, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_lower(NULL, 1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_lower((void *)1, 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t value = 100;
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_lower(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    assert_false(seahorse_red_black_tree_set_i_lower(&object, value, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t value = 1 + (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_set_i_add(&object, value));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_lower(&object, 1 + value, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(*out, value);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_first(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_first((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t check = 300;
    assert_true(seahorse_red_black_tree_set_i_add(&object, check));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &out));
    assert_int_equal(*out, check);
    check = 100;
    assert_true(seahorse_red_black_tree_set_i_add(&object, check));
    assert_true(seahorse_red_black_tree_set_i_first(&object, &out));
    assert_int_equal(*out, check);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_last(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_last((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    const uintmax_t *out;
    assert_false(seahorse_red_black_tree_set_i_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    uintmax_t check = 100;
    assert_true(seahorse_red_black_tree_set_i_add(&object, check));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &out));
    assert_int_equal(*out, check);
    check = 300;
    assert_true(seahorse_red_black_tree_set_i_add(&object, check));
    assert_true(seahorse_red_black_tree_set_i_last(&object, &out));
    assert_int_equal(*out, check);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_next(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_next((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(
            &object, rand() % UINTMAX_MAX));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &out));
    assert_false(seahorse_red_black_tree_set_i_next(out, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, 100));
    assert_true(seahorse_red_black_tree_set_i_add(&object, 200));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &out));
    assert_true(seahorse_red_black_tree_set_i_next(out, &out));
    assert_int_equal(*out, 200);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_prev(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_i_prev((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(
            &object, rand() % UINTMAX_MAX));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_first(&object, &out));
    assert_false(seahorse_red_black_tree_set_i_prev(out, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_i object;
    assert_true(seahorse_red_black_tree_set_i_init(&object));
    assert_true(seahorse_red_black_tree_set_i_add(&object, 100));
    assert_true(seahorse_red_black_tree_set_i_add(&object, 200));
    const uintmax_t *out;
    assert_true(seahorse_red_black_tree_set_i_last(&object, &out));
    assert_true(seahorse_red_black_tree_set_i_prev(out, &out));
    assert_int_equal(*out, 100);
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
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_value_already_exists),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_remove_error_on_value_not_found),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_item_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_on_item_not_found),
            cmocka_unit_test(check_ceiling),
            cmocka_unit_test(check_floor_error_on_object_is_null),
            cmocka_unit_test(check_floor_error_on_out_is_null),
            cmocka_unit_test(check_floor_error_on_item_not_found),
            cmocka_unit_test(check_floor),
            cmocka_unit_test(check_higher_error_on_object_is_null),
            cmocka_unit_test(check_higher_error_on_out_is_null),
            cmocka_unit_test(check_higher_error_on_item_not_found),
            cmocka_unit_test(check_higher),
            cmocka_unit_test(check_lower_error_on_object_is_null),
            cmocka_unit_test(check_lower_error_on_out_is_null),
            cmocka_unit_test(check_lower_error_on_item_not_found),
            cmocka_unit_test(check_lower),
            cmocka_unit_test(check_first_error_on_object_is_null),
            cmocka_unit_test(check_first_error_on_out_is_null),
            cmocka_unit_test(check_first_error_on_set_is_empty),
            cmocka_unit_test(check_first),
            cmocka_unit_test(check_last_error_on_object_is_null),
            cmocka_unit_test(check_last_error_on_out_is_null),
            cmocka_unit_test(check_last_error_on_set_is_empty),
            cmocka_unit_test(check_last),
            cmocka_unit_test(check_next_error_on_item_is_null),
            cmocka_unit_test(check_next_error_on_out_is_null),
            cmocka_unit_test(check_next_error_on_end_of_sequence),
            cmocka_unit_test(check_next),
            cmocka_unit_test(check_prev_error_on_item_is_null),
            cmocka_unit_test(check_prev_error_on_out_is_null),
            cmocka_unit_test(check_prev_error_on_end_of_sequence),
            cmocka_unit_test(check_prev),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
