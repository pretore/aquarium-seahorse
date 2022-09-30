#ifndef _SEAHORSE_ARRAY_NI_H_
#define _SEAHORSE_ARRAY_NI_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <rock.h>

#define SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL                      1
#define SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED            2
#define SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL                         3
#define SEAHORSE_ARRAY_NI_ERROR_COUNT_IS_ZERO                       4
#define SEAHORSE_ARRAY_NI_ERROR_VALUES_IS_NULL                      5
#define SEAHORSE_ARRAY_NI_ERROR_ARRAY_IS_EMPTY                      6
#define SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS              7
#define SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_NULL                        8
#define SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_OUT_OF_BOUNDS               9
#define SEAHORSE_ARRAY_NI_ERROR_END_OF_SEQUENCE                     10

struct seahorse_array_ni {
    struct rock_array array;
};

/**
 * @brief Initialise array.
 * @param [in] object instance to be initialised.
 * @param [in] capacity set the initial capacity.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is
 * insufficient memory to initialize the array instance.
 */
bool seahorse_array_ni_init(struct seahorse_array_ni *object,
                            uintmax_t capacity);

/**
 * @brief Invalidate the array.
 * <p>The actual <u>array instance is not deallocated</u> since it may have
 * been embedded in a larger structure.</p>
 * @param [in] object instance to be invalidated.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool seahorse_array_ni_invalidate(struct seahorse_array_ni *object);

/**
 * @brief Retrieve the capacity.
 * @param [in] object array instance.
 * @param [in] out receive the capacity.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_array_ni_capacity(const struct seahorse_array_ni *object,
                                uintmax_t *out);

/**
 * @brief Retrieve the length.
 * @param [in] object array instance.
 * @param [in] out receive the number of items.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_array_ni_get_length(const struct seahorse_array_ni *object,
                                  uintmax_t *out);

/**
 * @brief Set the length.
 * @param [in] object array instance.
 * @param [in] length number of items in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to set the array length.
 */
bool seahorse_array_ni_set_length(struct seahorse_array_ni *object,
                                  uintmax_t length);

/**
 * @brief Release excess capacity.
 * @param [in] object array instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 */
bool seahorse_array_ni_shrink(struct seahorse_array_ni *object);

/**
 * @brief Add an item at the end.
 * @param [in] object array instance.
 * @param [in] value to add at the end of the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to add another value.
 */
bool seahorse_array_ni_add(struct seahorse_array_ni *object, uintmax_t value);

/**
 * @brief Add all the items at the end.
 * @param [in] object array instance.
 * @param [in] count number of values.
 * @param [in] values all of which we would like to add to the end of the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_NI_ERROR_VALUES_IS_NULL is values is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to all the values.
 */
bool seahorse_array_ni_add_all(struct seahorse_array_ni *object,
                               uintmax_t count,
                               const uintmax_t *values);

/**
 * @brief Remove last item.
 * @param [in] object array instance.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_ni_remove_last(struct seahorse_array_ni *object);

/**
 * @brief Insert an value at index.
 * @param [in] object array instance.
 * @param [in] at index where item is to be inserted.
 * @param [in] value to be inserted.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to insert value.
 */
bool seahorse_array_ni_insert(struct seahorse_array_ni *object,
                              uintmax_t at,
                              uintmax_t value);

/**
 * @brief Insert all the values at index.
 * @param [in] object array instance.
 * @param [in] at index where items are to be inserted.
 * @param [in] count number of values.
 * @param [in] values all of which we would like to insert into the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 * @throws SEAHORSE_ARRAY_NI_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_NI_ERROR_VALUES_IS_NULL if values is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_MEMORY_ALLOCATION_FAILED if there is not
 * enough memory to insert all the values into the array.
 */
bool seahorse_array_ni_insert_all(struct seahorse_array_ni *object,
                                  uintmax_t at,
                                  uintmax_t count,
                                  const uintmax_t *values);

/**
 * @brief Remove an item at the given index.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_ni_remove(struct seahorse_array_ni *object, uintmax_t at);

/**
 * @brief Remove all the items from the given index up to count items.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @param [in] count of items to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_COUNT_IS_ZERO if count is zero.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_ni_remove_all(struct seahorse_array_ni *object,
                                  uintmax_t at,
                                  uintmax_t count);

/**
 * @brief Retrieve the value at the given index.
 * @param [in] object array instance.
 * @param [in] at index of item.
 * @param [out] out receive the value.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_ni_get(const struct seahorse_array_ni *object,
                           uintmax_t at,
                           uintmax_t *out);

/**
 * @brief Set the value at the given index.
 * @param [in] object array instance.
 * @param [in] at index where value should be stored.
 * @param [in] value to set at index.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_INDEX_IS_OUT_OF_BOUNDS if at does not refer
 * to an item contained within the array.
 */
bool seahorse_array_ni_set(struct seahorse_array_ni *object,
                           uintmax_t at,
                           uintmax_t value);

/**
 * @brief First item of the array.
 * @param [in] object array instance.
 * @param [out] out receive first item in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_ni_first(const struct seahorse_array_ni *object,
                             uintmax_t **out);

/**
 * @brief Last item of the array.
 * @param [in] object array instance.
 * @param [out] out receive last item in the array.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ARRAY_IS_EMPTY if the array is empty.
 */
bool seahorse_array_ni_last(const struct seahorse_array_ni *object,
                            uintmax_t **out);

/**
 * @brief Retrieve next item.
 * @param [in] object array instance.
 * @param [in] item current item.
 * @param [out] out receive the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_OUT_OF_BOUNDS if item is not
 * contained within the array.
 * @throws SEAHORSE_ARRAY_NI_ERROR_END_OF_SEQUENCE if there is no next item.
 */
bool seahorse_array_ni_next(const struct seahorse_array_ni *object,
                            const uintmax_t *item,
                            uintmax_t **out);

/**
 * @brief Retrieve previous item.
 * @param [in] object array instance.
 * @param [in] item current item.
 * @param [out] out receive the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_ARRAY_NI_ERROR_ITEM_IS_OUT_OF_BOUNDS if item is not
 * contained within the array.
 * @throws SEAHORSE_ARRAY_NI_ERROR_END_OF_SEQUENCE if there is no previous item.
 */
bool seahorse_array_ni_prev(const struct seahorse_array_ni *object,
                            const uintmax_t *item,
                            uintmax_t **out);

#endif /* _SEAHORSE_ARRAY_NI_H_ */
