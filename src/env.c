// needed to use `setenv` and `chdir` functions
#define _POSIX_C_SOURCE 200112L

#include "env.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:."

void init_env(void) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw == NULL) {
        fprintf(stderr, "ERROR: user not found\n");
        exit(EXIT_FAILURE);
    }

    setenv("USER", pw->pw_name, 1);
    setenv("HOME", pw->pw_dir, 1);
    setenv("PWD", pw->pw_dir, 1);
    setenv("PATH", PATH, 1);
    setenv("SHELL", "./bin/debug/losh", 1);

    // change current directory to $HOME
    (void)chdir(pw->pw_dir);
}
