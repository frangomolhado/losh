#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "cmd_parser.h"
}

TEST(CommandParsingValidInput, BasicInput) {
    char input_mock[] = "echo banana\n";
    Command *cmd = get_cmd(input_mock);

    EXPECT_NE(cmd, nullptr);
    EXPECT_EQ(cmd->size, 3);
    EXPECT_EQ(cmd->capacity, 8);

    EXPECT_TRUE(strcmp(cmd->args[0], "echo") == 0);
    EXPECT_TRUE(strcmp(cmd->args[1], "banana") == 0);
    EXPECT_EQ(cmd->args[2], nullptr);
}
