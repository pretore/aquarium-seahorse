#ifndef _SEAHORSE_PRIVATE_SORTED_SET_I_H_
#define _SEAHORSE_PRIVATE_SORTED_SET_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "ordered_set_i.h"

struct sea_turtle_integer;

struct seahorse_sorted_set_i {
    const struct seahorse_ordered_set_i ordered_set_i;

    bool (*const ceiling)(const void *object,
                          const struct sea_turtle_integer *value,
                          const struct sea_turtle_integer **out);

    bool (*const floor)(const void *object,
                        const struct sea_turtle_integer *value,
                        const struct sea_turtle_integer **out);

    bool (*const higher)(const void *object,
                         const struct sea_turtle_integer *value,
                         const struct sea_turtle_integer **out);

    bool (*const lower)(const void *object,
                        const struct sea_turtle_integer *value,
                        const struct sea_turtle_integer **out);
};

#endif /* _SEAHORSE_PRIVATE_SORTED_SET_I_H_ */
