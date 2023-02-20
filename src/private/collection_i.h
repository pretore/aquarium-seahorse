#ifndef _SEAHORSE_PRIVATE_COLLECTION_I_H_
#define _SEAHORSE_PRIVATE_COLLECTION_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "stream_i.h"

struct sea_turtle_integer;

struct seahorse_collection_i {
    const struct seahorse_stream_i stream_i;

    bool (*const count)(const void *object,
                        uintmax_t *out);

    bool (*const last)(const void *object,
                       const struct sea_turtle_integer **out);

    bool (*const prev)(const void *object,
                       const struct sea_turtle_integer *item,
                       const struct sea_turtle_integer **out);
};

#endif /* _SEAHORSE_PRIVATE_COLLECTION_I_H_ */
