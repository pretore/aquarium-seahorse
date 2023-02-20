#ifndef _SEAHORSE_PRIVATE_ORDERED_SET_I_H_
#define _SEAHORSE_PRIVATE_ORDERED_SET_I_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "set_i.h"

struct sea_turtle_integer;

struct seahorse_ordered_set_i {
    const struct seahorse_set_i set_i;
};

#endif /* _SEAHORSE_PRIVATE_ORDERED_SET_I_H_ */
