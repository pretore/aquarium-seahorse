#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_invalidate(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object = {};
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(
            &object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(
            &object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const uintmax_t check = (rand() % UINTMAX_MAX);
    object.map.tree.count = check;
    uintmax_t out;
    assert_true(seahorse_red_black_tree_map_s_p_count(
            &object, (uintmax_t *) &out));
    assert_int_equal(out, check);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_add(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_add(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const char KEY[] = u8"key";
    struct sea_turtle_string key;
    uintmax_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    posix_memalign_is_overridden = false;
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const char KEY[] = u8"key";
    struct sea_turtle_string key;
    uintmax_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_key_already_exists(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const char KEY[] = u8"key";
    struct sea_turtle_string key;
    uintmax_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_false(seahorse_red_black_tree_map_s_p_add(&object, &key, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    assert_true(sea_turtle_string_invalidate(&key));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    assert_false(seahorse_red_black_tree_map_s_p_remove(&object, &key));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_map_s_p_remove(&object, &key));
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 0);
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 1);
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_remove(&object, &key));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    bool result;
    assert_true(seahorse_red_black_tree_map_s_p_contains(
            &object, &key, &result));
    assert_false(result);
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_contains(
            &object, &key, &result));
    assert_true(result);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    bool result;
    assert_true(seahorse_red_black_tree_map_s_p_contains(
            &object, &key, &result));
    assert_false(result);
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_contains(
            &object, &key, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_set(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_set(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden =
            posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_set(&object, &key, NULL));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden =
            posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_set(&object, &key, NULL));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_get(&object, &key, &out));
    assert_null(out);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_set_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_false(seahorse_red_black_tree_map_s_p_set(&object, &key, value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* out;
    assert_false(seahorse_red_black_tree_map_s_p_get(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_get(&object, &key, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_get(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const void *out;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_ceiling(&object, &key, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&query, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_p_ceiling(
            &object, &query, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const void* out;
    assert_false(seahorse_red_black_tree_map_s_p_floor(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    assert_false(seahorse_red_black_tree_map_s_p_floor(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_floor(&object, &key, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    assert_true(seahorse_red_black_tree_map_s_p_floor(
            &object, &query, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_floor(&object, &key, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    assert_false(seahorse_red_black_tree_map_s_p_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_false(seahorse_red_black_tree_map_s_p_higher(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    assert_true(sea_turtle_string_init(&query, KEY0, sizeof(KEY0), &size));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_higher(
            &object, &query, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    assert_true(sea_turtle_string_init(&query, KEY0, sizeof(KEY0), &size));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_higher(
            &object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}









static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_false(seahorse_red_black_tree_map_s_p_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    assert_false(seahorse_red_black_tree_map_s_p_lower(&object, &key, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_lower(
            &object, &query, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY0[] = u8"key0";
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&query, KEY8, sizeof(KEY8), &size));
    const void *out;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_lower(
            &object, &query, &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const void *out;
    assert_false(seahorse_red_black_tree_map_s_p_first(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY9[] = u8"key9";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_first(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_first(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const void *out;
    assert_false(seahorse_red_black_tree_map_s_p_last(&object, &out));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    void const *out;
    assert_true(seahorse_red_black_tree_map_s_p_last(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_last(&object, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_get_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_key_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_get_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_get_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY5[] = u8"key5";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_get_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    const void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY4[] = u8"key4";
    assert_true(sea_turtle_string_init(&key, KEY4, sizeof(KEY4), &size));
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *out;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    const void* v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    assert_true(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &out));
    assert_ptr_not_equal(out, &key);
    assert_int_equal(sea_turtle_string_compare(&key, out), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_ceiling_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}







static void check_floor_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_floor_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY7[] = u8"key7";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY7, sizeof(KEY7), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY4[] = u8"key4";
    assert_true(sea_turtle_string_init(&key, KEY4, sizeof(KEY4), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    assert_false(seahorse_red_black_tree_map_s_p_floor_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    assert_true(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &query, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY1[] = u8"key1";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_ceiling_entry(
            &object, &key, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    size_t size;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_higher_entry(
            &object, &query, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_higher_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    size_t size;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&query, KEY3, sizeof(KEY3), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_higher_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}












static void check_lower_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_key_not_found(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY0[] = u8"key0";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY0, sizeof(KEY0), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY3[] = u8"key3";
    assert_true(sea_turtle_string_init(&key, KEY3, sizeof(KEY3), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, &value));
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            &object, &key, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_KEY_NOT_FOUND,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    size_t size;
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&query, KEY9, sizeof(KEY9), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_lower_entry(
            &object, &query, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_entry_error_on_memory_allocation_failed(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    size_t size;
    const char KEY5[] = u8"key5";
    assert_true(sea_turtle_string_init(&key, KEY5, sizeof(KEY5), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct sea_turtle_string query;
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&query, KEY9, sizeof(KEY9), &size));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_lower_entry(
            &object, &query, &entry));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&query));
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_first_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_first_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_last_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_last_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry_error_on_map_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_false(seahorse_red_black_tree_map_s_p_last_entry(&object, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MAP_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void* value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_last_entry(&object, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_not_equal(v, &value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY8[] = u8"key8";
    assert_true(sea_turtle_string_init(&key, KEY8, sizeof(KEY8), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_last_entry(&object, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_remove_entry(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_remove_entry(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    const char KEY[3][5] = {u8"key0", u8"key1", u8"key2"};
    size_t size;
    for (uintmax_t i = 0; i < 3; i++) {
        struct sea_turtle_string key;
        assert_true(sea_turtle_string_init(&key, KEY[i], sizeof(KEY[i]),
                                           &size));
        const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
        assert_true(seahorse_red_black_tree_map_s_p_add(
                &object, &key, value));
        assert_true(sea_turtle_string_invalidate(&key));
    }
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    struct sea_turtle_string key;
    assert_true(sea_turtle_string_init(&key, KEY[1], sizeof(KEY[1]),
                                       &size));
    assert_true(seahorse_red_black_tree_map_s_p_get_entry(
            &object, &key, &entry));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 3);
    assert_true(seahorse_red_black_tree_map_s_p_remove_entry(&object, entry));
    assert_true(seahorse_red_black_tree_map_s_p_count(&object, &count));
    assert_int_equal(count, 2);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_next_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_next_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, &value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_s_p_next_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_entry(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_next_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_prev_entry(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_prev_entry((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry_error_on_end_of_sequence(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY2[] = u8"key2";
    assert_true(sea_turtle_string_init(&key, KEY2, sizeof(KEY2), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_last_entry(&object, &entry));
    assert_false(seahorse_red_black_tree_map_s_p_prev_entry(entry, &entry));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_entry(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY9[] = u8"key9";
    assert_true(sea_turtle_string_init(&key, KEY9, sizeof(KEY9), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_last_entry(&object, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    assert_true(seahorse_red_black_tree_map_s_p_prev_entry(entry, &entry));
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_key(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_key(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_key(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_key(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    const void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    const struct sea_turtle_string *k;
    assert_true(seahorse_red_black_tree_map_s_p_entry_key(
            &object, entry, &k));
    assert_ptr_not_equal(k, &key);
    assert_int_equal(sea_turtle_string_compare(&key, k), 0);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_get_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_get_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_get_value(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_get_value(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(
            &object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    const void *v;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &v));
    assert_ptr_equal(v, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_set_value(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value_error_on_entry_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_entry_set_value(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_ENTRY_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_entry_set_value(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    size_t size;
    struct sea_turtle_string key;
    void *value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    const char KEY1[] = u8"key1";
    assert_true(sea_turtle_string_init(&key, KEY1, sizeof(KEY1), &size));
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    const struct seahorse_red_black_tree_map_s_p_entry *entry;
    assert_true(seahorse_red_black_tree_map_s_p_first_entry(&object, &entry));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    value = (void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_entry_set_value(
            &object, entry, value));
    assert_true(seahorse_red_black_tree_map_s_p_entry_get_value(
            &object, entry, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_init_red_black_tree_map_s_p_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_init_red_black_tree_map_s_p(
            NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_init_red_black_tree_map_s_p_error_on_other_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_map_s_p_init_red_black_tree_map_s_p(
            (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_OTHER_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_red_black_tree_map_s_p(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct seahorse_red_black_tree_map_s_p copy;
    assert_true(seahorse_red_black_tree_map_s_p_init_red_black_tree_map_s_p(
            &copy, &object));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
    const void *out;
    assert_true(seahorse_red_black_tree_map_s_p_get(&copy, &key, &out));
    assert_ptr_equal(out, value);
    assert_true(sea_turtle_string_invalidate(&key));
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&copy, NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void
check_init_red_black_tree_map_s_p_error_on_memory_allocation_failed(
        void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_map_s_p object;
    assert_true(seahorse_red_black_tree_map_s_p_init(&object));
    struct sea_turtle_string key;
    const char KEY[] = u8"key";
    size_t size;
    assert_true(sea_turtle_string_init(&key, KEY, sizeof(KEY), &size));
    const void* value = (const void *)(uintptr_t) (rand() % UINTMAX_MAX);
    assert_true(seahorse_red_black_tree_map_s_p_add(&object, &key, value));
    struct seahorse_red_black_tree_map_s_p copy;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_map_s_p_init_red_black_tree_map_s_p(
            &copy, &object));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_MAP_S_P_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_map_s_p_invalidate(&object, NULL));
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
            cmocka_unit_test(check_add_error_on_memory_allocation_failed),
            cmocka_unit_test(check_add),
            cmocka_unit_test(check_add_error_on_key_already_exists),
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
            cmocka_unit_test(check_entry_set_value),
            cmocka_unit_test(check_init_red_black_tree_map_s_p_error_on_object_is_null),
            cmocka_unit_test(check_init_red_black_tree_map_s_p_error_on_other_is_null),
            cmocka_unit_test(check_init_red_black_tree_map_s_p),
            cmocka_unit_test(check_init_red_black_tree_map_s_p_error_on_memory_allocation_failed),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
