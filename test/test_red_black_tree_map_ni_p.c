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
    assert_false(seahorse_red_black_tree_map_ni_p_invalidate(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object = {};
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(
            &object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(
            &object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.map.tree.count = check;
    uintmax_t out;
    assert_true(seahorse_red_black_tree_map_ni_p_count(
            &object, (uintmax_t *) &out));
    assert_int_equal(out, check);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_add(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    posix_memalign_is_overridden = false;
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value = (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    assert_false(seahorse_red_black_tree_map_ni_p_add(&object, key, &key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_remove(NULL, 0));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    assert_false(seahorse_red_black_tree_map_ni_p_remove(&object, key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_ni_p_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_ni_p_remove(&object, key));
    assert_true(seahorse_red_black_tree_map_ni_p_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_ni_p_count(&object, &count));
    assert_int_equal(count, 1);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_remove(&object, key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_contains(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_contains(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    bool out;
    assert_true(seahorse_red_black_tree_map_ni_p_contains(&object, key, &out));
    assert_false(out);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    assert_true(seahorse_red_black_tree_map_ni_p_contains(&object, key, &out));
    assert_true(out);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    bool out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_contains(&object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_set(NULL, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_on_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_false(seahorse_red_black_tree_map_ni_p_set(&object, key, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *out;
    assert_true(coral_red_black_tree_map_get(&object.map,
                                             &key,
                                             (const void **) &out));
    assert_ptr_equal(*out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_set(&object, key, &key));
    assert_true(coral_red_black_tree_map_get(&object.map,
                                             &key,
                                             (const void **) &out));
    assert_ptr_equal(*out, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *out;
    assert_true(coral_red_black_tree_map_get(&object.map,
                                             &key,
                                             (const void **) &out));
    assert_ptr_equal(*out, &value);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_set(&object, key, &key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_get(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_get((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_get(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_get(&object, key, &out));
    assert_ptr_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_get(&object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    const uintmax_t value;
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key += 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_ceiling(&object, 10, &out));
    assert_ptr_equal(out, &value);
    value += (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, 100, &value));
    assert_true(seahorse_red_black_tree_map_ni_p_ceiling(&object, 11, &out));
    assert_int_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling(&object, 10, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    const uintmax_t value;
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_floor(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key -= 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_floor(&object, 100, &out));
    assert_ptr_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, 10, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_floor(&object, 19, &out));
    assert_ptr_equal(out, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_floor(&object, 100, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    const uintmax_t value;
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_higher(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key += 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_higher(&object, 10, &out));
    assert_ptr_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_higher(&object, 10, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower(NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower((void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    const uintmax_t value;
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_lower(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key -= 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_NI_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_lower(&object, 100, &out));
    assert_ptr_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_lower(&object, 100, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_first(&object, &out));
    assert_int_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const void *out;
    assert_false(seahorse_red_black_tree_map_ni_p_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_ni_p_last(&object, &out));
    assert_int_equal(out, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_get_entry(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_get_entry(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const struct seahorse_red_black_tree_map_ni_p_entry *out;
    const uintmax_t key = (rand() % UINTMAX_MAX);
    assert_false(seahorse_red_black_tree_map_ni_p_get_entry(
            &object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_get_entry(
            &object, key, &entry));
    const uintmax_t *k;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(*k, key);
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_get_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    const uintmax_t value;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key += 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *k;
    const void *v;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            &object, key, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);
    key = 100;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            &object, 11, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_ceiling_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    const uintmax_t value;
    const struct seahorse_red_black_tree_map_ni_p_entry *out;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key -= 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *k;
    const void *v;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, key, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);
    key = 10;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, 19, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher_entry(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher_entry(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    const uintmax_t value;
    const struct seahorse_red_black_tree_map_ni_p_entry *out;
    assert_false(seahorse_red_black_tree_map_ni_p_higher_entry(
            &object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key += 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_higher_entry(
            &object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *k;
    const void *v;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_higher_entry(
            &object, 10, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 100;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_higher_entry(
            &object, 10, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower_entry(
            NULL, 0, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower_entry(
            (void *) 1, 0, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    const uintmax_t value;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_ni_p_lower_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    key -= 1 + (rand() % UINT8_MAX);
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_lower_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const uintmax_t *k;
    const void *v;
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, 100, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = 10;
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(&object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_ni_p_floor_entry(
            &object, 100, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_first_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_first_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    const uintmax_t *k;
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &value);

    key -= 1 + (rand() % UINT8_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_last_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_last_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_ni_p_last_entry(
            &object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_last_entry(
            &object, &entry));
    const uintmax_t *k;
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_int_equal(v, &value);

    key += 1 + (rand() % UINT8_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_last_entry(
            &object, &entry));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_int_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_remove_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_remove_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    for (uintmax_t i = 0; i < 3; i++) {
        assert_true(seahorse_red_black_tree_map_ni_p_add(&object, i, NULL));
    }
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_get_entry(&object, 1, &entry));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_ni_p_count(&object, &count));
    assert_int_equal(count, 3);
    assert_true(seahorse_red_black_tree_map_ni_p_remove_entry(&object, entry));
    assert_true(seahorse_red_black_tree_map_ni_p_count(&object, &count));
    assert_int_equal(count, 2);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_next_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_next_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    assert_false(seahorse_red_black_tree_map_ni_p_next_entry(
            entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    key += 1 + (rand() % UINT8_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_next_entry(
            entry, &entry));
    const uintmax_t *k;
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_prev_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_prev_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    const uintmax_t key = (rand() % UINTMAX_MAX);
    const uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_last_entry(
            &object, &entry));
    assert_false(seahorse_red_black_tree_map_ni_p_prev_entry(
            entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = UINT16_MAX - (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_last_entry(
            &object, &entry));
    key -= 1 + (rand() % UINT8_MAX);
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_prev_entry(
            entry, &entry));
    const uintmax_t *k;
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_key(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_key(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_key(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    const uintmax_t *k;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_key(
            &object, entry, &k));
    assert_int_equal(*k, key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_get_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_get_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_get_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_int_equal(v, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_set_value(
            NULL, (void *) 1, 0));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_ni_p_entry_set_value(
            (void *) 1, NULL, 0));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_NI_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_ni_p object;
    assert_true(seahorse_red_black_tree_map_ni_p_init(&object));
    uintmax_t key = (rand() % UINT8_MAX);
    uintmax_t value;
    assert_true(seahorse_red_black_tree_map_ni_p_add(
            &object, key, &value));
    const struct seahorse_red_black_tree_map_ni_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_ni_p_first_entry(
            &object, &entry));
    const void *v;
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_int_equal(v, &value);
    assert_true(seahorse_red_black_tree_map_ni_p_entry_set_value(
            &object, entry, &key));
    assert_true(seahorse_red_black_tree_map_ni_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, &key);
    assert_true(seahorse_red_black_tree_map_ni_p_invalidate(&object, NULL));
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
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_key_already_exists),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_key_not_found),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_remove_error_on_memory_allocation_failed),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_contains_error_on_memory_allocation_failed),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set_error_on_key_on_found),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_set_error_on_memory_allocation_failed),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_key_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_get_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_not_found),
            cmocka_unit_test(check_ceiling),
            cmocka_unit_test(check_ceiling_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_error_on_object_is_null),
            cmocka_unit_test(check_floor_error_on_out_is_null),
            cmocka_unit_test(check_floor_error_on_key_not_found),
            cmocka_unit_test(check_floor),
            cmocka_unit_test(check_floor_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_error_on_object_is_null),
            cmocka_unit_test(check_higher_error_on_out_is_null),
            cmocka_unit_test(check_higher_error_on_key_not_found),
            cmocka_unit_test(check_higher),
            cmocka_unit_test(check_higher_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_error_on_object_is_null),
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
            cmocka_unit_test(check_get_entry_error_on_out_is_null),
            cmocka_unit_test(check_get_entry_error_on_key_not_found),
            cmocka_unit_test(check_get_entry),
            cmocka_unit_test(check_get_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_entry_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_not_found),
            cmocka_unit_test(check_ceiling_entry),
            cmocka_unit_test(check_ceiling_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_entry_error_on_object_is_null),
            cmocka_unit_test(check_floor_entry_error_on_out_is_null),
            cmocka_unit_test(check_floor_entry_error_on_key_not_found),
            cmocka_unit_test(check_floor_entry),
            cmocka_unit_test(check_floor_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_entry_error_on_object_is_null),
            cmocka_unit_test(check_higher_entry_error_on_out_is_null),
            cmocka_unit_test(check_higher_entry_error_on_key_not_found),
            cmocka_unit_test(check_higher_entry),
            cmocka_unit_test(check_higher_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_entry_error_on_object_is_null),
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
            cmocka_unit_test(check_entry_set_value_error_on_object_is_null),
            cmocka_unit_test(check_entry_set_value_error_on_entry_is_null),
            cmocka_unit_test(check_entry_set_value),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
