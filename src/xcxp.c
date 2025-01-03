#include <xcxp.h>

#include "align.h"
#include "bytes.h"
#include "utility.h"

#define XCXP_BASE_OFFSET (size_t)8
#define XCXP_SIZE_OFFSET XCXP_BASE_OFFSET
#define XCXP_TAIL_OFFSET (XCXP_BASE_OFFSET + sizeof(size_t))
#define XCXP_HEAD_OFFSET (XCXP_TAIL_OFFSET + sizeof(size_t))
#define XCXP_MASK_OFFSET (XCXP_HEAD_OFFSET + sizeof(size_t))
#define XCXP_DATA_OFFSET (XCXP_MASK_OFFSET + sizeof(size_t))
#define XCXP_HEADER_SIZE (XCXP_DATA_OFFSET)
#define XCXP_DATA_SIZE(x) (x - XCXP_HEADER_SIZE)
#define XCXP_OFFSET(x, off) ((void*)((uint8_t*)(x) + (off)))

/*Memory layout:
 header: 16 bytes
 cc: 4 bytes
 type: 1 byte
 padding: 3 bytes
 size: sizeof(size_t) bytes
 tail: sizeof(size_t) bytes
 head: sizeof(size_t) bytes
 mask: sizeof(size_t) bytes
 data: size bytes
 */
XCXP_PUBLIC(xcxp_Err)
xcxp_setup_memory(xcxp_Type type, void* data, size_t size)
{
    XCXP_REQUIRE(data, XCXP_ERR_INVALID_ARG);
    XCXP_REQUIRE(XCXP_DATA_SIZE(size) > 128, XCXP_ERR_INVALID_ARG);
    XCXP_REQUIRE(XCXP_ALIGNAS(XCXP_ALIGNOF(xcxp_max_align), data) == data, XCXP_ERR_INVALID_ARG);
    uint32_t cc = 0x11a1992a; // magic number
    cc |= type;
    cc |= (uint32_t)size << 4;
    size_t data_size = xcxp_pow2_floor(XCXP_DATA_SIZE(size));
    uint32_t cur_cc = XCXP_BYTES_READU32(data);
    if (cur_cc == cc) {
        return XCXP_ERR_NONE;
    }
    XCXP_BYTES_WRITEU32(data, cc);
    XCXP_BYTES_WRITEU8(XCXP_OFFSET(data, XCXP_SIZE_OFFSET), (uint8_t)type);
    XCXP_BYTES_WRITEU32(XCXP_OFFSET(data, XCXP_SIZE_OFFSET), data_size);
    XCXP_BYTES_WRITEU32(XCXP_OFFSET(data, XCXP_TAIL_OFFSET), 0);
    XCXP_BYTES_WRITEU32(XCXP_OFFSET(data, XCXP_HEAD_OFFSET), 0);
    XCXP_BYTES_WRITEU32(XCXP_OFFSET(data, XCXP_MASK_OFFSET), data_size - 1);
    return XCXP_ERR_NONE;
}

XCXP_PUBLIC(size_t)
xcxp_get_memory_size(size_t size)
{
    if (size < 128) {
        size = 128;
    }
    return XCXP_HEADER_SIZE + xcxp_pow2_ceil(size);
}
