#ifndef _SEAHORSE_COLLECTION_I_H_
#define _SEAHORSE_COLLECTION_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

#include "stream_i.h"

struct sea_turtle_integer;

#define SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL \
    SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL
#define SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL \
    SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL
#define SEAHORSE_COLLECTION_I_ERROR_COLLECTION_IS_EMPTY \
    SEAHORSE_STREAM_I_ERROR_STREAM_IS_EMPTY
#define SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL \
    SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL
#define SEAHORSE_COLLECTION_I_ERROR_END_OF_SEQUENCE \
    SEAHORSE_STREAM_I_ERROR_END_OF_SEQUENCE

struct seahorse_collection_i;

/**
 * @brief Retrieve the count of items.
 * @param [in] object instance whose count we are to retrieve.
 * @param [out] out receive the count.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seahorse_collection_i_count(
        const struct seahorse_collection_i *object,
        uintmax_t *out);

/**
 * @brief First item of the collection.
 * @param [in] object collection instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_COLLECTION_IS_EMPTY if collection is
 * empty.
 */
bool seahorse_collection_i_first(
        const struct seahorse_collection_i *object,
        const struct sea_turtle_integer **out);

/**
 * @brief Last item of the collection.
 * @param [in] object collection instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_COLLECTION_IS_EMPTY if collection is
 * empty.
 */
bool seahorse_collection_i_last(
        const struct seahorse_collection_i *object,
        const struct sea_turtle_integer **out);

/**
 * @brief Remove item.
 * @param [in] object collection instance.
 * @param [in] item <u>address of</u> item to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 */
bool seahorse_collection_i_remove_item(
        struct seahorse_collection_i *object,
        const struct sea_turtle_integer *item);

/**
 * @brief Retrieve next item.
 * @param [in] object collection instance.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_END_OF_SEQUENCE if there is no next item.
 */
bool seahorse_collection_i_next(
        const struct seahorse_collection_i *object,
        const struct sea_turtle_integer *item,
        const struct sea_turtle_integer **out);

/**
 * @brief Retrieve the previous item.
 * @param [in] object collection instance.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the previous item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_COLLECTION_I_ERROR_END_OF_SEQUENCE if there is no
 * previous item.
 */
bool seahorse_collection_i_prev(
        const struct seahorse_collection_i *object,
        const struct sea_turtle_integer *item,
        const struct sea_turtle_integer **out);

#endif /* _SEAHORSE_COLLECTION_I_H_ */
