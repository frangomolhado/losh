#pragma once

#define DEFAULT_PATH \
    "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:."

const char *find_all_command(const char *cmd);
const char *find_command(const char *cmd);
