#include <stdio.h>
#include <string.h>

#include "input.h"

void get_input(char *input) {
    char *tmp = fgets(input, INPUT_BUFFER_SIZE, stdin);
    if (!tmp) {
        strcpy(input, "\0");
        clearerr(stdin);
    }
}
