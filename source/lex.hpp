#ifndef LEX_HPP
#define LEX_HPP

#include <string>
#include <vector>

enum class TokenType { Plus, Minus, Mul, Div, LParen, RParen, Int, Float, Err, Eol, Eof };

std::string type_name(TokenType);

typedef struct 
{
    TokenType type;
    std::string value;
    unsigned int line;
    unsigned int start;
    unsigned int end;
} Token;

class Lexer {
    public:
    Lexer() : input_text{""}, curr_pos{0}, look{0}, line{1}, offset{1} {};

    std::vector<Token> lex(std::string);
    Token next();
    Token build_token(TokenType type, std::string value);


    private:
    std::string input_text;
    unsigned int curr_pos;
    unsigned int look;
    unsigned int line;
    unsigned int offset;

    Token lexnum();
    Token lexfloat();
};

std::ostream& operator<<(std::ostream& os, const Token& node);

#endif