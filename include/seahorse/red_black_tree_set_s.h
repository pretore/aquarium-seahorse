#ifndef _SEAHORSE_RED_BLACK_TREE_SET_S_H_
#define _SEAHORSE_RED_BLACK_TREE_SET_S_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

struct sea_turtle_string;

#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL              1
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL                 2
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL               3
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_ALREADY_EXISTS        4
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED    5
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_NOT_FOUND             6
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND              7
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY                8
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL                9
#define SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE             10

struct seahorse_red_black_tree_set_s {
    struct coral_red_black_tree_set set;
};

/**
 * @brief Initialize red black tree set.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_s_init(
        struct seahorse_red_black_tree_set_s *object);

/**
 * @brief Invalidate red black tree set.
 * <p>The actual <u>tree set instance is not deallocated</u> since it may
 * have been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_s_invalidate(
        struct seahorse_red_black_tree_set_s *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_s_count(
        const struct seahorse_red_black_tree_set_s *object,
        uintmax_t *out);

/**
 * @brief Add value to the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be added.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_ALREADY_EXISTS if value is
 * already present in the tree set.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to add value to the tree set.
 */
bool seahorse_red_black_tree_set_s_add(
        struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value);

/**
 * @brief Remove value from the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_NOT_FOUND if value is not
 * in the tree set instance.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_remove(
        struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value);

/**
 * @brief Check if tree set contains the given value.
 * @param [in] object tree set instance.
 * @param [in] value to check if value is present.
 * @param [out] out receive true if value is present, otherwise false.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_contains(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        bool *out);

/**
 * @brief Retrieve item for value.
 * @param [in] object tree set instance.
 * @param [in] value to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND if there is no
 * item that matched value.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_get(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        const struct sea_turtle_string **out);

/**
 * @brief Retrieve item for value or the next higher value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next higher.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND if no item
 * matched value or a higher value.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_ceiling(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        const struct sea_turtle_string **out);

/**
 * @brief Retrieve item for value or the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next lower.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND if no item
 * matched value or a lower value.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_floor(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        const struct sea_turtle_string **out);

/**
 * @brief Retrieve item for next higher value.
 * @param [in] object tree set instance.
 * @param [in] value whose next higher value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND if there is no
 * greater value.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_higher(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        const struct sea_turtle_string **out);

/**
 * @brief Retrieve item for the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value whose next lower value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_VALUE_IS_NULL if value is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_NOT_FOUND if there is no
 * lower value.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_MEMORY_ALLOCATION_FAILED if
 * there is insufficient memory to find the item.
 */
bool seahorse_red_black_tree_set_s_lower(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *value,
        const struct sea_turtle_string **out);

/**
 * @brief First item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY if tree set is
 * empty.
 */
bool seahorse_red_black_tree_set_s_first(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string **out);

/**
 * @brief Last item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_SET_IS_EMPTY if tree set is
 * empty.
 */
bool seahorse_red_black_tree_set_s_last(
        const struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string **out);

/**
 * @brief Remove item.
 * @param [in] object tree set instance.
 * @param [in] item <u>address of</u> item to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_s_remove_item(
        struct seahorse_red_black_tree_set_s *object,
        const struct sea_turtle_string *item);

/**
 * @brief Retrieve next item.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE if there is no
 * next item.
 */
bool seahorse_red_black_tree_set_s_next(const struct sea_turtle_string *item,
                                        const struct sea_turtle_string **out);

/**
 * @brief Retrieve the previous item.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_S_ERROR_END_OF_SEQUENCE if there is no
 * previous item.
 */
bool seahorse_red_black_tree_set_s_prev(const struct sea_turtle_string *item,
                                        const struct sea_turtle_string **out);

#endif /* _SEAHORSE_RED_BLACK_TREE_SET_S_H_ */
