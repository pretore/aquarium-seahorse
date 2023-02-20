#include <stdlib.h>
#include <sea-turtle.h>
#include <seahorse.h>

#include "private/stream_i.h"

#ifdef TEST
#include <test/cmocka.h>
#endif

#define INVOKABLE   (*(struct seahorse_stream_i **) object)

#pragma mark stream_i -

bool seahorse_stream_i_first(
        const struct seahorse_stream_i *const object,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->first(object, out);
}

bool seahorse_stream_i_remove_item(
        struct seahorse_stream_i *const object,
        const struct sea_turtle_integer *const item) {
    if (!object) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    return INVOKABLE->remove_item(object, item);
}

bool seahorse_stream_i_next(
        const struct seahorse_stream_i *const object,
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_STREAM_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->next(object, item, out);
}
