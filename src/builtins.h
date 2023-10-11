#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int32_t (*HandlerFunction)(char **);

// set max to -1 for no limit of args
typedef struct builtin {
    HandlerFunction handler;
    uint32_t min_args;
    int32_t max_args;
} Builtin;

void initialize_builtins(void);
Builtin const *get_builtin(const char *cmd);
