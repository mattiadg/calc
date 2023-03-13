#include <iostream>
#include <string>

#include "eval.hpp"
#include "lex.hpp"
#include "parse.hpp"


int main (int argc, char* argv[]) {
    if (argc == 1)
    {
        std::string line;
        while (true)
        {
            std::cout << "> ";
            std::getline(std::cin, line);
            if (line == "")
            {
                break;
            }
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
