#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    char **args;
    size_t size;
    size_t capacity;
} Command;

void init_cmd(Command *cmd);
int32_t get_cmd(char buf[], Command *cmd);
