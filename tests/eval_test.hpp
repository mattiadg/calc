#ifndef EVAL_TEST_HPP
#define EVAL_TEST_HPP

#include <string>

#include "../source/lex.hpp"
#include "../source/parse.hpp"
#include "../source/eval.hpp"

std::string eval_string(std::string);

std::string eval_string(std::string cmd)
{
    Lexer lexer;
    Parser parser;
    std::cout << cmd << std::endl;
    auto tokens = lexer.lex(cmd + "\n");
    for (auto token: tokens)
        std::cout << token << std::endl;
    auto tree = parser.parse_line(tokens);
    return eval(tree);
}

#endif