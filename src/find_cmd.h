#pragma once

#define DEFAULT_PATH \
    "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:."

char *find_all_command(char *command);
char *find_command(char *command);
