#include <stdio.h>
#include <errno.h>

#include "error_handler.h"

void handle_error(int error) {
    switch (error) {
        case(ENOMEM):
            fprintf(stderr, "ERROR: Insufficient memory.\n");
            break;
        case(EINVAL):
            fprintf(stderr, "ERROR: Invalid arguments.\n");
            break;
        case(EIO):
            fprintf(stderr, "ERROR: Input/Output error.\n");
            break;
        default:
            fprintf(stderr, "ERROR: Unkown error.\n");
            break;
    }
}
