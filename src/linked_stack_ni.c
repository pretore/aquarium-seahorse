#include <stdlib.h>
#include <seagrass.h>
#include <seahorse.h>

bool seahorse_linked_stack_ni_init(
        struct seahorse_linked_stack_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_linked_stack_ni) {0};
    seagrass_required_true(coral_linked_stack_init(
            &object->stack, sizeof(uintmax_t)));
    return true;
}

bool seahorse_linked_stack_ni_invalidate(
        struct seahorse_linked_stack_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_stack_invalidate(
            &object->stack, NULL));
    return true;
}

bool seahorse_linked_stack_ni_count(
        const struct seahorse_linked_stack_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_stack_count(
            &object->stack, out));
    return true;
}

bool seahorse_linked_stack_ni_push(
        struct seahorse_linked_stack_ni *const object,
        const uintmax_t item) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_stack_push(&object->stack, &item);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_STACK_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_STACK_NI_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_linked_stack_ni_pop(
        struct seahorse_linked_stack_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_stack_pop(&object->stack,
                                               (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_STACK_ERROR_STACK_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY;
    }
    return result;
}

bool seahorse_linked_stack_ni_peek(
        const struct seahorse_linked_stack_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_stack_peek(&object->stack,
                                                (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_STACK_ERROR_STACK_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY;
    }
    return result;
}
