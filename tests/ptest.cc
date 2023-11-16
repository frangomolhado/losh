// TEMPORARY FILE JUST FOR INITIAL TEST COMPILATION TEST

#include <cstring>
#include <gtest/gtest.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include "env.h"
}

TEST(Enviroment2, Variables2) {
    init_env();
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    EXPECT_TRUE(strcmp(getenv("HOME"), pw->pw_dir) == 0);
}
