#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "input.h"

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    bool run = true;
    while (run) {
        printf("$prompt$ "); // temporary while a proper prompt doesn't exist
        get_input(input);
    }

    return EXIT_SUCCESS;
}
