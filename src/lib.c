// needed to use `strdup` function
#define _POSIX_C_SOURCE 200809L

#include "lib.h"

#include <stdlib.h>
#include <string.h>

StrVector *alloc_str_vector(void) {
    StrVector *sv = malloc(sizeof(StrVector));
    sv->strs = NULL;
    sv->size = 0;
    // 32 chosen because it covers the average use case of probably
    // almost every user
    sv->capacity = 32;
    return sv;
}

void free_str_vector(StrVector *sv) {
    for (size_t i = 0; i < sv->size; i++) {
        free(sv->strs[i]);
    }
    free(sv->strs);
    free(sv);
}

int32_t add_str(StrVector *sv, const char *str) {
    if (sv->strs == NULL) {
        sv->strs = malloc(sizeof(char *) * sv->capacity);
    }

    if (sv->size < sv->capacity) {
        sv->strs[sv->size++] = strdup(str);
    } else {
        sv->capacity *= 2;
        sv->strs = realloc(sv->strs, sizeof(char *) * sv->capacity);
        sv->strs[sv->size++] = strdup(str);
    }

    return 0;
}

char *concatenate_strs(StrVector *sv, char c) {
    if (sv->size == 0) {
        return "\0";
    }

    // starter value = number of `c` that will be necessary
    size_t size = sv->size - 1;
    for (size_t i = 0; i < sv->size; i++) {
        size += strlen(sv->strs[i]);
    }

    char *result = malloc(size + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < sv->size; i++) {
        strcpy(result + offset, sv->strs[i]);
        offset += strlen(sv->strs[i]);
        result[offset++] = c;
    }
    // change last char, which is `c`, to '\0'
    result[offset - 1] = '\0';

    return result;
}
