#include <cstring>
#include <gtest/gtest.h>

extern "C" {
#include "../src/cmd_parser.h"
}

TEST(CommandParsingValidInput, BasicInput) {
    char cmd[] = "echo banana\n";
    CommandList *cmd_list = get_cmds(cmd);

    EXPECT_NE(cmd_list, nullptr);
    EXPECT_EQ(cmd_list->size, 1);
    EXPECT_EQ(cmd_list->capacity, 4);

    EXPECT_TRUE(strcmp(cmd_list->cmds->args[0], "echo") == 0);
    EXPECT_TRUE(strcmp(cmd_list->cmds->args[1], "banana") == 0);

    EXPECT_EQ(cmd_list->input, nullptr);
    EXPECT_EQ(cmd_list->output, nullptr);

    EXPECT_FALSE(cmd_list->background_process);

    free_cmds(cmd_list);
}
