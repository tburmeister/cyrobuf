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

