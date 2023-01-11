#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <time.h>
#include <seahorse.h>

#include <test/cmocka.h>

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_invalidate(NULL));
    assert_ptr_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object = {};
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_init(NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_count(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_count((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object = {
            .queue.count = rand() % UINTMAX_MAX
    };
    uintmax_t out;
    assert_true(seahorse_linked_queue_ni_count(&object, &out));
    assert_int_equal(out, object.queue.count);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_add(NULL, 0));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_linked_queue_ni_add(&object, 0));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    const uintmax_t check = rand() % UINTMAX_MAX;
    assert_true(seahorse_linked_queue_ni_add(&object, check));
    uintmax_t out;
    assert_true(seahorse_linked_queue_ni_remove(&object, &out));
    assert_int_equal(out, check);
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_remove(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_remove((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_queue_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    uintmax_t out;
    assert_false(seahorse_linked_queue_ni_remove(&object, &out));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    const uintmax_t values[] = {
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
            rand() % UINTMAX_MAX,
    };
    uintmax_t count = sizeof(values) / sizeof(uintmax_t);
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(seahorse_linked_queue_ni_add(&object, values[i]));
    }
    uintmax_t out;
    for (uintmax_t i = 0; i < count; i++) {
        assert_true(seahorse_linked_queue_ni_remove(&object, &out));
        assert_int_equal(out, values[i]);
    }
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_peek(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_peek((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_queue_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    uintmax_t out;
    assert_false(seahorse_linked_queue_ni_peek(&object, &out));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_ni object;
    assert_true(seahorse_linked_queue_ni_init(&object));
    const uintmax_t check = rand() % UINTMAX_MAX;
    assert_true(seahorse_linked_queue_ni_add(&object, check));
    uintmax_t out;
    for (uintmax_t i = 0; i < 3; i++) {
        assert_true(seahorse_linked_queue_ni_peek(&object, &out));
        assert_int_equal(out, check);
    }
    assert_true(seahorse_linked_queue_ni_invalidate(&object));
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
            cmocka_unit_test(check_remove_error_on_object_is_null),
            cmocka_unit_test(check_remove_error_on_out_is_null),
            cmocka_unit_test(check_remove_error_on_queue_is_empty),
            cmocka_unit_test(check_remove),
            cmocka_unit_test(check_peek_error_on_object_is_null),
            cmocka_unit_test(check_peek_error_on_out_is_null),
            cmocka_unit_test(check_peek_error_on_queue_is_empty),
            cmocka_unit_test(check_peek),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
