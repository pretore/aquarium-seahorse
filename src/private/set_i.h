#ifndef _SEAHORSE_PRIVATE_SET_I_H_
#define _SEAHORSE_PRIVATE_SET_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "collection_i.h"

struct sea_turtle_integer;

struct seahorse_set_i {
    const struct seahorse_collection_i collection_i;

    bool (*const add)(void *object,
                      const struct sea_turtle_integer *value);

    bool (*const remove)(void *object,
                         const struct sea_turtle_integer *value);

    bool (*const contains)(const void *object,
                           const struct sea_turtle_integer *value,
                           bool *out);

    bool (*const get)(const void *object,
                      const struct sea_turtle_integer *value,
                      const struct sea_turtle_integer **out);
};

#endif /* _SEAHORSE_PRIVATE_SET_I_H_ */
