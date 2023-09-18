#include <stdio.h>
#include <errno.h>

#include "input_handler.h"
#include "error_handler.h"

bool get_input(char **input, size_t *size) {
    printf("  > ");
    ssize_t len = getline(input, size, stdin);

    if (len == -1) {
        handle_error(errno);
        return false;
    }

    return true;
}

void free_input(char **input, size_t *size) {
    free(*input);
    *input = NULL;
    *size = 0;
}
