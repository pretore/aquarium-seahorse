#ifndef _SEAHORSE_PRIVATE_STREAM_I_H_
#define _SEAHORSE_PRIVATE_STREAM_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

struct sea_turtle_integer;

struct seahorse_stream_i {
    bool (*const first)(const void *object,
                        const struct sea_turtle_integer **out);

    bool (*const remove_item)(void *object,
                              const struct sea_turtle_integer *item);

    bool (*const next)(const void *object,
                       const struct sea_turtle_integer *item,
                       const struct sea_turtle_integer **out);
};

#endif /* _SEAHORSE_PRIVATE_STREAM_I_H_ */
