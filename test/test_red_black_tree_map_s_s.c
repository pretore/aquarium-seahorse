#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <seagrass.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include "test/cmocka.h"

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object = {};
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_I_I_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object = {};
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.map.tree.count = check;
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_add(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_add(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_add(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    assert_false(seahorse_red_black_tree_map_s_s_remove(&object, &key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_s_s_remove(&object, &key));
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 1);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_remove(&object, &key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    bool result;
    assert_true(seahorse_red_black_tree_map_s_s_contains(
            &object, &key, &result));
    assert_false(result);
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_contains(
            &object, &key, &result));
    assert_true(result);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    bool result;
    assert_true(seahorse_red_black_tree_map_s_s_contains(
            &object, &key, &result));
    assert_false(result);
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_contains(
            &object, &key, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_set(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_set(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_set(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&value));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    malloc_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_set(&object, &key, &value));
    malloc_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&value));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_set(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_get(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_false(seahorse_red_black_tree_map_s_s_set(&object, &key, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_get(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_get(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_get(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_ceiling(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&query, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_ceiling(
            &object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_floor(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    assert_false(seahorse_red_black_tree_map_s_s_floor(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    struct sea_turtle_string value;
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_floor(&object, &key, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    assert_true(seahorse_red_black_tree_map_s_s_floor(
            &object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    struct sea_turtle_string value;
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_floor(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_false(seahorse_red_black_tree_map_s_s_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    assert_true(sea_turtle_string_init(&query, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_higher(
            &object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string value;
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    assert_true(sea_turtle_string_init(&query, KEY0, sizeof(KEY0), &size));
    struct sea_turtle_string *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_higher(
            &object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE[] = u8"value";
    assert_true(sea_turtle_string_init(&value, VALUE, sizeof(VALUE), &size));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_s_s_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    assert_false(seahorse_red_black_tree_map_s_s_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    struct sea_turtle_string value;
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_lower(
            &object, &query, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    struct sea_turtle_string value;
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const char VALUE0[] = u8"value0";
    assert_true(sea_turtle_string_init(&value, VALUE0, sizeof(VALUE0), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    struct sea_turtle_string *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_lower(
            &object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    struct sea_turtle_string value;
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_first(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_first(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string *out;
    assert_false(seahorse_red_black_tree_map_s_s_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    struct sea_turtle_string value;
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_last(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_last(&object, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_get_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_get_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    struct sea_turtle_string value;
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_get_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    struct sea_turtle_string value;
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_get_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    struct sea_turtle_string value;
    const char VALUE3[] = u8"value3";
    assert_true(sea_turtle_string_init(&value, VALUE3, sizeof(VALUE3), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY4[] = u8"key4";
    assert_true(sea_turtle_string_init(&key, KEY4, sizeof(KEY4), &size));
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    assert_true(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_floor_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY7[] = u8"key7";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY7, sizeof(KEY7), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY4[] = u8"key4";
    assert_true(sea_turtle_string_init(&key, KEY4, sizeof(KEY4), &size));
    struct sea_turtle_string value;
    const char VALUE4[] = u8"value4";
    assert_true(sea_turtle_string_init(&value, VALUE4, sizeof(VALUE4), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    assert_false(seahorse_red_black_tree_map_s_s_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    assert_true(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    struct sea_turtle_string value;
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    struct sea_turtle_string value;
    const char VALUE3[] = u8"value3";
    assert_true(sea_turtle_string_init(&value, VALUE3, sizeof(VALUE3), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    size_t size;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_higher_entry(
            &object, &query, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    size_t size;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_higher_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    struct sea_turtle_string value;
    const char VALUE3[] = u8"value3";
    assert_true(sea_turtle_string_init(&value, VALUE3, sizeof(VALUE3), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    size_t size;
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&query, KEY9, sizeof(KEY9), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_lower_entry(
            &object, &query, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    size_t size;
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    struct sea_turtle_string query;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&query, KEY9, sizeof(KEY9), &size));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_s_lower_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_first_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_first_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    const char VALUE2[] = u8"value2";
    assert_true(sea_turtle_string_init(&value, VALUE2, sizeof(VALUE2), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_last_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_last_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_s_last_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    const char VALUE2[] = u8"value2";
    assert_true(sea_turtle_string_init(&value, VALUE2, sizeof(VALUE2), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_last_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&key, KEY8, sizeof(KEY8), &size));
    const char VALUE8[] = u8"value8";
    assert_true(sea_turtle_string_init(&value, VALUE8, sizeof(VALUE8), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_last_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_remove_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_remove_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    const char KEY[3][5] = {u8"key0", u8"key1", u8"key2"};
    const char VALUE[3][7] = {u8"value0", u8"value1", u8"value2"};
    size_t size;
    for (uintmax_t i = 0; i < 3; i++) {
        struct sea_turtle_string key;
        assert_true(sea_turtle_string_init(&key, KEY[i], sizeof(KEY[i]),
                                           &size));
        struct sea_turtle_string value;
        assert_true(sea_turtle_string_init(&value, VALUE[i], sizeof(VALUE[i]),
                                           &size));
        assert_true(seahorse_red_black_tree_map_s_s_add(
                &object, &key, &value));
        assert_true(sea_turtle_string_invalidate(&value));
        assert_true(sea_turtle_string_invalidate(&key));
    }
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    struct sea_turtle_string key;
    assert_true(sea_turtle_string_init(&key, KEY[1], sizeof(KEY[1]),
                                       &size));
    assert_true(seahorse_red_black_tree_map_s_s_get_entry(
            &object, &key, &entry));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 3);
    assert_true(seahorse_red_black_tree_map_s_s_remove_entry(&object, entry));
    assert_true(seahorse_red_black_tree_map_s_s_count(&object, &count));
    assert_int_equal(count, 2);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_next_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_next_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    const char VALUE2[] = u8"value2";
    assert_true(sea_turtle_string_init(&value, VALUE2, sizeof(VALUE2), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_s_s_next_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_next_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_prev_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_prev_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    const char VALUE2[] = u8"value2";
    assert_true(sea_turtle_string_init(&value, VALUE2, sizeof(VALUE2), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_last_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_s_s_prev_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const char VALUE9[] = u8"value9";
    assert_true(sea_turtle_string_init(&value, VALUE9, sizeof(VALUE9), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_last_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    assert_true(seahorse_red_black_tree_map_s_s_prev_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_key(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_key(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_key(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_get_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_get_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_get_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_set_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_set_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_s_entry_set_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_s object;
    assert_true(seahorse_red_black_tree_map_s_s_init(&object));
    size_t size;
    struct sea_turtle_string key;
    struct sea_turtle_string value;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const char VALUE1[] = u8"value1";
    assert_true(sea_turtle_string_init(&value, VALUE1, sizeof(VALUE1), &size));
    assert_true(seahorse_red_black_tree_map_s_s_add(&object, &key, &value));
    const struct seahorse_red_black_tree_map_s_s_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_s_first_entry(&object, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    const char VALUE5[] = u8"value5";
    assert_true(sea_turtle_string_init(&value, VALUE5, sizeof(VALUE5), &size));
    assert_true(seahorse_red_black_tree_map_s_s_entry_set_value(
            &object, entry, &value));
    assert_true(seahorse_red_black_tree_map_s_s_entry_get_value(
            &object, entry, &out));
    assert_ptr_not_equal(out, &value);
    assert_int_equal(sea_turtle_string_compare(&value, out), 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_s_invalidate(&object));
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
            cmocka_unit_test(check_contains_error_memory_allocation_failed),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set_error_on_key_is_null),
            cmocka_unit_test(check_set_error_on_value_is_null),
            cmocka_unit_test(check_set_error_on_memory_allocation_failed),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_set_error_on_key_not_found),
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
            cmocka_unit_test(check_entry_get_value_error_on_object_is_null),
            cmocka_unit_test(check_entry_get_value_error_on_entry_is_null),
            cmocka_unit_test(check_entry_get_value_error_on_out_is_null),
            cmocka_unit_test(check_entry_get_value),
            cmocka_unit_test(check_entry_set_value_error_on_object_is_null),
            cmocka_unit_test(check_entry_set_value_error_on_entry_is_null),
            cmocka_unit_test(check_entry_set_value_error_on_value_is_null),
            cmocka_unit_test(check_entry_set_value),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
