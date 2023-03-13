#include <iostream>
#include <sstream>

#include "eval.hpp"
#include "lex.hpp"
#include "parse.hpp"

std::string eval(std::string cmd) {
    Lexer lexer;
    Parser parser;
    std::stringstream ss;
    
    auto tokens = lexer.lex(cmd);
    for (auto t : tokens)
    {
        if(t.type == TokenType::Err)
        {
            return "Error for token \"" + t.value + "\" at " + std::to_string(t.line) + ":" + std::to_string(t.start) + "-" + std::to_string(t.end);
        }
        std::cout << t;
    }
    std::cout << std::endl;
    auto tree = parser.parse_line(tokens);
    std::cout << *tree << std::endl;
    return ss.str();
}