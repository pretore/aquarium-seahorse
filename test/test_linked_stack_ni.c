#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seahorse.h>

#include "test/cmocka.h"

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_init(NULL));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object = {};
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_init(NULL));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_count(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_count((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object = {
            .stack.count = rand() % UINTMAX_MAX
    };
    uintmax_t out;
    assert_true(seahorse_linked_stack_ni_count(&object, &out));
    assert_int_equal(out, object.stack.count);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_push_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_push(NULL, 0));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_push_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_linked_stack_ni_push(&object, 0));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_push(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    const uintmax_t values[] = {
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX
    };
    const uintmax_t counter = sizeof(values) / sizeof(uintmax_t);
    for (uintmax_t i = 0; i < counter; i++) {
        assert_true(seahorse_linked_stack_ni_push(&object, values[i]));
    }
    uintmax_t out;
    for (uintmax_t i = 0; i < counter; i++) {
        assert_true(seahorse_linked_stack_ni_pop(&object, &out));
        assert_int_equal(out, values[counter - (1 + i)]);
    }
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_pop_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_pop(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_pop_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_pop((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_pop_error_on_stack_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    assert_false(seahorse_linked_stack_ni_pop(&object, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_pop(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    const uintmax_t values[] = {
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX
    };
    const uintmax_t counter = sizeof(values) / sizeof(uintmax_t);
    for (uintmax_t i = 0; i < counter; i++) {
        assert_true(seahorse_linked_stack_ni_push(&object, values[i]));
    }
    uintmax_t out;
    for (uintmax_t i = 0; i < counter; i++) {
        assert_true(seahorse_linked_stack_ni_pop(&object, &out));
        assert_int_equal(out, values[counter - (1 + i)]);
    }
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_peek(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_stack_ni_peek((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_stack_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    assert_false(seahorse_linked_stack_ni_peek(&object, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_stack_ni object;
    assert_true(seahorse_linked_stack_ni_init(&object));
    const uintmax_t value = rand() % UINTMAX_MAX;
    assert_true(seahorse_linked_stack_ni_push(&object, value));
    uintmax_t out;
    assert_true(seahorse_linked_stack_ni_peek(&object, &out));
    assert_int_equal(out, value);
    assert_true(seahorse_linked_stack_ni_peek(&object, &out));
    assert_int_equal(out, value);
    assert_true(seahorse_linked_stack_ni_invalidate(&object));
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
            cmocka_unit_test(check_push_error_on_object_is_null),
            cmocka_unit_test(check_push_error_on_memory_allocation_failed),
            cmocka_unit_test(check_push),
            cmocka_unit_test(check_pop_error_on_object_is_null),
            cmocka_unit_test(check_pop_error_on_out_is_null),
            cmocka_unit_test(check_pop_error_on_stack_is_empty),
            cmocka_unit_test(check_pop),
            cmocka_unit_test(check_peek_error_on_object_is_null),
            cmocka_unit_test(check_peek_error_on_out_is_null),
            cmocka_unit_test(check_peek_error_on_stack_is_empty),
            cmocka_unit_test(check_peek),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
