#pragma once

#include "input.h"

#include <stddef.h>

typedef struct {
    char **args;
    size_t args_size;
    size_t args_capacity;
} Command;

typedef struct {
    Command *cmds;
    size_t size;
    size_t capacity;
} CommandList;

CommandList *get_commands(char input[INPUT_BUFFER_SIZE]);
