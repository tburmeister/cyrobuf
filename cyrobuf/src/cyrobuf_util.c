#include <string.h>

#include "cyrobuf_util.h"

void
cyrobuf_bytes_destroy(struct cyrobuf_bytes *bytes)
{
    free(bytes);
}

struct cyrobuf_bytes *
cyrobuf_bytes_copy(struct cyrobuf_bytes *bytes)
{
    size_t data_size = sizeof(struct cyrobuf_bytes) + bytes->len * sizeof(uint8_t);

    struct cyrobuf_bytes *out = malloc(data_size);
    memcpy(out->data, bytes->data, data_size);

    return out;
}

int32_t
get_varint32(const uint8_t *buffer, size_t *offset)
{
    /*
     * Deserialize a protobuf varint starting from given offset in memory; update
     * offset based on number of bytes consumed.
     */
    int32_t value = 0;
    int32_t base = 1;
    uint8_t val_byte;

    for (;;) {
        val_byte = buffer[(*offset)++];
        value += (int32_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            return value;
        }
    }
}

int64_t
get_varint64(const uint8_t *buffer, size_t *offset)
{
    /*
     * Deserialize a protobuf varint starting from given offset in memory; update
     * offset based on number of bytes consumed.
     */
    int64_t value = 0;
    int64_t base = 1;
    uint8_t val_byte;

    for (;;) {
        val_byte = buffer[(*offset)++];
        value += (int64_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            return value;
        }
    }
}

int32_t
get_signed_varint32(const uint8_t *buffer, size_t *offset)
{
    /*
     * Deserialize a signed protobuf varint starting from given offset in memory;
     * update offset based on number of bytes consumed.
     */
    uint32_t value = 0;
    uint32_t base = 1;
    uint8_t val_byte;

    for (;;) {
        val_byte = buffer[(*offset)++];
        value += (uint32_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            /* zigzag decoding */
            return (int32_t)((value >> 1) ^ (-(value & 1)));
        }
    }
}

int64_t
get_signed_varint64(const uint8_t *buffer, size_t *offset)
{
    /*
     * Deserialize a signed protobuf varint starting from given offset in memory;
     * update offset based on number of bytes consumed.
     */
    uint64_t value = 0;
    uint64_t base = 1;
    uint8_t val_byte;

    for (;;) {
        val_byte = buffer[(*offset)++];
        value += (uint64_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            /* zigzag decoding */
            return (int64_t)((value >> 1) ^ (-(value & 1)));
        }
    }
}

int
set_varint32(int32_t varint, uint8_t *buffer, size_t *offset)
{
    /*
     * Serialize an integer into a protobuf varint.
     */
    uint8_t bits = (uint8_t)(varint & 0x7f);
    varint >>= 7;

    while (varint != 0) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = varint & 0x7f;
        varint >>= 7;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_varint64(int64_t varint, uint8_t *buffer, size_t *offset)
{
    /*
     * Serialize an integer into a protobuf varint.
     */
    uint8_t bits = (uint8_t)(varint & 0x7f);
    varint >>= 7;

    while (varint != 0) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = varint & 0x7f;
        varint >>= 7;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_signed_varint32(int32_t varint, uint8_t *buffer, size_t *offset)
{
    /*
     * Serialize an integer into a signed protobuf varint.
     */
    uint32_t enc = (varint << 1) ^ (varint >> 31);
    uint8_t bits = enc & 0x7f;
    enc >>= 7;

    while (enc != 0) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_signed_varint64(int64_t varint, uint8_t *buffer, size_t *offset)
{
    /*
     * Serialize an integer into a signed protobuf varint.
     */
    uint64_t enc = (varint << 1) ^ (varint >> 63);
    uint8_t bits = enc & 0x7f;
    enc >>= 7;

    while (enc != 0) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

