#include <stdlib.h>
#include <seahorse.h>

#include "private/collection_i.h"

#ifdef TEST
#include <test/cmocka.h>
#endif

#define INVOKABLE   (*(struct seahorse_collection_i **) object)

#pragma mark stream_i -

bool seahorse_collection_i_first(
        const struct seahorse_collection_i *const object,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->stream_i
            .first(object, out);
}

bool seahorse_collection_i_remove_item(
        struct seahorse_collection_i *const object,
        const struct sea_turtle_integer *const item) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    return INVOKABLE->stream_i
            .remove_item(object, item);
}

bool seahorse_collection_i_next(
        const struct seahorse_collection_i *const object,
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->stream_i
            .next(object, item, out);
}

#pragma mark collection_i -

bool seahorse_collection_i_count(
        const struct seahorse_collection_i *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->count(object, out);
}

bool seahorse_collection_i_last(
        const struct seahorse_collection_i *const object,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->last(object, out);
}

bool seahorse_collection_i_prev(
        const struct seahorse_collection_i *const object,
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_COLLECTION_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->prev(object, item, out);
}
