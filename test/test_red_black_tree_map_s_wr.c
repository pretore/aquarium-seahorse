#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <time.h>
#include <sea-turtle.h>
#include <triggerfish.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object = {};
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
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
    assert_false(seahorse_red_black_tree_map_s_wr_add(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_add(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_add(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void on_destroy(void *instance) {
    assert_non_null(instance);
}

static void check_add_error_on_strong_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"add";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference and it that pointer will be NULL if the
     * strong reference has been invalidated.
     * */
    struct triggerfish_weak *value = calloc(1, sizeof(void *));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_false(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_STRONG_IS_INVALID,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    free(value);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"add";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    assert_false(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_ALREADY_EXISTS,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"add";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"add";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"remove";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_wr_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_s_wr_remove(&object, &key));
    assert_true(seahorse_red_black_tree_map_s_wr_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
            seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"contains";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    bool result;
    assert_true(seahorse_red_black_tree_map_s_wr_contains(
            &object, &key, &result));
    assert_false(result);
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_wr_contains(
            &object, &key, &result));
    assert_true(result);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"contains";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    bool result;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_contains(
            &object, &key, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_set(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_set(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_set(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_strong_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"set";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference. It is that pointer that will be
     * NULL if the strong reference has been invalidated.
     * */
    struct triggerfish_weak *other = calloc(1, sizeof(void *));
    assert_false(seahorse_red_black_tree_map_s_wr_set(&object, &key, other));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_STRONG_IS_INVALID,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    free(other);
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_strong_release(strong));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"set";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    struct triggerfish_weak *other;
    assert_true(triggerfish_weak_of(strong, &other));
    assert_true(seahorse_red_black_tree_map_s_wr_set(&object, &key, other));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_weak_destroy(other));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"set";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *value;
    assert_true(triggerfish_weak_of(strong, &value));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, value));
    struct triggerfish_weak *other;
    assert_true(triggerfish_weak_of(strong, &other));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_set(&object, &key, other));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(value));
    assert_true(triggerfish_weak_destroy(other));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *weak;
    assert_false(seahorse_red_black_tree_map_s_wr_get(&object, &key, &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_get(&object, &key, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_get(&object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"ceiling";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *weak;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling(
            &object, &key, &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][9] = {
            u8"ceiling0", u8"ceiling9"
    };
    struct triggerfish_strong *strong[2];
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
    }
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    struct triggerfish_weak *weak[2];
    assert_true(triggerfish_weak_of(strong[1], &weak[1]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[1], weak[1]));
    const struct triggerfish_weak *out;
    /* using the lower key will retrieve the higher key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_ceiling(
            &object, &key[0], &out));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[1]);
    assert_true(triggerfish_weak_of(strong[0], &weak[0]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[0], weak[0]));
    /* using the same lower key will retrieve the lower key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_ceiling(
            &object, &key[0], &out));
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[0]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"ceiling";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling(
            &object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"floor";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *weak;
    assert_false(seahorse_red_black_tree_map_s_wr_floor(
            &object, &key, &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][7] = {
            u8"floor0", u8"floor9"
    };
    struct triggerfish_strong *strong[2];
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
    }
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    struct triggerfish_weak *weak[2];
    assert_true(triggerfish_weak_of(strong[0], &weak[0]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[0], weak[0]));
    const struct triggerfish_weak *out;
    /* using the higher key will retrieve the lower key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_floor(
            &object, &key[1], &out));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[0]);
    assert_true(triggerfish_weak_of(strong[1], &weak[1]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[1], weak[1]));
    /* using the same higher key will retrieve the higher key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_floor(
            &object, &key[1], &out));
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[1]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"floor";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_floor(
            &object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"higher";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *weak;
    assert_false(seahorse_red_black_tree_map_s_wr_higher(
            &object, &key, &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][9] = {
            u8"higher0", u8"higher9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct triggerfish_weak *out;
    /* using the lower key will retrieve the higher key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_higher(
            &object, &key[0], &out));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[1]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"higher";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_higher(
            &object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"lower";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *weak;
    assert_false(seahorse_red_black_tree_map_s_wr_lower(
            &object, &key, &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][9] = {
            u8"lower0", u8"lower9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct triggerfish_weak *out;
    /* using the higher key will retrieve the lower key's value */
    assert_true(seahorse_red_black_tree_map_s_wr_lower(
            &object, &key[1], &out));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) out, *(uintmax_t *) weak[0]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"lower";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *value;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_lower(
            &object, &key, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *out;
    assert_false(seahorse_red_black_tree_map_s_wr_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"first";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *first;
    assert_true(seahorse_red_black_tree_map_s_wr_first(&object, &first));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) first, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct triggerfish_weak *out;
    assert_false(seahorse_red_black_tree_map_s_wr_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"last";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct triggerfish_weak *first;
    assert_true(seahorse_red_black_tree_map_s_wr_first(&object, &first));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) first, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_get_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"get entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"ceiling entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][15] = {
            u8"ceiling entry0", u8"ceiling entry9"
    };
    struct triggerfish_strong *strong[2];
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
    }
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    struct triggerfish_weak *weak[2];
    assert_true(triggerfish_weak_of(strong[1], &weak[1]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[1], weak[1]));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    /* using the lower key will retrieve the higher key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            &object, &key[0], &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[1]);
    assert_true(triggerfish_weak_of(strong[0], &weak[0]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[0], weak[0]));
    /* using the same lower key will retrieve the lower key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            &object, &key[0], &entry));
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[0]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"ceiling entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor_entry(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_floor_entry(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"floor entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][13] = {
            u8"floor entry0", u8"floor entry9"
    };
    struct triggerfish_strong *strong[2];
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
    }
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    struct triggerfish_weak *weak[2];
    assert_true(triggerfish_weak_of(strong[0], &weak[0]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[0], weak[0]));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    /* using the higher key will retrieve the lower key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_floor_entry(
            &object, &key[1], &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[0]);
    assert_true(triggerfish_weak_of(strong[1], &weak[1]));
    assert_true(seahorse_red_black_tree_map_s_wr_add(
            &object, &key[1], weak[1]));
    /* using the same higher key will retrieve the higher key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_floor_entry(
            &object, &key[1], &entry));
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[1]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"floor entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_floor_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher_entry(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher_entry(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_higher_entry(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"higher entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][14] = {
            u8"higher entry0", u8"higher entry9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    /* using the lower key will retrieve the higher key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_higher_entry(
            &object, &key[0], &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[1]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"higher entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_higher_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower_entry(
            NULL, (void *)1, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower_entry(
            (void *)1, NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_lower_entry(
            (void *)1, (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"lower entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][13] = {
            u8"lower entry0", u8"lower entry9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    /* using the higher key will retrieve the lower key's entry */
    assert_true(seahorse_red_black_tree_map_s_wr_lower_entry(
            &object, &key[1], &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[0]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_lower_entry_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"lower entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_lower_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_first_entry(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_first_entry((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_first_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"first entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_first_entry(&object, &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_last_entry(NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_last_entry((void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_wr_last_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_remove_entry(
            NULL, (void *)1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_remove_entry(
            (void *)1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"remove entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_wr_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_s_wr_remove_entry(&object, entry));
    assert_true(seahorse_red_black_tree_map_s_wr_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_next_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_next_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"next entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_false(seahorse_red_black_tree_map_s_wr_next_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][12] = {
            u8"next entry0", u8"next entry9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_first_entry(&object,&entry));
    assert_true(seahorse_red_black_tree_map_s_wr_next_entry(entry, &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[1]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_prev_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_prev_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"prev entry";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_false(seahorse_red_black_tree_map_s_wr_prev_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct sea_turtle_string key[2];
    const char chars[][12] = {
            u8"prev entry0", u8"prev entry9"
    };
    struct triggerfish_strong *strong[2];
    struct triggerfish_weak *weak[2];
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        size_t out;
        assert_true(sea_turtle_string_init(
                &key[i], chars[i], sizeof(chars), &out));
        assert_true(triggerfish_strong_of(
                malloc(1), on_destroy, &strong[i]));
        assert_true(triggerfish_weak_of(strong[i], &weak[i]));
        assert_true(seahorse_red_black_tree_map_s_wr_add(
                &object, &key[i], weak[i]));
    }
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_last_entry(&object,&entry));
    assert_true(seahorse_red_black_tree_map_s_wr_prev_entry(entry, &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak[0]);
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    for (uintmax_t i = 0; i < 2; i++) {
        assert_true(sea_turtle_string_invalidate(&key[i]));
        assert_true(triggerfish_strong_release(strong[i]));
        assert_true(triggerfish_weak_destroy(weak[i]));
    }
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_key(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_key(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_key(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"entry key";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_key(&object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(k, &key), 0);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_get_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_get_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_get_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"entry get value";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_set_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_set_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_set_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_strong_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"entry set value";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_true(triggerfish_strong_release(strong));
    assert_false(seahorse_red_black_tree_map_s_wr_entry_set_value(
            &object, entry, (const struct triggerfish_weak *) &weak));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_STRONG_IS_INVALID,
                     seahorse_error);
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"entry set value";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    assert_true(triggerfish_weak_destroy(weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_true(triggerfish_weak_of(strong, &weak));
    assert_true(seahorse_red_black_tree_map_s_wr_entry_set_value(
            &object, entry, weak));
    const struct triggerfish_weak *value;
    assert_true(seahorse_red_black_tree_map_s_wr_entry_get_value(
            &object, entry, &value));
    /* exploiting knowledge that the weak reference only contain an atomic
     * pointer to the owning reference.
     * */
    assert_int_equal(*(uintmax_t *) value, *(uintmax_t *) weak);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_entry_set_value_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    const char chars[] = u8"entry set value";
    struct sea_turtle_string key;
    size_t out;
    assert_true(sea_turtle_string_init(&key, chars, sizeof(chars), &out));
    struct triggerfish_strong *strong;
    assert_true(triggerfish_strong_of(malloc(1), on_destroy, &strong));
    struct triggerfish_weak *weak;
    assert_true(triggerfish_weak_of(strong, &weak));
    struct seahorse_red_black_tree_map_s_wr object;
    assert_true(seahorse_red_black_tree_map_s_wr_init(&object));
    assert_true(seahorse_red_black_tree_map_s_wr_add(&object, &key, weak));
    assert_true(triggerfish_weak_destroy(weak));
    const struct seahorse_red_black_tree_map_s_wr_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_wr_get_entry(
            &object, &key, &entry));
    assert_true(triggerfish_weak_of(strong, &weak));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_wr_entry_set_value(
            &object, entry, weak));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_WR_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(triggerfish_strong_release(strong));
    assert_true(triggerfish_weak_destroy(weak));
    assert_true(seahorse_red_black_tree_map_s_wr_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&key));
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
            cmocka_unit_test(check_add_error_on_strong_is_invalid),
            cmocka_unit_test(check_add_error_on_key_already_exists),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_out_is_null),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_contains_error_on_object_is_null),
            cmocka_unit_test(check_contains_error_on_key_is_null),
            cmocka_unit_test(check_contains_error_on_out_is_null),
            cmocka_unit_test(check_contains),
            cmocka_unit_test(check_contains_error_on_memory_allocation_failed),
            cmocka_unit_test(check_set_error_on_object_is_null),
            cmocka_unit_test(check_set_error_on_key_is_null),
            cmocka_unit_test(check_set_error_on_value_is_null),
            cmocka_unit_test(check_set_error_on_strong_is_invalid),
            cmocka_unit_test(check_set),
            cmocka_unit_test(check_set_error_on_memory_allocation_failed),
            cmocka_unit_test(check_get_error_on_object_is_null),
            cmocka_unit_test(check_get_error_on_key_is_null),
            cmocka_unit_test(check_get_error_on_out_is_null),
            cmocka_unit_test(check_get_error_on_key_not_found),
            cmocka_unit_test(check_get),
            cmocka_unit_test(check_get_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_error_key_not_found),
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
            cmocka_unit_test(check_get_entry_on_object_is_null),
            cmocka_unit_test(check_get_entry_on_key_is_null),
            cmocka_unit_test(check_get_entry_on_out_is_null),
            cmocka_unit_test(check_get_entry_on_key_not_found),
            cmocka_unit_test(check_get_entry),
            cmocka_unit_test(check_get_entry_error_on_memory_allocation_failed),
            cmocka_unit_test(check_ceiling_entry_error_on_object_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_key_is_null),
            cmocka_unit_test(check_ceiling_entry_error_on_out_is_null),
            cmocka_unit_test(check_ceiling_entry_error_key_not_found),
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
            cmocka_unit_test(check_last_entry_error_on_map_is_null),
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
            cmocka_unit_test(check_entry_set_value_error_on_strong_is_invalid),
            cmocka_unit_test(check_entry_set_value),
            cmocka_unit_test(check_entry_set_value_error_on_memory_allocation_failed),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
