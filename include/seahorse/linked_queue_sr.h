#ifndef _SEAHORSE_LINKED_QUEUE_SR_H_
#define _SEAHORSE_LINKED_QUEUE_SR_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

struct triggerfish_strong;

#define SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL               1
#define SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL                  2
#define SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_NULL                 3
#define SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_INVALID              4
#define SEAHORSE_LINKED_QUEUE_SR_ERROR_MEMORY_ALLOCATION_FAILED     5
#define SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY               6

struct seahorse_linked_queue_sr {
    struct coral_linked_queue queue;
};

/**
 * @brief Initialize linked queue.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_queue_sr_init(struct seahorse_linked_queue_sr *object);

/**
 * @brief Invalidate linked queue.
 * <p>The actual <u>linked queue instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_queue_sr_invalidate(
        struct seahorse_linked_queue_sr *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_linked_queue_sr_count(
        const struct seahorse_linked_queue_sr *object,
        uintmax_t *out);

/**
 * @brief Add item to the end of the linked queue.
 * @param [in] object linked queue instance.
 * @param [in] item to add to the end of the queue.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_ITEM_IS_INVALID if the strong
 * reference of item has been invalidated.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_MEMORY_ALLOCATION_FAILED if there
 * is insufficient memory to add item to linked queue.
 */
bool seahorse_linked_queue_sr_add(struct seahorse_linked_queue_sr *object,
                                  struct triggerfish_strong *item);

/**
 * @brief Remove item from the front of the linked queue.
 * @param [in] object linked queue instance.
 * @param [out] out receive the item in the front of the linked queue.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY if linked queue is
 * empty.
 */
bool seahorse_linked_queue_sr_remove(struct seahorse_linked_queue_sr *object,
                                     struct triggerfish_strong **out);

/**
 * @brief Retrieve the item from the front of the queue without removing it.
 * @param [in] object linked queue instance.
 * @param [in] out receive the item in the front of the queue without
 * removing it.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_SR_ERROR_QUEUE_IS_EMPTY if linked queue is
 * empty.
 * @note The retrieved item's reference count was not increased.
 */
bool seahorse_linked_queue_sr_peek(
        const struct seahorse_linked_queue_sr *object,
        struct triggerfish_strong **out);

#endif /* _SEAHORSE_LINKED_QUEUE_SR_H_ */
