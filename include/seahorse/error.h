#ifndef _SEAHORSE_ERROR_H_
#define _SEAHORSE_ERROR_H_

#include <stddef.h>
#include <stdint.h>

#define SEAHORSE_ERROR_NONE                                         0

extern _Thread_local uintmax_t seahorse_error;

#endif /* _SEAHORSE_ERROR_H_ */
