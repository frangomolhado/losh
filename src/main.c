#include "builtins.h"
#include "cmd_parser.h"
#include "env.h"
#include "exec_cmd.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE (size_t)4096

int main(void) {
    init_env();
    init_builtins();

    char input[INPUT_SIZE];
    Command cmd;
    init_cmd(&cmd);
    bool run = true;
    while (run) {
        printf("losh$ "); // temporary while a proper prompt doesn't exist
        fflush(stdout);

        char *get_result = fgets(input, INPUT_SIZE, stdin);
        if (get_result == NULL) {
            const char *errmsg = strerror(errno);
            perror(errmsg);
            clearerr(stdin);
            continue;
        } else if (get_result[0] == '\n') {
            continue;
        }

        if (get_cmd(input, &cmd) != 0) continue;

        exec_cmd(&cmd);
    }

    return EXIT_SUCCESS;
}
