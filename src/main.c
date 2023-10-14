#include "builtins.h"
#include "cmd_parser.h"
#include "env.h"
#include "exec_cmd.h"
#include "input.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    init_env();
    init_builtins();

    char input[INPUT_BUFFER_SIZE];
    bool run = true;
    while (run) {
        printf("losh$ "); // temporary while a proper prompt doesn't exist
        get_input(input);
        CommandList *cmdlist = get_commands(input);
        exec_cmd(cmdlist);
    }

    return EXIT_SUCCESS;
}
