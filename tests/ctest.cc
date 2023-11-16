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

TEST(Enviroment, Variables) {
    init_env();
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    EXPECT_TRUE(strcmp(getenv("USER"), pw->pw_name) == 0);
}
