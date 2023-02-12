#ifndef _SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_H_
#define _SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL           1
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL              2
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS     3
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED 4
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_NOT_FOUND          5
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND           6
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY             7
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL             8
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE          9
#define SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OTHER_IS_NULL            10

struct seahorse_linked_red_black_tree_set_ni {
    struct coral_linked_red_black_tree_set set;
};

/**
 * @brief Initialize linked red black tree set.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 */
bool seahorse_linked_red_black_tree_set_ni_init(
        struct seahorse_linked_red_black_tree_set_ni *object);

/**
 * @brief Copy initialize linked red black tree set.
 * @param [in] object instance to be initialized.
 * @param [in] other linked red black tree set to be copied.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OTHER_IS_NULL if other
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to create a copy.
 */
bool seahorse_linked_red_black_tree_set_ni_init_linked_red_black_tree_set_ni(
        struct seahorse_linked_red_black_tree_set_ni *object,
        const struct seahorse_linked_red_black_tree_set_ni *other);

/**
 * @brief Invalidate linked red black tree set.
 * <p>The actual <u>tree set instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 */
bool seahorse_linked_red_black_tree_set_ni_invalidate(
        struct seahorse_linked_red_black_tree_set_ni *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_linked_red_black_tree_set_ni_count(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t *out);

/**
 * @brief Add value to the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be added.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS
 * if value is already present in the tree set.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there was insufficient memory to add value to the tree set.
 */
bool seahorse_linked_red_black_tree_set_ni_add(
        struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value);

/**
 * @brief Remove value from the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_NOT_FOUND if
 * value is not in the tree set instance.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_remove(
        struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value);

/**
 * @brief Check if tree set contains the given value.
 * @param [in] object tree set instance.
 * @param [in] value to check if value is present.
 * @param [out] out receive true if value is present, otherwise false.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_contains(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        bool *out);

/**
 * @brief Retrieve item for value.
 * @param [in] object tree set instance.
 * @param [in] value to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND if
 * there is no item that matched value.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_get(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for value or the next higher value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next higher.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND if no
 * item matched value or a higher value.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_ceiling(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for value or the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next lower.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND if no
 * item matched value or a lower value.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_floor(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for next higher value.
 * @param [in] object tree set instance.
 * @param [in] value whose next higher value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND if
 * there is no greater value.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_higher(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value whose next lower value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_NOT_FOUND if
 * there is no lower value.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there is insufficient memory to find the item.
 */
bool seahorse_linked_red_black_tree_set_ni_lower(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item with the highest value.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY if tree
 * set is empty.
 */
bool seahorse_linked_red_black_tree_set_ni_highest(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t **out);

/**
 * @brief Retrieve item with the lowest value.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY if tree
 * set is empty.
 */
bool seahorse_linked_red_black_tree_set_ni_lowest(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t **out);

/**
 * @brief First item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY if tree
 * set is empty.
 */
bool seahorse_linked_red_black_tree_set_ni_first(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t **out);

/**
 * @brief Last item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_SET_IS_EMPTY if tree
 * set is empty.
 */
bool seahorse_linked_red_black_tree_set_ni_last(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t **out);

/**
 * @brief Remove item.
 * @param [in] object tree set instance.
 * @param [out] item <u>address of</u> item to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 */
bool seahorse_linked_red_black_tree_set_ni_remove_item(
        struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t *item);

/**
 * @brief Retrieve next item.
 * @param [in] object tree set instance.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if item
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE if
 * there is no next item.
 */
bool seahorse_linked_red_black_tree_set_ni_next(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t *item,
        const uintmax_t **out);

/**
 * @brief Retrieve previous item.
 * @param [in] object tree set instance.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if item
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_END_OF_SEQUENCE if there
 * is no previous item.
 */
bool seahorse_linked_red_black_tree_set_ni_prev(
        const struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t *item,
        const uintmax_t **out);

/**
 * @brief Insert value after item.
 * @param [in] object tree set instance.
 * @param [in] item current <u>address of</u> item after which <b>value</b>
 * will be inserted.
 * @param [in] value to be inserted.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_VALUE_ALREADY_EXISTS if
 * value is already present in the tree set.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there was not enough memory to add value to the tree set.
 */
bool seahorse_linked_red_black_tree_set_ni_insert_after(
        struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t *item,
        uintmax_t value);

/**
 * @brief Insert value before item.
 * @param [in] object tree set instance.
 * @param [in] item current <u>address of</u> item before which <b>value</b>
 * will be inserted.
 * @param [in] value to be inserted.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if
 * object is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws ROCK_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS if value is
 * already present in the tree set.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there was not enough memory to add value to the tree set.
 */
bool seahorse_linked_red_black_tree_set_ni_insert_before(
        struct seahorse_linked_red_black_tree_set_ni *object,
        const uintmax_t *item,
        uintmax_t value);

/**
 * @brief Add value to the end.
 * @param [in] object tree set instance.
 * @param [in] value which will be added after all values.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS if
 * value is already present in the tree set.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there was not enough memory to add value to the tree set.
 */
bool seahorse_linked_red_black_tree_set_ni_append(
        struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value);

/**
 * @brief Add value to the beginning.
 * @param [in] object tree set instance.
 * @param [in] value which will be added before all other values.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_OBJECT_IS_NULL if object
 * is <i>NULL</i>.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_ERROR_VALUE_ALREADY_EXISTS if
 * value is already present in the tree set.
 * @throws SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_ERROR_MEMORY_ALLOCATION_FAILED
 * if there was not enough memory to add value to the tree set.
 */
bool seahorse_linked_red_black_tree_set_ni_prepend(
        struct seahorse_linked_red_black_tree_set_ni *object,
        uintmax_t value);

#endif /* _SEAHORSE_LINKED_RED_BLACK_TREE_SET_NI_H_ */
