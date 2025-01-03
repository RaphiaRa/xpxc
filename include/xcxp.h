#ifndef XCXP_H
#define XCXP_H

#include <assert.h>
#include <stdlib.h>

#define XCXP_INLINE(x) static inline x

#if XCXP_AMALGAMATED
#define XCXP_PRIVATE(x) static x
#else
#define XCXP_PRIVATE(x) x
#endif

#define XCXP_PUBLIC(x) x

typedef enum xcxp_Err {
    XCXP_ERR_NONE,
    XCXP_ERR_INVALID_ARG,
} xcxp_Err;

XCXP_PUBLIC(const char*)
xcxp_Err_str(xcxp_Err err);

typedef enum xcxp_Type {
    XCXP_TYPE_SCMP,
    XCXP_TYPE_SCMP_MT,
} xcxp_Type;

XCXP_PUBLIC(xcxp_Err)
xcxp_setup_memory(xcxp_Type type, void* data, size_t size);

XCXP_PUBLIC(size_t)
xcxp_get_memory_size(size_t size);

typedef struct xcxp_Consumer xcxp_Consumer;

XCXP_PUBLIC(xcxp_Err)
xcxp_Consumer_create(xcxp_Consumer** cons, void* data, size_t size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Conumer_read(xcxp_Consumer* cons, void* data, size_t* size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Consumer_peek(xcxp_Consumer* cons, void* data, size_t* size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Consumer_discard(xcxp_Consumer* cons, size_t size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Consumer_destroy(xcxp_Consumer* cons);

typedef struct xcxp_Producer xcxp_Producer;

XCXP_PUBLIC(xcxp_Err)
xcxp_Producer_create(xcxp_Producer** prod, void* data, size_t size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Producer_write(xcxp_Producer* prod, void* data, size_t size);

XCXP_PUBLIC(xcxp_Err)
xcxp_Producer_destroy(xcxp_Producer* prod);

#endif
