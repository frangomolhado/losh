#pragma once

#include "input.h"

#include <stdbool.h>
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
    char *input;
    char *output;
    bool background_process;
} CommandList;

void free_cmds(CommandList *cmdlist);

CommandList *get_cmds(char input[INPUT_BUFFER_SIZE]);
