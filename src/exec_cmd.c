#include "exec_cmd.h"

#include "builtins.h"
#include "cmd_parser.h"
#include "find_cmd.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

typedef int32_t (*ExecFuntion)(char **args);

static void redirect_output(ExecFuntion func, char **args, char *output_file) {
    int32_t original_stdout = dup(STDOUT_FILENO);
    int32_t file_descriptor =
        open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        // TODO: handle error opening file
    }

    dup2(file_descriptor, STDOUT_FILENO);
    close(file_descriptor);

    func(args);

    fflush(stdout);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
}

static int32_t fork_exec(ExecFuntion func, char **args, char *output_file) {
    pid_t pid = fork();
    int32_t pid_status = 0;
    if (pid == -1) {
        // TODO: handle error
    } else if (pid == 0) {
        if (output_file == NULL) {
            func(args);
        } else {
            redirect_output(func, args, output_file);
        }
    } else {
        waitpid(pid, &pid_status, 0);
        printf("\n");
    }

    return pid_status;
}

static inline int32_t exec_binary(char **args) {
    const char *cmd_path = find_command(args[0]);
    return execv(cmd_path, args);
}

int32_t exec_cmd(CommandList *cmdlist) {
    int32_t status = 0;

    if (cmdlist == NULL) {
        status = -1;
        return status;
    }

    char **args = cmdlist->cmds[0].args;
    Builtin const *builtin = get_builtin(args[0]);
    // TODO: handle errors of incorrect number of min_args and max_args sizes
    // in builtin execution
    if (builtin == NULL) {
        status = fork_exec(exec_binary, args, cmdlist->output);
    } else if (cmdlist->output != NULL) {
        status = fork_exec(builtin->handler, args, cmdlist->output);
        printf("\n");
    } else {
        status = builtin->handler(args);
        printf("\n");
    }

    return status;
}
