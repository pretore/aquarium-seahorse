#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <time.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_invalidate(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object = {};
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_init(NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_count(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_count((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    const uintmax_t check = (rand() % UINTMAX_MAX);
    struct seahorse_red_black_tree_set_s object = {
            .set.tree.count = check
    };
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_s_count(&object, &count));
    assert_int_equal(count, check);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_add(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_add((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_s_count(&object, &count));
    assert_int_equal(count, 0);
    const char chars[] = u8"add";
    struct sea_turtle_string value;
    size_t out;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_s_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_value_already_exists(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const char chars[] = u8"add";
    struct sea_turtle_string value;
    size_t out;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    assert_false(seahorse_red_black_tree_set_s_add(&object, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_ALREADY_EXISTS,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const char chars[] = u8"add";
    struct sea_turtle_string value;
    size_t out;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_add(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_remove(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_remove((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_value_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"remove";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_false(seahorse_red_black_tree_set_s_remove(&object, &value));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"remove";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    uintmax_t count;
    assert_true(seahorse_red_black_tree_set_s_count(&object, &count));
    assert_int_equal(count, 1);
    assert_true(seahorse_red_black_tree_set_s_remove(&object, &value));
    assert_true(seahorse_red_black_tree_set_s_count(&object, &count));
    assert_int_equal(count, 0);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"remove";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_remove(&object, &value));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(sea_turtle_string_invalidate(&value));
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_contains(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_contains(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_contains(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"contains";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    bool result;
    assert_true(seahorse_red_black_tree_set_s_contains(
            &object, &value, &result));
    assert_false(result);
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    assert_true(seahorse_red_black_tree_set_s_contains(
            &object, &value, &result));
    assert_true(result);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_contains_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"contains";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    bool result;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_contains(
            &object, &value, &result));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_get(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_get(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_get(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"get";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_get(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"get";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_get(&object, &value, &item));
    assert_ptr_not_equal(item, &value);
    assert_int_equal(sea_turtle_string_compare(item, &value), 0);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_get_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"get";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    const struct sea_turtle_string *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_get(&object, &value, &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_ceiling(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_ceiling(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_ceiling(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"ceiling";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_ceiling(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"ceiling0", u8"ceiling9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_ceiling(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    assert_true(seahorse_red_black_tree_set_s_ceiling(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_ceiling_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"ceiling0", u8"ceiling9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    const struct sea_turtle_string *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_ceiling(
            &object, &value[0], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_floor(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_floor(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_floor(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"floor";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_floor(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"floor0", u8"floor9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_floor(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    assert_true(seahorse_red_black_tree_set_s_floor(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_floor_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"floor0", u8"floor9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    const struct sea_turtle_string *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_floor(
            &object, &value[1], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_higher(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_higher(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_higher(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"higher";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_higher(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"higher0", u8"higher9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_higher(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    assert_true(seahorse_red_black_tree_set_s_higher(
            &object, &value[0], &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_higher_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"higher0", u8"higher9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    const struct sea_turtle_string *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_higher(
            &object, &value[0], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_lower(
            NULL, (void *) 1, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_value_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_lower(
            (void *) 1, NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_lower(
            (void *) 1, (void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_item_not_found(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"lower";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_lower(&object, &value, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"lower0", u8"lower9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_lower(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[1]));
    assert_true(seahorse_red_black_tree_set_s_lower(
            &object, &value[1], &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_lower_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char *chars[] = {
            u8"lower0", u8"lower9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
    }
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value[0]));
    const struct sea_turtle_string *item;
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_red_black_tree_set_s_lower(
            &object, &value[1], &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(
            SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED,
            seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_first(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_first((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_first(&object, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_first(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"first0", u8"first9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_first(&object, &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}


static void check_last_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_last(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_last((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last_error_on_set_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    const struct sea_turtle_string *item;
    assert_false(seahorse_red_black_tree_set_s_last(&object, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_last(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"last0", u8"last9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_last(&object, &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_remove_item(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_remove_item((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_item(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    size_t out;
    const char chars[] = u8"remove item";
    struct sea_turtle_string value;
    assert_true(sea_turtle_string_init(&value, chars, strlen(chars), &out));
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    assert_true(seahorse_red_black_tree_set_s_add(&object, &value));
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_get(&object, &value, &item));
    assert_true(seahorse_red_black_tree_set_s_remove_item(&object, item));
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    assert_true(sea_turtle_string_invalidate(&value));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_next(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_next((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"check next0", u8"check next9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_first(&object, &item));
    assert_true(seahorse_red_black_tree_set_s_next(item, &item));
    assert_ptr_not_equal(item, &value[1]);
    assert_int_equal(sea_turtle_string_compare(item, &value[1]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_next_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"check next0", u8"check next9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_last(&object, &item));
    assert_false(seahorse_red_black_tree_set_s_next(item, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_prev(NULL, (void *) 1));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_red_black_tree_set_s_prev((void *) 1, NULL));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"check prev0", u8"check prev9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_last(&object, &item));
    assert_true(seahorse_red_black_tree_set_s_prev(item, &item));
    assert_ptr_not_equal(item, &value[0]);
    assert_int_equal(sea_turtle_string_compare(item, &value[0]), 0);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_prev_error_on_end_of_sequence(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_red_black_tree_set_s object;
    assert_true(seahorse_red_black_tree_set_s_init(&object));
    size_t out;
    const char *chars[] = {
            u8"check prev0", u8"check prev9"
    };
    const uintmax_t limit = sizeof(chars) / sizeof(const char *);
    struct sea_turtle_string value[2];
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_init(&value[i], chars[i],
                                           strlen(chars[i]), &out));
        assert_true(seahorse_red_black_tree_set_s_add(&object, &value[i]));
    }
    const struct sea_turtle_string *item;
    assert_true(seahorse_red_black_tree_set_s_first(&object, &item));
    assert_false(seahorse_red_black_tree_set_s_prev(item, &item));
    assert_int_equal(SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE,
                     seahorse_error);
    for (uintmax_t i = 0; i < limit; i++) {
        assert_true(sea_turtle_string_invalidate(&value[i]));
    }
    assert_true(seahorse_red_black_tree_set_s_invalidate(&object));
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
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
