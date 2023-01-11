#include <stdlib.h>
#include <seagrass.h>
#include <triggerfish.h>
#include <seahorse.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

bool seahorse_linked_queue_sr_init(
        struct seahorse_linked_queue_sr *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    *object = (struct seahorse_linked_queue_sr) {0};
    seagrass_required_true(coral_linked_queue_init(
            &object->queue,
            sizeof(struct triggerfish_strong *)));
    return true;
}

static void on_destroy(void *const a) {
    struct triggerfish_strong **const A = a;
    seagrass_required_true(triggerfish_strong_release(*A));
}

bool seahorse_linked_queue_sr_invalidate(
        struct seahorse_linked_queue_sr *const object) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_queue_invalidate(
            &object->queue, on_destroy));
    *object = (struct seahorse_linked_queue_sr) {0};
    return true;
}

bool seahorse_linked_queue_sr_count(
        const struct seahorse_linked_queue_sr *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    seagrass_required_true(coral_linked_queue_count(
            &object->queue, out));
    return true;
}

bool seahorse_linked_queue_sr_add(
        struct seahorse_linked_queue_sr *const object,
        struct triggerfish_strong *const item) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!triggerfish_strong_retain(item)) {
        seagrass_required_true(TRIGGERFISH_STRONG_ERROR_OBJECT_IS_INVALID
                               == triggerfish_error);
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_INVALID;
        return false;
    }
    const bool result = coral_linked_queue_add(&object->queue, &item);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_MEMORY_ALLOCATION_FAILED
                               == coral_error);
        seagrass_required_true(triggerfish_strong_release(item));
        seahorse_error =
                SEAHORSE_LINKED_QUEUE_SR_ERROR_MEMORY_ALLOCATION_FAILED;
    }
    return result;
}

bool seahorse_linked_queue_sr_remove(
        struct seahorse_linked_queue_sr *const object,
        struct triggerfish_strong **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_queue_remove(&object->queue,
                                                  (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_QUEUE_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY;
    }
    return result;
}

bool seahorse_linked_queue_sr_peek(
        const struct seahorse_linked_queue_sr *const object,
        struct triggerfish_strong **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL;
        return false;
    }
    const bool result = coral_linked_queue_peek(&object->queue,
                                                (void **) out);
    if (!result) {
        seagrass_required_true(CORAL_LINKED_QUEUE_ERROR_QUEUE_IS_EMPTY
                               == coral_error);
        seahorse_error = SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY;
    }
    return result;
}
