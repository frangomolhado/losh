#include "cmd_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMANDS_ARGS_ALLOCATION_FAILED 1
#define COMMANDS_ARGS_REALLOCATION_FAILED 2

void init_cmd(Command *cmd) {
    cmd->size = 0;
    cmd->capacity = 8;
    cmd->args = NULL;
}

static int32_t cmd_add_arg(Command *cmd, char *arg) {
    if (cmd->args == NULL) {
        // not freeing this memory because the OS will free it anyway when
        // the program stops
        cmd->args = malloc(sizeof(char *) * cmd->capacity);
        if (cmd->args == NULL) {
            fprintf(stderr, "\nERROR: memory allocation failed while allocating command's args\n");
            return COMMANDS_ARGS_ALLOCATION_FAILED;
        }
    } else if (cmd->size == cmd->capacity) {
        cmd->capacity *= 2;
        char **tmp = realloc(cmd->args, sizeof(char *) * cmd->capacity);
        if (tmp == NULL) {
            cmd->capacity /= 2;
            fprintf(stderr,
                    "\nERROR: memory reallocation failed while reallocating command's args\n");
            return COMMANDS_ARGS_REALLOCATION_FAILED;
        }

        cmd->args = tmp;
    }

    cmd->args[cmd->size++] = arg;

    return 0;
}

int32_t parse_cmd(char buf[], Command *cmd) {
    init_cmd(cmd);

    const char *delimiter = " \n";
    char *tk = strtok(buf, delimiter);
    while (tk) {
        int32_t status = cmd_add_arg(cmd, tk);
        if (status != 0) {
            return status;
        }

        tk = strtok(NULL, delimiter);
    }

    cmd_add_arg(cmd, NULL);

    return 0;
}
