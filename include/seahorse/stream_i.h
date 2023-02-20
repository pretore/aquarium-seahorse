#ifndef _SEAHORSE_STREAM_I_H_
#define _SEAHORSE_STREAM_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <coral.h>

struct sea_turtle_integer;

#define SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL              1
#define SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL                 2
#define SEAHORSE_STREAM_I_ERROR_STREAM_IS_EMPTY             3
#define SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL                4
#define SEAHORSE_STREAM_I_ERROR_END_OF_SEQUENCE             5

struct seahorse_stream_i;

/**
 * @brief First item of the stream.
 * @param [in] object stream instance.
 * @param [out] out receive the <u>address of</u> item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_STREAM_IS_EMPTY if stream is empty.
 */
bool seahorse_stream_i_first(
        const struct seahorse_stream_i *object,
        const struct sea_turtle_integer **out);

/**
 * @brief Remove item.
 * @param [in] object stream instance.
 * @param [in] item <u>address of</u> item to be removed.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 */
bool seahorse_stream_i_remove_item(
        struct seahorse_stream_i *object,
        const struct sea_turtle_integer *item);

/**
 * @brief Retrieve next item.
 * @param [in] object stream instance.
 * @param [in] item current <u>address of</u> item.
 * @param [out] out receive the <u>address of</u> the next item.
 * @return On success true, otherwise false if an error has occurred.
 * @throws SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL if object is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL if item is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAHORSE_STREAM_I_ERROR_END_OF_SEQUENCE if there is no next item.
 */
bool seahorse_stream_i_next(
        const struct seahorse_stream_i *object,
        const struct sea_turtle_integer *item,
        const struct sea_turtle_integer **out);

#endif /* _SEAHORSE_STREAM_I_H_ */
