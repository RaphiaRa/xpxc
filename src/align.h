#ifndef XCXP_ALIGN_H
#define XCXP_ALIGN_H

#include <stdint.h>
#include <stddef.h>

#define XCXP_ALIGNOF(type) offsetof(struct { char c; type member; }, member)
#define XCXP_ALIGNAS(align, ptr) ((void*)(((uintptr_t)(ptr) + ((align) - 1)) & ~((align) - 1)))
#define XCXP_ALIGNUP(n, align) (((n) + (align) - 1) & ~((align) - 1))
#define XCXP_ALIGNDOWN(n, align) ((n) & ~((align) - 1))

typedef long double xcxp_max_align;

#endif
