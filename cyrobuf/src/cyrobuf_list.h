#ifndef CYROBUF_LIST_H
#define CYROBUF_LIST_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cyrobuf_util.h"

struct cyrobuf_string_list {
    char **values;
    size_t len;
    size_t _size;
};

void cyrobuf_string_list_destroy(struct cyrobuf_string_list *list);
void cyrobuf_string_list_copy(struct cyrobuf_string_list *dest, struct cyrobuf_string_list *src);
void cyrobuf_string_list_append(struct cyrobuf_string_list *list, char *item);
void cyrobuf_string_list_extend(struct cyrobuf_string_list *list, struct cyrobuf_string_list *other);
void cyrobuf_string_list_insert(struct cyrobuf_string_list *list, int i, char *item);
char *cyrobuf_string_list_pop(struct cyrobuf_string_list *list);

struct cyrobuf_bytes_list {
    struct cyrobuf_bytes **values;
    size_t len;
    size_t _size;
};

void cyrobuf_bytes_list_destroy(struct cyrobuf_bytes_list *list);
void cyrobuf_bytes_list_copy(struct cyrobuf_bytes_list *dest, struct cyrobuf_bytes_list *src);
void cyrobuf_bytes_list_append(struct cyrobuf_bytes_list *list, struct cyrobuf_bytes *item);
void cyrobuf_bytes_list_extend(struct cyrobuf_bytes_list *list, struct cyrobuf_bytes_list *other);
void cyrobuf_bytes_list_insert(struct cyrobuf_bytes_list *list, int i, struct cyrobuf_bytes *item);
struct cyrobuf_bytes *cyrobuf_bytes_list_pop(struct cyrobuf_bytes_list *list);





struct cyrobuf_uint64_list {
    uint64_t *values;
    size_t len;
    size_t _size;
};

void cyrobuf_uint64_list_destroy(struct cyrobuf_uint64_list *list);
void cyrobuf_uint64_list_copy(struct cyrobuf_uint64_list *dest, struct cyrobuf_uint64_list *src);
void cyrobuf_uint64_list_append(struct cyrobuf_uint64_list *list, uint64_t item);
void cyrobuf_uint64_list_extend(struct cyrobuf_uint64_list *list, struct cyrobuf_uint64_list *other);
void cyrobuf_uint64_list_insert(struct cyrobuf_uint64_list *list, int i, uint64_t item);
uint64_t cyrobuf_uint64_list_pop(struct cyrobuf_uint64_list *list);



struct cyrobuf_double_list {
    double *values;
    size_t len;
    size_t _size;
};

void cyrobuf_double_list_destroy(struct cyrobuf_double_list *list);
void cyrobuf_double_list_copy(struct cyrobuf_double_list *dest, struct cyrobuf_double_list *src);
void cyrobuf_double_list_append(struct cyrobuf_double_list *list, double item);
void cyrobuf_double_list_extend(struct cyrobuf_double_list *list, struct cyrobuf_double_list *other);
void cyrobuf_double_list_insert(struct cyrobuf_double_list *list, int i, double item);
double cyrobuf_double_list_pop(struct cyrobuf_double_list *list);



struct cyrobuf_uint32_list {
    uint32_t *values;
    size_t len;
    size_t _size;
};

void cyrobuf_uint32_list_destroy(struct cyrobuf_uint32_list *list);
void cyrobuf_uint32_list_copy(struct cyrobuf_uint32_list *dest, struct cyrobuf_uint32_list *src);
void cyrobuf_uint32_list_append(struct cyrobuf_uint32_list *list, uint32_t item);
void cyrobuf_uint32_list_extend(struct cyrobuf_uint32_list *list, struct cyrobuf_uint32_list *other);
void cyrobuf_uint32_list_insert(struct cyrobuf_uint32_list *list, int i, uint32_t item);
uint32_t cyrobuf_uint32_list_pop(struct cyrobuf_uint32_list *list);



struct cyrobuf_int_list {
    int *values;
    size_t len;
    size_t _size;
};

void cyrobuf_int_list_destroy(struct cyrobuf_int_list *list);
void cyrobuf_int_list_copy(struct cyrobuf_int_list *dest, struct cyrobuf_int_list *src);
void cyrobuf_int_list_append(struct cyrobuf_int_list *list, int item);
void cyrobuf_int_list_extend(struct cyrobuf_int_list *list, struct cyrobuf_int_list *other);
void cyrobuf_int_list_insert(struct cyrobuf_int_list *list, int i, int item);
int cyrobuf_int_list_pop(struct cyrobuf_int_list *list);



struct cyrobuf_int32_list {
    int32_t *values;
    size_t len;
    size_t _size;
};

void cyrobuf_int32_list_destroy(struct cyrobuf_int32_list *list);
void cyrobuf_int32_list_copy(struct cyrobuf_int32_list *dest, struct cyrobuf_int32_list *src);
void cyrobuf_int32_list_append(struct cyrobuf_int32_list *list, int32_t item);
void cyrobuf_int32_list_extend(struct cyrobuf_int32_list *list, struct cyrobuf_int32_list *other);
void cyrobuf_int32_list_insert(struct cyrobuf_int32_list *list, int i, int32_t item);
int32_t cyrobuf_int32_list_pop(struct cyrobuf_int32_list *list);



struct cyrobuf_float_list {
    float *values;
    size_t len;
    size_t _size;
};

void cyrobuf_float_list_destroy(struct cyrobuf_float_list *list);
void cyrobuf_float_list_copy(struct cyrobuf_float_list *dest, struct cyrobuf_float_list *src);
void cyrobuf_float_list_append(struct cyrobuf_float_list *list, float item);
void cyrobuf_float_list_extend(struct cyrobuf_float_list *list, struct cyrobuf_float_list *other);
void cyrobuf_float_list_insert(struct cyrobuf_float_list *list, int i, float item);
float cyrobuf_float_list_pop(struct cyrobuf_float_list *list);



struct cyrobuf_int64_list {
    int64_t *values;
    size_t len;
    size_t _size;
};

void cyrobuf_int64_list_destroy(struct cyrobuf_int64_list *list);
void cyrobuf_int64_list_copy(struct cyrobuf_int64_list *dest, struct cyrobuf_int64_list *src);
void cyrobuf_int64_list_append(struct cyrobuf_int64_list *list, int64_t item);
void cyrobuf_int64_list_extend(struct cyrobuf_int64_list *list, struct cyrobuf_int64_list *other);
void cyrobuf_int64_list_insert(struct cyrobuf_int64_list *list, int i, int64_t item);
int64_t cyrobuf_int64_list_pop(struct cyrobuf_int64_list *list);



#endif
