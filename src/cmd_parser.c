#include "cmd_parser.h"

#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Command *alloc_cmd(void) {
    Command *c = malloc(sizeof(Command));
    c->args = NULL;
    c->args_size = 0;
    c->args_capacity = 4;

    return c;
}

static void cmd_add_arg(Command *cmd, char *arg) {
    if (!cmd->args) {
        cmd->args = malloc(sizeof(char *) * cmd->args_capacity);
    } else if (cmd->args_size >= cmd->args_capacity) {
        // FIXME: the bad use of realloc here can cause a dangling pointer in
        // case of lack of memory
        cmd->args_capacity *= 2;
        cmd->args = realloc(cmd->args, sizeof(char *) * cmd->args_capacity);
    }
    cmd->args[cmd->args_size++] = arg;
}

static CommandList *alloc_cmdlist(void) {
    CommandList *l = malloc(sizeof(CommandList));
    l->cmds = NULL;
    l->size = 0;
    l->capacity = 4;

    return l;
}

static void cmdlist_push(CommandList *cmdlist, Command *cmd) {
    if (!cmdlist->cmds) {
        cmdlist->cmds = malloc(sizeof(Command) * cmdlist->capacity);
    } else if (cmdlist->size >= cmdlist->capacity) {
        // FIXME: the bad use of realloc here can cause a dangling pointer in
        // case of lack of memory
        cmdlist->capacity *= 2;
        cmdlist->cmds =
            realloc(cmdlist->cmds, sizeof(Command) * cmdlist->capacity);
        cmdlist->cmds[cmdlist->size++] = *cmd;
    }

    cmd_add_arg(cmd, NULL);
    cmdlist->cmds[cmdlist->size++] = *cmd;
}

// TODO: handle memory allocation fails
CommandList *get_commands(char input[INPUT_BUFFER_SIZE]) {
    CommandList *cmdlist = alloc_cmdlist();
    Command *cmd = alloc_cmd();

    const char *delimiter = " \n";
    char *tk = strtok(input, delimiter);
    while (tk) {
        cmd_add_arg(cmd, tk);
        tk = strtok(NULL, delimiter);
    }

    cmdlist_push(cmdlist, cmd);

    return cmdlist;
}
