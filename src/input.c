#include "input.h"

#include <stdio.h>
#include <string.h>

void get_input(char input[INPUT_BUFFER_SIZE]) {
    char *tmp = fgets(input, INPUT_BUFFER_SIZE, stdin);
    if (tmp == NULL || tmp[0] == '\n') {
        input[0] = '\0';
        clearerr(stdin);
    }
}
