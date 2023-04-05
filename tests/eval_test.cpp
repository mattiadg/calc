#include <gtest/gtest.h>
#include <iostream>

#include "eval_test.hpp"

std::string eval_string(std::string cmd)
{
    Lexer lexer;
    Parser parser;
    auto tokens = lexer.lex(cmd + "\n");
    auto tree = parser.parse_line(tokens);
    return eval(tree);
}

TEST(End2End_Test, Expect_Eval) 
{
    EXPECT_EQ(2+3, 5);
    EXPECT_EQ(eval_string(std::string("2 + 3")), "5");
    EXPECT_EQ(eval_string(std::string("2.0 + 3")), "5.000000");
    EXPECT_EQ(eval_string(std::string("2 + 3.0")), "5.000000");
    EXPECT_EQ(eval_string(std::string("4 / (2 - 1) * 3.0")), "12.000000");
    EXPECT_EQ(eval_string(std::string("(2 + 3) * 2")), "10");
    EXPECT_EQ(eval_string(std::string("2 + 3 * 2")), "8");
}