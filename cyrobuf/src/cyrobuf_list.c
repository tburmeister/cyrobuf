#include "cyrobuf_list.h"

void
cyrobuf_string_list_destroy(struct cyrobuf_string_list *list)
{
    /* free elements of list but not the list itself */
    for (size_t i = 0; i < list->len; i++) {
        free(list->values[i]);
    }

    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_string_list_copy(struct cyrobuf_string_list *dest, struct cyrobuf_string_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(char *));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = strdup(src->values[i]);
    }
}

void
cyrobuf_string_list_append(struct cyrobuf_string_list *list, char *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(char *));
    }

    list->values[list->len++] = strdup(item);
}

void
cyrobuf_string_list_append_unsafe(struct cyrobuf_string_list *list, char *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(char *));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_string_list_extend(struct cyrobuf_string_list *list, struct cyrobuf_string_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(char *));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = strdup(other->values[i]);
    }
}

void
cyrobuf_string_list_insert(struct cyrobuf_string_list *list, int i, char *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(char *));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = strdup(item);
    list->len++;
}

char *
cyrobuf_string_list_pop(struct cyrobuf_string_list *list)
{
    return list->values[--list->len];
}

void
cyrobuf_bytes_list_destroy(struct cyrobuf_bytes_list *list)
{
    /* free elements of list but not the list itself */
    for (size_t i = 0; i < list->len; i++) {
        cyrobuf_bytes_destroy(list->values[i]);
    }

    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_bytes_list_copy(struct cyrobuf_bytes_list *dest, struct cyrobuf_bytes_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(struct cyrobuf_bytes *));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = cyrobuf_bytes_copy(src->values[i]);
    }
}

void
cyrobuf_bytes_list_append(struct cyrobuf_bytes_list *list, struct cyrobuf_bytes *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(struct cyrobuf_bytes *));
    }

    list->values[list->len++] = cyrobuf_bytes_copy(item);
}

void
cyrobuf_bytes_list_append_unsafe(struct cyrobuf_bytes_list *list, struct cyrobuf_bytes *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(struct cyrobuf_bytes *));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_bytes_list_extend(struct cyrobuf_bytes_list *list, struct cyrobuf_bytes_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(struct cyrobuf_bytes *));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = cyrobuf_bytes_copy(other->values[i]);
    }
}

void
cyrobuf_bytes_list_insert(struct cyrobuf_bytes_list *list, int i, struct cyrobuf_bytes *item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(struct cyrobuf_bytes *));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = cyrobuf_bytes_copy(item);
    list->len++;
}

struct cyrobuf_bytes *
cyrobuf_bytes_list_pop(struct cyrobuf_bytes_list *list)
{
    return list->values[--list->len];
}





void
cyrobuf_uint64_list_destroy(struct cyrobuf_uint64_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_uint64_list_copy(struct cyrobuf_uint64_list *dest, struct cyrobuf_uint64_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(uint64_t));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_uint64_list_append(struct cyrobuf_uint64_list *list, uint64_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(uint64_t));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_uint64_list_extend(struct cyrobuf_uint64_list *list, struct cyrobuf_uint64_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(uint64_t));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_uint64_list_insert(struct cyrobuf_uint64_list *list, int i, uint64_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(uint64_t));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

uint64_t
cyrobuf_uint64_list_pop(struct cyrobuf_uint64_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_double_list_destroy(struct cyrobuf_double_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_double_list_copy(struct cyrobuf_double_list *dest, struct cyrobuf_double_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(double));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_double_list_append(struct cyrobuf_double_list *list, double item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(double));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_double_list_extend(struct cyrobuf_double_list *list, struct cyrobuf_double_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(double));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_double_list_insert(struct cyrobuf_double_list *list, int i, double item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(double));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

double
cyrobuf_double_list_pop(struct cyrobuf_double_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_uint32_list_destroy(struct cyrobuf_uint32_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_uint32_list_copy(struct cyrobuf_uint32_list *dest, struct cyrobuf_uint32_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(uint32_t));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_uint32_list_append(struct cyrobuf_uint32_list *list, uint32_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(uint32_t));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_uint32_list_extend(struct cyrobuf_uint32_list *list, struct cyrobuf_uint32_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(uint32_t));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_uint32_list_insert(struct cyrobuf_uint32_list *list, int i, uint32_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(uint32_t));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

uint32_t
cyrobuf_uint32_list_pop(struct cyrobuf_uint32_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_int_list_destroy(struct cyrobuf_int_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_int_list_copy(struct cyrobuf_int_list *dest, struct cyrobuf_int_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(int));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_int_list_append(struct cyrobuf_int_list *list, int item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_int_list_extend(struct cyrobuf_int_list *list, struct cyrobuf_int_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(int));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_int_list_insert(struct cyrobuf_int_list *list, int i, int item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

int
cyrobuf_int_list_pop(struct cyrobuf_int_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_int32_list_destroy(struct cyrobuf_int32_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_int32_list_copy(struct cyrobuf_int32_list *dest, struct cyrobuf_int32_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(int32_t));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_int32_list_append(struct cyrobuf_int32_list *list, int32_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int32_t));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_int32_list_extend(struct cyrobuf_int32_list *list, struct cyrobuf_int32_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(int32_t));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_int32_list_insert(struct cyrobuf_int32_list *list, int i, int32_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int32_t));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

int32_t
cyrobuf_int32_list_pop(struct cyrobuf_int32_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_float_list_destroy(struct cyrobuf_float_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_float_list_copy(struct cyrobuf_float_list *dest, struct cyrobuf_float_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(float));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_float_list_append(struct cyrobuf_float_list *list, float item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(float));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_float_list_extend(struct cyrobuf_float_list *list, struct cyrobuf_float_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(float));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_float_list_insert(struct cyrobuf_float_list *list, int i, float item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(float));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

float
cyrobuf_float_list_pop(struct cyrobuf_float_list *list)
{
    return list->values[--list->len];
}



void
cyrobuf_int64_list_destroy(struct cyrobuf_int64_list *list)
{
    free(list->values);

    list->len = 0;
    list->_size = 0;
}

void
cyrobuf_int64_list_copy(struct cyrobuf_int64_list *dest, struct cyrobuf_int64_list *src)
{
    dest->values = realloc(dest->values, src->len * sizeof(int64_t));
    dest->len = dest->_size = src->len;

    for (size_t i = 0; i < src->len; i++) {
        dest->values[i] = src->values[i];
    }
}

void
cyrobuf_int64_list_append(struct cyrobuf_int64_list *list, int64_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int64_t));
    }

    list->values[list->len++] = item;
}

void
cyrobuf_int64_list_extend(struct cyrobuf_int64_list *list, struct cyrobuf_int64_list *other)
{
    if (list->_size < list->len + other->len) {
        list->_size = list->len + other->len;
        list->values = realloc(list->values, list->_size * sizeof(int64_t));
    }

    for (size_t i = 0; i < other->len; i++) {
        list->values[list->len++] = other->values[i];
    }
}

void
cyrobuf_int64_list_insert(struct cyrobuf_int64_list *list, int i, int64_t item)
{
    if (list->_size <= list->len) {
        list->_size = list->_size > 0 ? list->_size << 1 : 4;
        list->values = realloc(list->values, list->_size * sizeof(int64_t));
    }

    for (size_t j = list->len; j > i; j--) {
        list->values[j] = list->values[j - 1];
    }

    list->values[i] = item;
    list->len++;
}

int64_t
cyrobuf_int64_list_pop(struct cyrobuf_int64_list *list)
{
    return list->values[--list->len];
}


