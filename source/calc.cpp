#include <iostream>
#include <string>

#include "eval.hpp"
#include "lex.hpp"
#include "parse.hpp"


int main (int argc, char* argv[]) {
    Lexer lexer;
    Parser parser;
    if (argc == 1)
    {
        std::string line;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, line);           // READ
            if (line == "")
            {
                break;
            }
            auto tokens = lexer.lex(line + "\n");
            auto tree = parser.parse_line(tokens);
            auto evaled_value = eval(tree);  // EVAL
            std::cout << evaled_value << std::endl; // PRINT
        }                                           // LOOP
        std::cout << "Qutting... Good bye" << std::endl;
    } else if (argc == 2)
    {
        std::string cmd {argv[1]};
        auto tokens = lexer.lex(cmd + "\n");
        auto tree = parser.parse_line(tokens);
        auto evaled_value = eval(tree);
        std::cout << evaled_value << std::endl; // PRINT
    }
    return 0;
}
