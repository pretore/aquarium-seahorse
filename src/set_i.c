#include <stdlib.h>
#include <seahorse.h>

#include "private/set_i.h"

#ifdef TEST
#include <test/cmocka.h>
#endif

#define INVOKABLE   (*(struct seahorse_set_i **) object)

#pragma mark stream_i -

bool seahorse_set_i_first(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .stream_i
            .first(object, out);
}

bool seahorse_set_i_remove_item(
        struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const item) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_SET_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .stream_i
            .remove_item(object, item);
}

bool seahorse_set_i_next(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_SET_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .stream_i
            .next(object, item, out);
}

#pragma mark collection_i -

bool seahorse_set_i_count(
        const struct seahorse_set_i *const object,
        uintmax_t *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .count(object, out);
}

bool seahorse_set_i_last(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .last(object, out);
}

bool seahorse_set_i_prev(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const item,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!item) {
        seahorse_error = SEAHORSE_SET_I_ERROR_ITEM_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->collection_i
            .prev(object, item, out);
}

#pragma mark set_i -

bool seahorse_set_i_add(
        struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    return INVOKABLE->add(object, value);
}

bool seahorse_set_i_remove(
        struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const value) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    return INVOKABLE->remove(object, value);
}

bool seahorse_set_i_contains(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const value,
        bool *const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->contains(object, value, out);
}

bool seahorse_set_i_get(
        const struct seahorse_set_i *const object,
        const struct sea_turtle_integer *const value,
        const struct sea_turtle_integer **const out) {
    if (!object) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OBJECT_IS_NULL;
        return false;
    }
    if (!value) {
        seahorse_error = SEAHORSE_SET_I_ERROR_VALUE_IS_NULL;
        return false;
    }
    if (!out) {
        seahorse_error = SEAHORSE_SET_I_ERROR_OUT_IS_NULL;
        return false;
    }
    return INVOKABLE->get(object, value, out);
}
