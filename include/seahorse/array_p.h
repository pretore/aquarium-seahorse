#ifndef _SEAHORSE_ARRAY_P_H_
#define _SEAHORSE_ARRAY_P_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <rock.h>

#define SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL                       1
#define SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED             2
#define SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL                          3
#define SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO                        4
#define SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL                       5
#define SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY                       6
#define SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS               7
#define SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL                         8
#define SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS                9
#define SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE                      10

struct seahorse_array_p {
    struct rock_array array;
};

/**
 * @brief Initialise array.
 * @param [in] object instance to be initialised.
 * @param [in] capacity set the initial capacity.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is
 * insufficient memory to initialize the array instance.
 */
bool seahorse_array_p_init(struct seahorse_array_p *object, uintmax_t capacity);

/**
 * @brief Invalidate the array.
 * <p>The actual <u>array instance is not deallocated</u> since it may have
 * been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool seahorse_array_p_invalidate(struct seahorse_array_p *object);

/**
 * @brief Retrieve the capacity.
 * @param [in] object array instance.
 * @param [in] out receive the capacity.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_array_p_capacity(const struct seahorse_array_p *object,
                               uintmax_t *out);

/**
 * @brief Retrieve the length.
 * @param [in] object array instance.
 * @param [in] out receive the number of items.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_array_p_get_length(const struct seahorse_array_p *object,
                                 uintmax_t *out);

/**
 * @brief Set the length.
 * @param [in] object array instance.
 * @param [in] length number of items in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to set the array length.
 */
bool seahorse_array_p_set_length(struct seahorse_array_p *object,
                                 uintmax_t length);

/**
 * @brief Release excess capacity.
 * @param [in] object array instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool seahorse_array_p_shrink(struct seahorse_array_p *object);

/**
 * @brief Add an item at the end.
 * @param [in] object array instance.
 * @param [in] value to add at the end of the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to add another value.
 */
bool seahorse_array_p_add(struct seahorse_array_p *object, const void *value);

/**
 * @brief Add all the items at the end.
 * @param [in] object array instance.
 * @param [in] count number of values.
 * @param [in] values all of which we would like to add to the end of the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL is values is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to all the values.
 */
bool seahorse_array_p_add_all(struct seahorse_array_p *object,
                              uintmax_t count,
                              const void **values);

/**
 * @brief Remove last item.
 * @param [in] object array instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_p_remove_last(struct seahorse_array_p *object);

/**
 * @brief Insert an value at index.
 * @param [in] object array instance.
 * @param [in] at index where item is to be inserted.
 * @param [in] value to be inserted.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to insert value.
 */
bool seahorse_array_p_insert(struct seahorse_array_p *object,
                             uintmax_t at,
                             const void *value);

/**
 * @brief Insert all the values at index.
 * @param [in] object array instance.
 * @param [in] at index where items are to be inserted.
 * @param [in] count number of values.
 * @param [in] values all of which we would like to insert into the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 * @throws SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_P_ERROR_VALUES_IS_NULL if values is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to insert all the values into the array.
 */
bool seahorse_array_p_insert_all(struct seahorse_array_p *object,
                                 uintmax_t at,
                                 uintmax_t count,
                                 const void **values);

/**
 * @brief Remove an item at the given index.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_p_remove(struct seahorse_array_p *object, uintmax_t at);

/**
 * @brief Remove all the items from the given index up to count items.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @param [in] count of items to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_p_remove_all(struct seahorse_array_p *object,
                                 uintmax_t at,
                                 uintmax_t count);

/**
 * @brief Retrieve the value at the given index.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_p_get(const struct seahorse_array_p *object,
                          uintmax_t at,
                          void **out);

/**
 * @brief Set the value at the given index.
 * @param [in] object array instance.
 * @param [in] at index where value should be stored.
 * @param [in] value to set at index.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_p_set(struct seahorse_array_p *object,
                          uintmax_t at,
                          const void *value);

/**
 * @brief First item of the array.
 * @param [in] object array instance.
 * @param [out] out receive <u>address of</u> first item in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_p_first(const struct seahorse_array_p *object, void ***out);

/**
 * @brief Last item of the array.
 * @param [in] object array instance.
 * @param [out] out receive <u>address of</u> last item in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_p_last(const struct seahorse_array_p *object, void ***out);

/**
 * @brief Retrieve next item.
 * @param [in] object array instance.
 * @param [in] item <u>address of</u> current item.
 * @param [out] out receive <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS if item is not
 * contained within the array.
 * @throws SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE if there is no next item.
 */
bool seahorse_array_p_next(const struct seahorse_array_p *object,
                           void **item,
                           void ***out);

/**
 * @brief Retrieve previous item.
 * @param [in] object array instance.
 * @param [in] item <u>address of</u> current item.
 * @param [out] out receive <u>address of</u> the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_P_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_P_ERROR_ITEM_IS_OUT_OF_BOUNDS if item is not
 * contained within the array.
 * @throws SEAHORSE_ARRAY_P_ERROR_END_OF_SEQUENCE if there is no previous item.
 */
bool seahorse_array_p_prev(const struct seahorse_array_p *object,
                           void **item,
                           void ***out);

#endif /* _SEAHORSE_ARRAY_P_H_ */
