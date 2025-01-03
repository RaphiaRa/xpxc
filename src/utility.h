#ifndef XCXP_UTILITY_H
#define XCXP_UTILITY_H

#include <xcxp.h>

#define XCXP_REQUIRE(x, err) \
    if (!(x))                \
    return err

#ifndef NDEBUG
#define XCXP_ASSERT(cond, msg) \
    assert((cond) && msg)
#else
#define XCXP_ASSERT(cond, msg) \
    do {                       \
        (void)sizeof(cond);    \
        (void)sizeof(msg);     \
    } while (0)
#endif

/// @brief Returns the smallest power of 2 greater than or equal to n.
/// Taken from https://stackoverflow.com/questions/2679815/previous-power-of-2
XCXP_INLINE(size_t)
xcxp_pow2_floor(size_t n)
{
    XCXP_ASSERT(n > 0, "n must be greater than 0");
    n = n | (n >> 1);
    n = n | (n >> 2);
    n = n | (n >> 4);
    n = n | (n >> 8);
    n = n | (n >> 16);
    return n - (n >> 1);
}

XCXP_INLINE(size_t)
xcxp_pow2_ceil(size_t n)
{
    XCXP_ASSERT(n > 0, "n must be greater than 0");
    return xcxp_pow2_floor(n - 1) << 1;
}

#endif
