#include "exec_cmd.h"

#include "builtins.h"
#include "cmd_parser.h"
#include "find_cmd.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

typedef int32_t (*ExecFuntion)(char **args);

static void redirect_input(ExecFuntion func, char **args, char *input_file) {
    int32_t original_stdin = dup(STDOUT_FILENO);
    int32_t file_descriptor = open(input_file, O_RDONLY);
    if (file_descriptor == -1) {
        // TODO: handle error opening file
    }

    dup2(file_descriptor, STDIN_FILENO);
    close(file_descriptor);

    func(args);

    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
}

static void redirect_output(ExecFuntion func, char **args, char *output_file) {
    int32_t original_stdout = dup(STDOUT_FILENO);
    int32_t file_descriptor = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

static void redirect_input_output(ExecFuntion func, char **args, char *input_file,
                                  char *output_file) {
    int32_t original_stdin = dup(STDOUT_FILENO);
    int32_t input_descriptor = open(input_file, O_RDONLY);
    if (input_descriptor == -1) {
        // TODO: handle error opening file
    }

    int32_t original_stdout = dup(STDOUT_FILENO);
    int32_t output_descriptor = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_descriptor == -1) {
        // TODO: handle error opening file
    }

    dup2(input_descriptor, STDIN_FILENO);
    close(input_descriptor);

    dup2(output_descriptor, STDOUT_FILENO);
    close(output_descriptor);

    func(args);

    fflush(stdout);

    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);

    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
}

static int32_t fork_exec(ExecFuntion func, char **args, char *input_file, char *output_file) {
    pid_t pid = fork();
    int32_t pid_status = 0;
    if (pid == -1) {
        // TODO: handle error
    } else if (pid == 0) {
        if (input_file == NULL && output_file == NULL) {
            func(args);
        } else if (input_file != NULL && output_file == NULL) {
            redirect_input(func, args, input_file);
        } else if (input_file == NULL && output_file != NULL) {
            redirect_output(func, args, output_file);
        } else {
            redirect_input_output(func, args, input_file, output_file);
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
        status = fork_exec(exec_binary, args, cmdlist->input, cmdlist->output);
    } else if (cmdlist->input != NULL || cmdlist->output != NULL) {
        status = fork_exec(builtin->handler, args, cmdlist->input, cmdlist->output);
        printf("\n");
    } else {
        status = builtin->handler(args);
        printf("\n");
    }

    return status;
}
