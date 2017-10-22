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

int
get_varint32(int32_t *varint, const uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Deserialize a protobuf varint starting from given offset in memory; update
     * offset based on number of bytes consumed.
     */
    int32_t base = 1;
    uint8_t val_byte;

    *varint = 0;
    while (*offset <= max_offset) {
        val_byte = buffer[(*offset)++];
        *varint += (int32_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            return 0;
        }
    }

    return 1;
}

int
get_varint64(int64_t *varint, const uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Deserialize a protobuf varint starting from given offset in memory; update
     * offset based on number of bytes consumed.
     */
    int64_t base = 1;
    uint8_t val_byte;

    *varint = 0;
    while (*offset <= max_offset) {
        val_byte = buffer[(*offset)++];
        *varint += (int64_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            return 0;
        }
    }

    return 1;
}

int
get_signed_varint32(int32_t *varint, const uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Deserialize a signed protobuf varint starting from given offset in memory;
     * update offset based on number of bytes consumed.
     */
    uint32_t base = 1;
    uint8_t val_byte;

    *varint = 0;
    while (*offset <= max_offset) {
        val_byte = buffer[(*offset)++];
        *varint += (uint32_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            /* zigzag decoding */
            *varint = (int32_t)((*varint >> 1) ^ (-(*varint & 1)));
            return 0;
        }
    }

    return 1;
}

int
get_signed_varint64(int64_t *varint, const uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Deserialize a signed protobuf varint starting from given offset in memory;
     * update offset based on number of bytes consumed.
     */
    uint64_t base = 1;
    uint8_t val_byte;

    *varint = 0;
    while (*offset <= max_offset) {
        val_byte = buffer[(*offset)++];
        *varint += (uint64_t)(val_byte & 0x7F) * base;
        if (val_byte & 0x80) {
            base <<= 7;
        } else {
            /* zigzag decoding */
            *varint = (int64_t)((*varint >> 1) ^ (-(*varint & 1)));
            return 0;
        }
    }

    return 1;
}

int
set_varint32(int32_t varint, uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Serialize an integer into a protobuf varint.
     */
    uint32_t enc = (uint32_t)varint;
    uint8_t bits = (uint8_t)(enc & 0x7f);
    enc >>= 7;

    while (enc != 0 && *offset < max_offset) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    if (*offset >= max_offset) {
        return 1;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_varint64(int64_t varint, uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Serialize an integer into a protobuf varint.
     */
    uint64_t enc = (uint64_t)varint;
    uint8_t bits = (uint8_t)(varint & 0x7f);
    enc >>= 7;

    while (enc != 0 && *offset < max_offset) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    if (*offset >= max_offset) {
        return 1;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_signed_varint32(int32_t varint, uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Serialize an integer into a signed protobuf varint.
     */
    uint32_t enc = (varint << 1) ^ (varint >> 31);
    uint8_t bits = enc & 0x7f;
    enc >>= 7;

    while (enc != 0 && *offset < max_offset) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    if (*offset >= max_offset) {
        return 1;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
set_signed_varint64(int64_t varint, uint8_t *buffer, size_t max_offset, size_t *offset)
{
    /*
     * Serialize an integer into a signed protobuf varint.
     */
    uint64_t enc = (varint << 1) ^ (varint >> 63);
    uint8_t bits = enc & 0x7f;
    enc >>= 7;

    while (enc != 0 && *offset < max_offset) {
        buffer[(*offset)++] = (uint8_t)(bits | 0x80);
        bits = enc & 0x7f;
        enc >>= 7;
    }

    if (*offset >= max_offset) {
        return 1;
    }

    buffer[(*offset)++] = (uint8_t)bits;

    return 0;
}

int
skip_generic(const uint8_t *buffer, size_t max_offset, size_t *offset, int wire_type)
{
	int64_t varint;

	switch (wire_type) {
		case 0:
			return get_varint64(&varint, buffer, max_offset, offset);
		case 1:
			*offset += sizeof(uint64_t);
			break;
		case 2:
			get_varint64(&varint, buffer, max_offset, offset);
			*offset += (size_t)varint;
			break;
		case 5:
			*offset += sizeof(uint32_t);
			break;
		default:
			return 1;
	}

	return *offset <= max_offset;
}

