#ifndef CYROBUF_UTIL_H
#define CYROBUF_UTIL_H

#include <stdint.h>
#include <stdlib.h>

struct cyrobuf_bytes {
    size_t len;
    uint8_t data[];
};

int32_t get_varint32(const uint8_t *buffer, size_t *offset);
int64_t get_varint64(const uint8_t *buffer, size_t *offset);
int32_t get_signed_varint32(const uint8_t *buffer, size_t *offset);
int64_t get_signed_varint64(const uint8_t *buffer, size_t *offset);
int set_varint32(int32_t varint, uint8_t *buffer, size_t *offset);
int set_varint64(int64_t varint, uint8_t *buffer, size_t *offset);
int set_signed_varint32(int32_t varint, uint8_t *buffer, size_t *offset);
int set_signed_varint64(int32_t varint, uint8_t *buffer, size_t *offset);

#endif

