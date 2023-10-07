#define _POSIX_C_SOURCE 200809L

#include "exec_cmd.h"

#include "cmd_parser.h"
#include "find_cmd.h"

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int exec_binary(const Command *cmd) {
    pid_t pid = fork();
    int pid_status = 0;
    if (pid == -1) {
        // TODO: handle error
    } else if (pid == 0) {
        char *cmd_path = find_command(cmd->args[0]);
        execv(cmd_path, cmd->args);
    } else {
        waitpid(pid, &pid_status, 0);
    }

    return pid_status;
}

int exec_cmds(CommandList *cmdlist) {
    return exec_binary(&cmdlist->cmds[0]);
}
