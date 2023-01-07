#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <triggerfish.h>
#include <seagrass.h>
#include <seahorse.h>

#include "test/cmocka.h"

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, (void *) 1));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object = {
            .map.tree.count = 1 + (rand() + (UINTMAX_MAX - 1))
    };
    uintmax_t out;
    assert_true(seahorse_red_black_tree_map_s_wr_count(&object, &out));
    assert_int_equal(out, object.map.tree.count);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_add(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_add(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_add(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void on_destroy(void *instance) {

}

static void check_add_error_on_value_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, (void *) 1));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *value = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID,
                     seahorse_error);
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static int compare(const struct triggerfish_strong **a,
                   const struct triggerfish_strong **b) {
    uintptr_t A;
    seagrass_required_true(triggerfish_strong_instance(*a, (void **) &A));
    uintptr_t B;
    seagrass_required_true(triggerfish_strong_instance(*b, (void **) &B));
    return seagrass_uintmax_t_compare(A, B);
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_false(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_ALREADY_EXISTS,
            seahorse_error);
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove((void *) 1, key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove(&object, key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_true(seahorse_red_black_tree_map_sr_sr_remove(&object, key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    assert_true(seahorse_red_black_tree_map_sr_sr_remove(&object, key));
    assert_true(triggerfish_strong_release(value));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove(&object, key));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    bool out;
    assert_false(seahorse_red_black_tree_map_sr_sr_contains(
            (void *) 1, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    bool out;
    assert_true(seahorse_red_black_tree_map_sr_sr_contains(&object, key, &out));
    assert_false(out);
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_true(seahorse_red_black_tree_map_sr_sr_contains(&object, key, &out));
    assert_true(out);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    bool out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_contains(
            &object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_set(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_set(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_set((void *) 1, key, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_value_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *value = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_set(&object, key, value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_false(seahorse_red_black_tree_map_sr_sr_set(&object, key, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    assert_true(triggerfish_strong_release(value));
    assert_true(seahorse_red_black_tree_map_sr_sr_set(&object, key, NULL));
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_set(&object, key, value));
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    assert_true(triggerfish_strong_release(value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_set(&object, key, NULL));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(key));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    assert_true(seahorse_red_black_tree_map_sr_sr_get(&object, key, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_get(&object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    assert_true(seahorse_red_black_tree_map_sr_sr_ceiling(&object, key, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling(&object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    assert_true(seahorse_red_black_tree_map_sr_sr_floor(&object, key, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out = NULL;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor(&object, key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static int ptr_compare(const void *a, const void *b) {
    return seagrass_void_ptr_compare(*(void **) a, *(void **) b);
}

static void check_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_higher(
            &object, key[0], &out));
    assert_ptr_equal(out, value[1]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    struct triggerfish_strong *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher(
            &object, key[0], &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(&object, key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_lower(
            &object, key[1], &out));
    assert_ptr_equal(out, value[0]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    struct triggerfish_strong *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower(
            &object, key[1], &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_first(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *out;
    assert_false(seahorse_red_black_tree_map_sr_sr_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_last(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
}

static void check_get_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_ceiling_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_floor_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_floor_entry(
            &object, key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_higher_entry(
            &object, key[0], &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key[1]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value[1]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_higher_entry(
            &object, key[0], &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *key = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            (void *) 1, key, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            &object, key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_lower_entry(
            &object, key[1], &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key[0]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value[0]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_lower_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_sr_sr_lower_entry(
            &object, key[1], &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_first_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_first_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_first_entry(
            &object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_first_entry(&object, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_last_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_last_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_false(seahorse_red_black_tree_map_sr_sr_last_entry(
            &object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry(void **state) {
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_last_entry(&object, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    assert_true(triggerfish_strong_release(value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_remove_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    assert_true(seahorse_red_black_tree_map_sr_sr_remove_entry(
            &object, entry));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_next_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_next_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_first_entry(
            &object, &entry));
    assert_false(seahorse_red_black_tree_map_sr_sr_next_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_first_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_sr_sr_next_entry(entry, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key[1]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value[1]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_prev_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_prev_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_last_entry(
            &object, &entry));
    assert_false(seahorse_red_black_tree_map_sr_sr_prev_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    void *data[4] = {
            malloc(1), malloc(1), malloc(1), malloc(1)
    };
    const uintmax_t count = sizeof(data) / sizeof(void *);
    qsort(data, count, sizeof(void *), ptr_compare);
    struct triggerfish_strong *key[2];
    struct triggerfish_strong *value[2];
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_of(data[i], on_destroy, &key[i]));
        assert_true(triggerfish_strong_of(data[2 + i], on_destroy, &value[i]));
    }
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(seahorse_red_black_tree_map_sr_sr_add(
                &object, key[i], value[i]));
    }
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_last_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_sr_sr_prev_entry(entry, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key[0]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value[0]);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(triggerfish_strong_release(key[i]));
        assert_true(triggerfish_strong_release(value[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}


static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_key(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_key(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_key(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, NULL));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_key(
            &object, entry, &out));
    assert_ptr_equal(out, key);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_set_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_set_value(
            (void *) 1, NULL,(void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_value_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t counter = 0;
    /* knowledge that the first field in the strong reference is the counter
     * is being used here.
     */
    struct triggerfish_strong *value = (void *) &counter;
    assert_false(seahorse_red_black_tree_map_sr_sr_entry_set_value(
            (void *) 1, (void *) 1, value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_SR_SR_ERROR_VALUE_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_sr_sr object;
    assert_true(seahorse_red_black_tree_map_sr_sr_init(&object, compare));
    struct triggerfish_strong *key;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &key));
    struct triggerfish_strong *value;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &value));
    assert_true(seahorse_red_black_tree_map_sr_sr_add(&object, key, value));
    const struct seahorse_red_black_tree_map_sr_sr_entry *entry;
    assert_true(seahorse_red_black_tree_map_sr_sr_get_entry(
            &object, key, &entry));
    struct triggerfish_strong *out;
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(triggerfish_strong_release(out));
    assert_true(seahorse_red_black_tree_map_sr_sr_entry_set_value(
            &object, entry, NULL));
    assert_true(seahorse_red_black_tree_map_sr_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(value));
    assert_true(triggerfish_strong_release(key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_invalidate_error_on_object_is_null),
            cmocka_unit_test(check_invalidate),
            cmocka_unit_test(check_count_error_on_object_is_null),
            cmocka_unit_test(check_count_error_on_out_is_null),
            cmocka_unit_test(check_count),
            cmocka_unit_test(check_add_error_on_object_is_null),
            cmocka_unit_test(check_add_error_on_key_is_null),
            cmocka_unit_test(check_add_error_on_key_is_invalid),
            cmocka_unit_test(check_add_error_on_value_is_invalid),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_key_already_exists),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_key_is_null),
            cmocka_unit_test(check_remove_error_on_key_is_invalid),
            cmocka_unit_test(check_remove_error_on_key_not_found),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_remove_error_on_memory_allocation_failed),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_key_is_null),
            cmocka_unit_test(check_contains_error_on_key_is_invalid),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_contains_error_on_memory_allocation_failed),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set_error_on_key_is_null),
            cmocka_unit_test(check_set_error_on_key_is_invalid),
            cmocka_unit_test(check_set_error_on_value_is_invalid),
            cmocka_unit_test(check_set_error_on_key_not_found),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_set_error_on_memory_allocation_failed),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_key_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_key_is_invalid),
            cmocka_unit_test(check_get_error_on_key_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_get_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_is_invalid),
            cmocka_unit_test(check_ceiling_error_on_key_not_found),
            cmocka_unit_test(check_ceiling),
            cmocka_unit_test(check_ceiling_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_error_on_object_is_null),
            cmocka_unit_test(check_floor_error_on_key_is_null),
            cmocka_unit_test(check_floor_error_on_out_is_null),
            cmocka_unit_test(check_floor_error_on_key_is_invalid),
            cmocka_unit_test(check_floor_error_on_key_not_found),
            cmocka_unit_test(check_floor),
            cmocka_unit_test(check_floor_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_error_on_object_is_null),
            cmocka_unit_test(check_higher_error_on_key_is_null),
            cmocka_unit_test(check_higher_error_on_out_is_null),
            cmocka_unit_test(check_higher_error_on_key_is_invalid),
            cmocka_unit_test(check_higher_error_on_key_not_found),
            cmocka_unit_test(check_higher),
            cmocka_unit_test(check_higher_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_error_on_object_is_null),
            cmocka_unit_test(check_lower_error_on_key_is_null),
            cmocka_unit_test(check_lower_error_on_out_is_null),
            cmocka_unit_test(check_lower_error_on_key_is_invalid),
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
            cmocka_unit_test(check_get_entry_error_on_key_is_invalid),
            cmocka_unit_test(check_get_entry_error_on_key_not_found),
            cmocka_unit_test(check_get_entry),
            cmocka_unit_test(check_get_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_entry_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_is_invalid),
            cmocka_unit_test(check_ceiling_entry_error_on_key_not_found),
            cmocka_unit_test(check_ceiling_entry),
            cmocka_unit_test(check_ceiling_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_floor_entry_error_on_object_is_null),
            cmocka_unit_test(check_floor_entry_error_on_key_is_null),
            cmocka_unit_test(check_floor_entry_error_on_out_is_null),
            cmocka_unit_test(check_floor_entry_error_on_key_is_invalid),
            cmocka_unit_test(check_floor_entry_error_on_key_not_found),
            cmocka_unit_test(check_floor_entry),
            cmocka_unit_test(check_floor_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_higher_entry_error_on_object_is_null),
            cmocka_unit_test(check_higher_entry_error_on_key_is_null),
            cmocka_unit_test(check_higher_entry_error_on_out_is_null),
            cmocka_unit_test(check_higher_entry_error_on_key_is_invalid),
            cmocka_unit_test(check_higher_entry_error_on_key_not_found),
            cmocka_unit_test(check_higher_entry),
            cmocka_unit_test(check_higher_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_lower_entry_error_on_object_is_null),
            cmocka_unit_test(check_lower_entry_error_on_key_is_null),
            cmocka_unit_test(check_lower_entry_error_on_out_is_null),
            cmocka_unit_test(check_lower_entry_error_on_key_is_invalid),
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
            cmocka_unit_test(check_entry_set_value_error_on_value_is_invalid),
            cmocka_unit_test(check_entry_set_value),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
