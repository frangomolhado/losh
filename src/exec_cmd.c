#include "exec_cmd.h"

#include "builtins.h"
#include "cmd_parser.h"
#include "find_cmd.h"

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static int32_t exec_binary(const Command *cmd) {
    pid_t pid = fork();
    int32_t pid_status = 0;
    if (pid == -1) {
        // TODO: handle error
    } else if (pid == 0) {
        const char *cmd_path = find_command(cmd->args[0]);
        execv(cmd_path, cmd->args);
    } else {
        waitpid(pid, &pid_status, 0);
    }

    return pid_status;
}

// TODO: handle errors of incorrect number of min_args and max_args sizes
static int32_t exec_builtin(Builtin const *builtin, char **args) {
    return builtin->handler(args);
}

int32_t exec_cmd(CommandList *cmdlist) {
    const char *cmd = cmdlist->cmds[0].args[0];
    Builtin const *builtin = get_builtin(cmd);
    if (builtin) {
        char **args = cmdlist->cmds[0].args;
        return exec_builtin(builtin, args);
    }

    return exec_binary(&cmdlist->cmds[0]);
}
