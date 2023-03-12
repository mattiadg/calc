#include <iostream>
#include <sstream>
#include <string>
#include "lex.hpp"
#include "parse.hpp"

std::string eval(std::string cmd);

int main (int argc, char* argv[]) {
    if (argc == 1)
    {
        std::string line;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, line);
            std::cout << eval(line + "\n") << std::endl;
        }
        std::cout << "Qutting... Good bye" << std::endl;
    } else if (argc == 2)
    {
        std::string cmd {argv[1]};
        std::cout << eval(cmd + "\n") << std::endl;
    }
    return 0;
}

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
        ss << type_name(t.type) << "{" << t.value << "} ";
    }
    auto tree = parser.parse_line(tokens);
    std::cout << *tree << std::endl;
    return ss.str();
}