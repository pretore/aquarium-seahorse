#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdatomic.h>
#include <time.h>
#include <triggerfish.h>
#include <seahorse.h>

#include "test/cmocka.h"

static void check_invalidate_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_invalidate(NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_invalidate(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object = {};
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_init(NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_init(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_count(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_count((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_count(void **state) {
    srand(time(NULL));
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object = {
            .queue.count = rand() % UINTMAX_MAX
    };
    uintmax_t out;
    assert_true(seahorse_linked_queue_sr_count(&object, &out));
    assert_int_equal(out, object.queue.count);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_add(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_item_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_add((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add_error_on_item_is_invalid(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    /* exploiting knowledge that the first field of strong is the atomic
     * counter for reference counting */
    atomic_uintmax_t counter;
    atomic_store(&counter, 0);
    assert_false(seahorse_linked_queue_sr_add(
            (void *)1, (struct triggerfish_strong *) &counter));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_INVALID,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void on_destroy(void *instance) {

}

static void check_add_error_on_memory_allocation_failed(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    void *instance = malloc(1);
    struct triggerfish_strong *item;
    assert_true(triggerfish_strong_of(instance, on_destroy, &item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = true;
    assert_false(seahorse_linked_queue_sr_add(&object, item));
    malloc_is_overridden = calloc_is_overridden = realloc_is_overridden
            = posix_memalign_is_overridden = false;
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_MEMORY_ALLOCATION_FAILED,
                     seahorse_error);
    assert_true(triggerfish_strong_release(item));
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_add(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    void *instance = malloc(1);
    struct triggerfish_strong *item;
    assert_true(triggerfish_strong_of(instance, on_destroy, &item));
    assert_true(seahorse_linked_queue_sr_add(&object, item));
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(item));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_remove(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_remove((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove_error_on_queue_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    struct triggerfish_strong *out;
    assert_false(seahorse_linked_queue_sr_remove(&object, &out));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_remove(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    void *instance = malloc(1);
    struct triggerfish_strong *item;
    assert_true(triggerfish_strong_of(instance, on_destroy, &item));
    assert_true(seahorse_linked_queue_sr_add(&object, item));
    struct triggerfish_strong *out;
    assert_true(seahorse_linked_queue_sr_remove(&object, &out));
    assert_int_equal(out, item);
    assert_true(triggerfish_strong_release(item));
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(item));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_object_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_sr_peek(NULL, (void *)1));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_out_is_null(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    assert_false(seahorse_linked_queue_ni_peek((void *)1, NULL));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL,
                     seahorse_error);
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek_error_on_queue_is_empty(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    struct triggerfish_strong *out;
    assert_false(seahorse_linked_queue_sr_peek(&object, &out));
    assert_int_equal(SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY,
                     seahorse_error);
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    seahorse_error = SEAHORSE_ERROR_NONE;
}

static void check_peek(void **state) {
    seahorse_error = SEAHORSE_ERROR_NONE;
    struct seahorse_linked_queue_sr object;
    assert_true(seahorse_linked_queue_sr_init(&object));
    void *instance = malloc(1);
    struct triggerfish_strong *item;
    assert_true(triggerfish_strong_of(instance, on_destroy, &item));
    assert_true(seahorse_linked_queue_sr_add(&object, item));
    struct triggerfish_strong *out;
    assert_true(seahorse_linked_queue_sr_peek(&object, &out));
    assert_int_equal(out, item);
    assert_true(seahorse_linked_queue_sr_invalidate(&object));
    assert_true(triggerfish_strong_release(item));
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
            cmocka_unit_test(check_add_error_on_item_is_null),
            cmocka_unit_test(check_add_error_on_item_is_invalid),
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
