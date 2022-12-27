#ifndef _SEAHORSE_LINKED_STACK_NI_H_
#define _SEAHORSE_LINKED_STACK_NI_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

#define SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL               1
#define SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL                  2
#define SEAHORSE_LINKED_STACK_NI_ERROR_MEMORY_ALLOCATION_FAILED     3
#define SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY               4

struct seahorse_linked_stack_ni {
    struct coral_linked_stack stack;
};

/**
 * @brief Initialize linked stack.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_stack_ni_init(struct seahorse_linked_stack_ni *object);

/**
 * @brief Invalidate linked stack.
 * <p>The actual <u>stack instance is not deallocated</u> since it may have
 * been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_linked_stack_ni_invalidate(
        struct seahorse_linked_stack_ni *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_linked_stack_ni_count(
        const struct seahorse_linked_stack_ni *object,
        uintmax_t *out);

/**
 * @brief Add item to the top of the linked stack.
 * @param [in] object linked stack instance.
 * @param [in] item to add to the top of the linked stack.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_MEMORY_ALLOCATION_FAILED if there
 * is insufficient memory to add item to linked stack.
 */
bool seahorse_linked_stack_ni_push(struct seahorse_linked_stack_ni *object,
                                   uintmax_t item);

/**
 * @brief Remove item from the top of the stack.
 * @param [in] object linked stack instance.
 * @param [in] out receive the item in the top of the linked stack.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY if linked stack is
 * empty.
 */
bool seahorse_linked_stack_ni_pop(struct seahorse_linked_stack_ni *object,
                                  uintmax_t *out);

/**
 * @brief Retrieve the item from the top of the stack without removing it.
 * @param [in] object linked stack instance.
 * @param [in] out receive the item in the top of the linked stack without
 * removing it.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_STACK_NI_ERROR_STACK_IS_EMPTY if linked stack is
 * empty.
 */
bool seahorse_linked_stack_ni_peek(
        const struct seahorse_linked_stack_ni *object,
        uintmax_t *out);

#endif /* _SEAHORSE_LINKED_STACK_NI_H_ */
