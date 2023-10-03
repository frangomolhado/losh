#include "input.h"
#include "tokenizer.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[INPUT_BUFFER_SIZE];
    bool run = true;
    while (run) {
        printf("$prompt$ "); // temporary while a proper prompt doesn't exist
        get_input(input);
        TokenQueue *tk_queue = tokenize(input);
    }

    return EXIT_SUCCESS;
}
