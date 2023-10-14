// needed to use `strdup` function
#define _POSIX_C_SOURCE 200809L

#include "find_cmd.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct {
    char **paths;
    size_t size;
} PathsList;

PathsList *alloc_paths_list(void) {
    PathsList *pl = malloc(sizeof(PathsList));
    pl->paths = NULL;
    pl->size = 0;
    return pl;
}

static char *join_paths(const char *root, const char *relative) {
    size_t size = strlen(root) + 1 + strlen(relative) + 1;
    char *result = calloc(size, 0);
    if (result == NULL) {
        return NULL;
    }
    strcat(result, root);
    strcat(result, "/");
    strcat(result, relative);
    strcat(result, "\0");
    return result;
}

static bool is_binary(const char *path) {
    struct stat file_info;
    if (stat(path, &file_info) == 0) {
        return file_info.st_mode & S_IXUSR;
    }

    return false;
}

static bool add_path(PathsList *pl, const char *path) {
    if (pl->paths == NULL) {
        pl->paths = malloc(sizeof(char *));
        if (pl->paths == NULL) {
            return false;
        }
        pl->paths[pl->size++] = strdup(path);
    } else {
        char **tmp = realloc(pl->paths, sizeof(char *) * (pl->size + 1));
        if (tmp == NULL) {
            return false;
        }
        pl->paths = tmp;
        pl->paths[pl->size++] = strdup(path);
    }

    return true;
}

static char *concatenate_paths(PathsList *pl, char c) {
    // starter value = number of `c` that will be necessary
    size_t size = pl->size - 1;
    for (size_t i = 0; i < pl->size; i++) {
        size += strlen(pl->paths[i]);
    }

    char *result = malloc(size + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;
    for (size_t i = 0; i < pl->size; i++) {
        strcpy(result + offset, pl->paths[i]);
        offset += strlen(pl->paths[i]);
        result[offset++] = c;
    }
    // change last '\n' to '\0'
    result[offset - 1] = '\0';

    return result;
}

char *find_all_command(const char *cmd) {
    PathsList *pl = alloc_paths_list();
    if (pl == NULL) {
        return NULL;
    }
    const char *delim = ":";
    char *dir_path = strtok(getenv("PATH"), delim);
    while (dir_path) {
        char *cmd_path = join_paths(dir_path, cmd);
        if (cmd_path == NULL) {
            return NULL;
        }

        if (is_binary(cmd_path)) {
            bool successfull = add_path(pl, cmd_path);
            if (!successfull) {
                return NULL;
            }
        }

        free(cmd_path);
        dir_path = strtok(NULL, delim);
    }

    if (pl->paths == NULL) {
        return NULL;
    }

    return concatenate_paths(pl, '\n');
}

char *find_command(const char *cmd) {
    const char *delim = ":";
    char *dir_path = strtok(getenv("PATH"), delim);
    while (dir_path) {
        char *cmd_path = join_paths(dir_path, cmd);
        if (is_binary(cmd_path)) {
            return cmd_path;
        }
        free(cmd_path);
        dir_path = strtok(NULL, delim);
    }

    return NULL;
}
