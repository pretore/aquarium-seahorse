#ifndef _SEAHORSE_RED_BLACK_TREE_SET_I_H_
#define _SEAHORSE_RED_BLACK_TREE_SET_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <rock.h>

struct sea_turtle_integer;

#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL              1
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL                 2
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED    3
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS        4
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_NOT_FOUND             5
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND              6
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY                7
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL                8
#define SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE             9

struct seahorse_red_black_tree_set_i {
    struct rock_red_black_tree_set set;
};

/**
 * @brief Initialize red black tree set.
 * @param [in] object instance to be initialized.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_i_init(
        struct seahorse_red_black_tree_set_i *object);

/**
 * @brief Invalidate red black tree set.
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_i_invalidate(
        struct seahorse_red_black_tree_set_i *object);

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_i_count(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t *out);

/**
 * @brief Add value to the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be added.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_ALREADY_EXISTS if value is
 * already present in the tree set.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_MEMORY_ALLOCATION_FAILED if
 * there was not enough memory to add value to the tree set.
 */
bool seahorse_red_black_tree_set_i_add(
        struct seahorse_red_black_tree_set_i *object,
        uintmax_t value);

/**
 * @brief Remove value from the tree set.
 * @param [in] object tree set instance.
 * @param [in] value to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_VALUE_NOT_FOUND if value is not
 * in the tree set instance.
 */
bool seahorse_red_black_tree_set_i_remove(
        struct seahorse_red_black_tree_set_i *object,
        uintmax_t value);

/**
 * @brief Check if tree set contains the given value.
 * @param [in] object tree set instance.
 * @param [in] value to check if value is present.
 * @param [out] out receive true if value is present, otherwise false.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 */
bool seahorse_red_black_tree_set_i_contains(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        bool *out);

/**
 * @brief Retrieve item for value.
 * @param [in] object tree set instance.
 * @param [in] value to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND if there is no
 * item that matched value.
 */
bool seahorse_red_black_tree_set_i_get(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for value or the next higher value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next higher.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND if no item
 * matched value or a higher value.
 */
bool seahorse_red_black_tree_set_i_ceiling(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for value or the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value to find or its next lower.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND if no item
 * matched value or a lower value.
 */
bool seahorse_red_black_tree_set_i_floor(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for next higher value.
 * @param [in] object tree set instance.
 * @param [in] value whose next higher value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND if there is no
 * greater value.
 */
bool seahorse_red_black_tree_set_i_higher(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief Retrieve item for the next lower value.
 * @param [in] object tree set instance.
 * @param [in] value whose next lower value we are trying to find.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_NOT_FOUND if there is no
 * lower value.
 */
bool seahorse_red_black_tree_set_i_lower(
        const struct seahorse_red_black_tree_set_i *object,
        uintmax_t value,
        const uintmax_t **out);

/**
 * @brief First item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY if tree set is
 * empty.
 */
bool seahorse_red_black_tree_set_i_first(
        const struct seahorse_red_black_tree_set_i *object,
        const uintmax_t **out);

/**
 * @brief Last item of the tree set.
 * @param [in] object tree set instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OBJECT_IS_NULL if object is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_SET_IS_EMPTY if tree set is
 * empty.
 */
bool seahorse_red_black_tree_set_i_last(
        const struct seahorse_red_black_tree_set_i *object,
        const uintmax_t **out);

/**
 * @brief Retrieve next item.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE if there is no
 * next item.
 */
bool seahorse_red_black_tree_set_i_next(const uintmax_t *item,
                                        const uintmax_t **out);

/**
 * @brief Retrieve the previous item.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_ITEM_IS_NULL if item is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_OUT_IS_NULL if out is
 * <i>NULL</i>.
 * @throws SEAHORSE_RED_BLACK_TREE_SET_I_ERROR_END_OF_SEQUENCE if there is no
 * previous item.
 */
bool seahorse_red_black_tree_set_i_prev(const uintmax_t *item,
                                        const uintmax_t **out);

#endif /* _SEAHORSE_RED_BLACK_TREE_SET_I_H_ */
