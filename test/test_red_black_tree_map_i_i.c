#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <time.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object = {};
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.map.tree.count = check;
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_add(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_add(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_add(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    assert_false(seahorse_red_black_tree_map_i_i_remove(&object, &key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_i_i_remove(&object, &key));
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 1);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_remove(&object, &key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    bool result;
    assert_true(seahorse_red_black_tree_map_i_i_contains(
            &object, &key, &result));
    assert_false(result);
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_contains(
            &object, &key, &result));
    assert_true(result);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    bool result;
    assert_true(seahorse_red_black_tree_map_i_i_contains(
            &object, &key, &result));
    assert_false(result);
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_contains(
            &object, &key, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_get(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_get(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_get(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling(
            (void *)1, NULL,  (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer *value;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling(
            &object, &key,&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_ceiling(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 11));
    assert_true(seahorse_red_black_tree_map_i_i_ceiling(
            &object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_floor(
            NULL, (void *)1, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_floor(
            (void *)1, NULL, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_floor(
            (void *)1, (void*)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_floor(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_floor(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 10));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 19));
    assert_true(seahorse_red_black_tree_map_i_i_floor(&object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_floor(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 101));
    assert_false(seahorse_red_black_tree_map_i_i_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 10));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_higher(&object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 10));
    struct sea_turtle_integer *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_higher(&object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower((void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 99));
    assert_false(seahorse_red_black_tree_map_i_i_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 100));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_lower(&object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 100));
    struct sea_turtle_integer *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_lower(&object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_first(NULL, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_first((void*)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_first(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 10));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_first(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_last(NULL, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_last((void*)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer *out;
    assert_false(seahorse_red_black_tree_map_i_i_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_last(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_last(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get_entry(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get_entry(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_get_entry(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_get_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_get_entry(
            &object, &key, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry,&out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_get_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_ceiling_entry(
            &object, &key, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 11));
    assert_true(seahorse_red_black_tree_map_i_i_ceiling_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            NULL, (void*)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            (void*)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_ceiling_entry(
            (void*)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_floor_entry(
            &object, &key, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 10));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 11));
    assert_true(seahorse_red_black_tree_map_i_i_floor_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_floor_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            NULL, (void*)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            (void*)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            (void*)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 101));
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 10));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_higher_entry(
            &object, &query, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(&object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 10));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_higher_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            NULL, (void*)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            (void*)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            (void*)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 101));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 100));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_lower_entry(
            &object, &query, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(&object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    struct sea_turtle_integer query;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&query, 100));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_i_i_lower_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&query));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_first_entry(NULL, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_first_entry((void*)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 10));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_last_entry(NULL, (void*)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_last_entry((void*)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_false(seahorse_red_black_tree_map_i_i_last_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_last_entry(&object, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_last_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_remove_entry(
            NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_remove_entry(
            (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    for (uintmax_t i = 0; i < 3; i++) {
        struct sea_turtle_integer key;
        assert_true(sea_turtle_integer_init_with_uintmax_t(&key, i));
        struct sea_turtle_integer value;
        assert_true(sea_turtle_integer_init_with_uintmax_t(
                &value, rand() % UINTMAX_MAX));
        assert_true(seahorse_red_black_tree_map_i_i_add(
                &object, &key, &value));
        assert_true(sea_turtle_integer_invalidate(&value));
        assert_true(sea_turtle_integer_invalidate(&key));
    }
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 1));
    assert_true(seahorse_red_black_tree_map_i_i_get_entry(
            &object, &key, &entry));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 3);
    assert_true(seahorse_red_black_tree_map_i_i_remove_entry(&object, entry));
    assert_true(seahorse_red_black_tree_map_i_i_count(&object, &count));
    assert_int_equal(count, 2);
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_next_entry(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_next_entry((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_i_i_next_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 10));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 100));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_next_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_prev_entry(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_prev_entry((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_last_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_i_i_prev_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(&key, 100));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_last_entry(&object, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_set_with_uintmax_t(&key, 10));
    assert_true(sea_turtle_integer_set_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_i_i_prev_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, (struct sea_turtle_integer **) &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_key(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_key(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_key(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    const struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_integer_compare(&key, out), 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_value(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_value(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_i_i_entry_value(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_value(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_i_i object;
    assert_true(seahorse_red_black_tree_map_i_i_init(&object));
    struct sea_turtle_integer key;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &key, rand() % UINTMAX_MAX));
    struct sea_turtle_integer value;
    assert_true(sea_turtle_integer_init_with_uintmax_t(
            &value, rand() % UINTMAX_MAX));
    assert_true(seahorse_red_black_tree_map_i_i_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_i_i_entry *entry;
    assert_true(seahorse_red_black_tree_map_i_i_first_entry(&object, &entry));
    struct sea_turtle_integer *out;
    assert_true(seahorse_red_black_tree_map_i_i_entry_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_integer_compare(&value, out), 0);
    assert_true(sea_turtle_integer_invalidate(&value));
    assert_true(sea_turtle_integer_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_i_i_invalidate(&object));
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
            cmocka_unit_test(check_add_error_on_key_is_null),
            cmocka_unit_test(check_add_error_on_value_is_null),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_key_already_exists),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_key_is_null),
            cmocka_unit_test(check_remove_error_on_key_not_found),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_remove_error_on_memory_allocation_failed),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_key_is_null),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_contains_error_on_memory_allocation_failed),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_key_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_key_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_get_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_not_found),
            cmocka_unit_test(check_ceiling),
            cmocka_unit_test(check_ceiling_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_error_on_object_is_null),
            cmocka_unit_test(check_floor_error_on_key_is_null),
            cmocka_unit_test(check_floor_error_on_out_is_null),
            cmocka_unit_test(check_floor_error_on_key_not_found),
            cmocka_unit_test(check_floor),
            cmocka_unit_test(check_floor_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_error_on_object_is_null),
            cmocka_unit_test(check_higher_error_on_key_is_null),
            cmocka_unit_test(check_higher_error_on_out_is_null),
            cmocka_unit_test(check_higher_error_on_key_not_found),
            cmocka_unit_test(check_higher),
            cmocka_unit_test(check_higher_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_error_on_object_is_null),
            cmocka_unit_test(check_lower_error_on_key_is_null),
            cmocka_unit_test(check_lower_error_on_out_is_null),
            cmocka_unit_test(check_lower_error_on_key_not_found),
            cmocka_unit_test(check_lower),
            cmocka_unit_test(check_lower_error_on_memory_allocation_failed),
            cmocka_unit_test(check_first_error_on_object_is_null),
            cmocka_unit_test(check_first_error_on_out_is_null),
            cmocka_unit_test(check_first_error_on_map_is_empty),
            cmocka_unit_test(check_first),
            cmocka_unit_test(check_last_error_on_object_is_null),
            cmocka_unit_test(check_last_error_on_out_is_null),
            cmocka_unit_test(check_last_error_on_map_is_empty),
            cmocka_unit_test(check_last),
            cmocka_unit_test(check_get_entry_error_on_object_is_null),
            cmocka_unit_test(check_get_entry_error_on_key_is_null),
            cmocka_unit_test(check_get_entry_error_on_out_is_null),
            cmocka_unit_test(check_get_entry_error_on_key_not_found),
            cmocka_unit_test(check_get_entry),
            cmocka_unit_test(check_get_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_entry_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_not_found),
            cmocka_unit_test(check_ceiling_entry),
            cmocka_unit_test(check_ceiling_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_entry_error_on_object_is_null),
            cmocka_unit_test(check_floor_entry_error_on_key_is_null),
            cmocka_unit_test(check_floor_entry_error_on_out_is_null),
            cmocka_unit_test(check_floor_entry_error_on_key_not_found),
            cmocka_unit_test(check_floor_entry),
            cmocka_unit_test(check_floor_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_entry_error_on_object_is_null),
            cmocka_unit_test(check_higher_entry_error_on_key_is_null),
            cmocka_unit_test(check_higher_entry_error_on_out_is_null),
            cmocka_unit_test(check_higher_entry_error_on_key_not_found),
            cmocka_unit_test(check_higher_entry),
            cmocka_unit_test(check_higher_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_entry_error_on_object_is_null),
            cmocka_unit_test(check_lower_entry_error_on_key_is_null),
            cmocka_unit_test(check_lower_entry_error_on_out_is_null),
            cmocka_unit_test(check_lower_entry_error_on_key_not_found),
            cmocka_unit_test(check_lower_entry),
            cmocka_unit_test(check_lower_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_first_entry_error_on_object_is_null),
            cmocka_unit_test(check_first_entry_error_on_out_is_null),
            cmocka_unit_test(check_first_entry_error_on_map_is_empty),
            cmocka_unit_test(check_first_entry),
            cmocka_unit_test(check_last_entry_error_on_object_is_null),
            cmocka_unit_test(check_last_entry_error_on_out_is_null),
            cmocka_unit_test(check_last_entry_error_on_map_is_empty),
            cmocka_unit_test(check_last_entry),
            cmocka_unit_test(check_remove_entry_error_on_object_is_null),
            cmocka_unit_test(check_remove_entry_error_on_entry_is_null),
            cmocka_unit_test(check_remove_entry),
            cmocka_unit_test(check_next_entry_error_on_entry_is_null),
            cmocka_unit_test(check_next_entry_error_on_out_is_null),
            cmocka_unit_test(check_next_entry_error_on_end_of_sequence),
            cmocka_unit_test(check_next_entry),
            cmocka_unit_test(check_prev_entry_error_on_entry_is_null),
            cmocka_unit_test(check_prev_entry_error_on_out_is_null),
            cmocka_unit_test(check_prev_entry_error_on_end_of_sequence),
            cmocka_unit_test(check_prev_entry),
            cmocka_unit_test(check_entry_key_error_on_object_is_null),
            cmocka_unit_test(check_entry_key_error_on_entry_is_null),
            cmocka_unit_test(check_entry_key_error_on_out_is_null),
            cmocka_unit_test(check_entry_key),
            cmocka_unit_test(check_entry_value_error_on_object_is_null),
            cmocka_unit_test(check_entry_value_error_on_entry_is_null),
            cmocka_unit_test(check_entry_value_error_on_out_is_null),
            cmocka_unit_test(check_entry_value),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
