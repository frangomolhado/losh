#include "input.h"
#include "parser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    bool run = true;
    while (run) {
        printf("$prompt$ "); // temporary while a proper prompt doesn't exist
        get_input(input);
        TokenQueue *tk_queue = parse(input);
    }

    return EXIT_SUCCESS;
}
