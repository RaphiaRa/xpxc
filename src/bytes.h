#ifndef XCXP_BYTES_H
#define XCXP_BYTES_H

#define XCXP_BYTES_READU8(data) ((uint8_t)((uint8_t*)(data))[0])

#define XCXP_BYTES_READU16(data) (((uint16_t)((uint8_t*)(data))[0]) << 8 | ((uint16_t)((uint8_t*)(data))[1]))

#define XCXP_BYTES_READU32(data) (((uint32_t)((uint8_t*)(data))[0]) << 24 | ((uint32_t)((uint8_t*)(data))[1]) << 16 | ((uint32_t)((uint8_t*)(data))[2]) << 8 | ((uint32_t)((uint8_t*)(data))[3]))

#define XCXP_BYTES_WRITEU8(data, value) ((uint8_t*)(data))[0] = (value)

#define XCXP_BYTES_WRITEU16(data, value)      \
    do {                                      \
        ((uint8_t*)(data))[0] = (value) >> 8; \
        ((uint8_t*)(data))[1] = (value);      \
    } while (0)

#define XCXP_BYTES_WRITEU32(data, value)       \
    do {                                       \
        ((uint8_t*)(data))[0] = (value) >> 24; \
        ((uint8_t*)(data))[1] = (value) >> 16; \
        ((uint8_t*)(data))[2] = (value) >> 8;  \
        ((uint8_t*)(data))[3] = (value);       \
    } while (0)

#endif
