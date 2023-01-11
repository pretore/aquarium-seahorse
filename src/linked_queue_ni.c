#include <stdlib.h>
#include <seagrass.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

bool seahorse_linked_queue_ni_init(
        struct seahorse_linked_queue_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_linked_queue_ni) {0};
    seagrass_required_true(coral_linked_queue_init(
            &object->queue, sizeof(uintmax_t)));
    return true;
}

bool seahorse_linked_queue_ni_invalidate(
        struct seahorse_linked_queue_ni *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_queue_invalidate(
            &object->queue, NULL));
    *object = (struct seahorse_linked_queue_ni) {0};
    return true;
}

bool seahorse_linked_queue_ni_count(
        const struct seahorse_linked_queue_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_queue_count(
            &object->queue, out));
    return true;
}

bool seahorse_linked_queue_ni_add(
        struct seahorse_linked_queue_ni *const object,
        const uintmax_t item) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_queue_add(&object->queue, &item);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seahorse_error =
                SEAHORSE_LINKED_QUEUE_NI_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_linked_queue_ni_remove(
        struct seahorse_linked_queue_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_queue_remove(&object->queue,
                                                  (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_QUEUE_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY;
    }
    return result;
}

bool seahorse_linked_queue_ni_peek(
        const struct seahorse_linked_queue_ni *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_queue_peek(&object->queue,
                                                (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_QUEUE_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY;
    }
    return result;
}
