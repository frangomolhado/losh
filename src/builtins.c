#include "builtins.h"

#include "find_cmd.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// must be the amount of builtin commands
#define BUILTINS_AMOUNT 2

// builtin commands definitions - initializations at the end of file
static int32_t where(char **args);
static int32_t which(char **args);

// macro for easier node creation
#define NODE(name, handler, min_args, max_args, next) \
    { \
        name, { handler, min_args, max_args }, next \
    }

typedef struct hash_node {
    const char *key;
    Builtin cmd;
    struct hash_node *next;
} HashNode;

static size_t hash(const char *str) {
    uint64_t hash = 5381;
    int c;

    while ((c = *(unsigned char *)str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % BUILTINS_AMOUNT;
}

static HashNode *builtins_hashtable[BUILTINS_AMOUNT] = { NULL };

static void insert_node(HashNode *node) {
    size_t index = hash(node->key);
    HashNode *new_node = malloc(sizeof(HashNode));
    memcpy(new_node, node, sizeof(HashNode));
    if (!builtins_hashtable[index]) {
        builtins_hashtable[index] = new_node;
    } else {
        HashNode *current = builtins_hashtable[index];
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void initialize_builtins(void) {
    HashNode nodes[BUILTINS_AMOUNT] = { NODE("which", which, 0, -1, NULL),
                                        NODE("where", where, 0, -1, NULL) };

    for (int i = 0; i < BUILTINS_AMOUNT; i++) {
        insert_node(&nodes[i]);
    }
}

Builtin const *get_builtin(const char *cmd) {
    size_t index = hash(cmd);
    if (builtins_hashtable[index]) {
        HashNode *current = builtins_hashtable[index];
        while (current) {
            if (strcmp(current->key, cmd) == 0) return &current->cmd;

            current = current->next;
        }
    }

    return NULL;
}

static bool is_builtin(const char *cmd) {
    return get_builtin(cmd) != NULL;
}

static int32_t where(char **args) {
    int32_t status = 0;
    const char *arg = args[1];
    bool is_bltin = is_builtin(arg);
    if (is_bltin) {
        printf("%s: shell built-in command\n", arg);
    }

    char *paths_found = find_all_command(arg);
    if (paths_found) {
        puts(paths_found);
        free(paths_found);
    } else if (!is_bltin) {
        status = -1;
    }

    printf("\n");

    return status;
}

static int32_t which(char **args) {
    int32_t status = 0;
    const char *arg = args[1];
    if (is_builtin(arg)) {
        printf("%s: shell built-in command\n", arg);
    } else {
        char *result = find_command(arg);
        if (result) {
            puts(result);
            free(result);
        } else {
            status = -1;
        }
    }

    printf("\n");

    return status;
}
