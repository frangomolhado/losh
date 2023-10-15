#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char **strs;
    size_t size;
    size_t capacity;
} StrVector;

StrVector *alloc_str_vector(void);
void free_str_vector(StrVector *sv);

int32_t add_str(StrVector *sv, const char *str);
char *concatenate_strs(StrVector *sv, char c);
