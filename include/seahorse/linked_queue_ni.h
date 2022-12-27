#ifndef _SEAHORSE_LINKED_QUEUE_NI_H_
#define _SEAHORSE_LINKED_QUEUE_NI_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

#define SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL               1
#define SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL                  2
#define SEAHORSE_LINKED_QUEUE_NI_ERROR_MEMORY_ALLOCATION_FAILED     3
#define SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY               4

struct seahorse_linked_queue_ni {
    struct coral_linked_queue queue;
};

/**
 * @brief Initialize linked queue.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_queue_ni_init(struct seahorse_linked_queue_ni *object);

/**
 * @brief Invalidate linked queue.
 * <p>The actual <u>linked queue instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_queue_ni_invalidate(
        struct seahorse_linked_queue_ni *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_linked_queue_ni_count(
        const struct seahorse_linked_queue_ni *object,
        uintmax_t *out);

/**
 * @brief Add item to the end of the linked queue.
 * @param [in] object linked queue instance.
 * @param [in] item to add to the end of the queue.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_MEMORY_ALLOCATION_FAILED if there
 * is insufficient memory to add item to linked queue.
 */
bool seahorse_linked_queue_ni_add(struct seahorse_linked_queue_ni *object,
                                  uintmax_t item);

/**
 * @brief Remove item from the front of the linked queue.
 * @param [in] object linked queue instance.
 * @param [out] out receive the item in the front of the linked queue.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY if linked queue is
 * empty.
 */
bool seahorse_linked_queue_ni_remove(struct seahorse_linked_queue_ni *object,
                                     uintmax_t *out);

/**
 * @brief Retrieve the item from the front of the queue without removing it.
 * @param [in] object linked queue instance.
 * @param [in] out receive the item in the front of the queue without
 * removing it.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_QUEUE_NI_ERROR_QUEUE_IS_EMPTY if linked queue is
 * empty.
 */
bool seahorse_linked_queue_ni_peek(
        const struct seahorse_linked_queue_ni *object,
        uintmax_t *out);

#endif /* _SEAHORSE_LINKED_QUEUE_NI_H_ */
