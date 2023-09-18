#include <stdio.h>
#include <stdlib.h>

#include "io_handler/input_handler.h"

int main(void) {
    while (1) {
        char *input = NULL;
        size_t size = 0;
        bool input_successfull = get_input(&input, &size);

        if (!input_successfull) {
            clearerr(stdin);
            free_input(&input, &size);
            continue;
        }

        free_input(&input, &size);
    }

    return EXIT_SUCCESS;
}
