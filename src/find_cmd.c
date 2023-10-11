#include "find_cmd.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static char *join_paths(const char *root, const char *subdirs) {
    size_t size = strlen(root) + 1 + strlen(subdirs) + 1;
    char *result = calloc(size, 0);
    strcat(result, root);
    strcat(result, "/");
    strcat(result, subdirs);
    strcat(result, "\0");
    return result;
}

// FIXME: the bad use of realloc here can cause a dangling pointer in case of
// lack of memory
char *find_all_command(const char *command) {
    char *result = NULL;
    const char *delim = ":";
    char default_path[] = DEFAULT_PATH;
    char *dir_path = strtok(default_path, delim);
    while (dir_path) {
        char *absolute_command_path = join_paths(dir_path, command);
        struct stat file_info;
        if (stat(absolute_command_path, &file_info) == 0) {
            if (file_info.st_mode & S_IXUSR) {
                if (!result) {
                    result = calloc(strlen(absolute_command_path), 0);
                } else {
                    result = realloc(result,
                                     1 + strlen(result) +
                                         strlen(absolute_command_path));
                    strcat(result, "\n");
                }
                strcat(result, absolute_command_path);
            }
        }
        free(absolute_command_path);
        dir_path = strtok(NULL, delim);
    }

    if (!result) {
        return result;
    }

    result = realloc(result, strlen(result) + 1);
    strcat(result, "\0");
    return result;
}

char *find_command(const char *cmd) {
    const char *delim = ":";
    char default_path[] = DEFAULT_PATH;
    char *dir_path = strtok(default_path, delim);
    while (dir_path) {
        char *absolute_command_path = join_paths(dir_path, cmd);
        struct stat file_info;
        if (stat(absolute_command_path, &file_info) == 0) {
            if (file_info.st_mode & S_IXUSR) {
                return absolute_command_path;
            }
        }
        free(absolute_command_path);
        dir_path = strtok(NULL, delim);
    }

    return NULL;
}
