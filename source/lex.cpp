#include <cctype>
#include <iostream>
#include "lex.hpp"


std::string type_name(TokenType type)
{
    std::string name;
    switch (type)
    {
    case TokenType::Plus:
        name = "Plus";
        break;
    case TokenType::Minus:
        name = "Minus";
        break;
    case TokenType::Mul:
        name = "Mul";
        break;
    case TokenType::Div:
        name = "Div";
        break;
    case TokenType::LParen:
        name = "LParen";
        break;
    case TokenType::RParen:
        name = "RParen";
        break;
    case TokenType::Int:
        name = "Int";
        break;
    case TokenType::Float:
        name = "Float";
        break;
    case TokenType::Eof:
        name = "Eof";
        break;
    case TokenType::Err:
        name = "Err";
        break;
    default:
        name = "UNK";
        break;
    }
    return name;
}

std::vector<Token> Lexer::lex(std::string text) 
{
    input_text += text;
    std::vector<Token> tokens{};
    Token token = next();

    while (token.type != TokenType::Eol && token.type != TokenType::Eof)
    {
        tokens.push_back(token);
        token = next();
    }
    return tokens;
}

Token Lexer::next()
{
    while (input_text[curr_pos] == ' ' || input_text[curr_pos] == '\n')
    {
        char curr = input_text[curr_pos];
        ++offset;
        ++curr_pos;
        if(curr == '\n')
        {
            ++line;
            offset = 1;
            return build_token(TokenType::Eol, "\n");
        }        
    }
    
    Token t;
    look = curr_pos;
    if (std::isdigit(input_text[curr_pos]))
    {
        t = lexnum();
    } else if (input_text[curr_pos] == '+')
    {
        t = build_token(TokenType::Plus, "+");
    } else if (input_text[curr_pos] == '-')
    {
        t = build_token(TokenType::Minus, "-");
    }  else if (input_text[curr_pos] == '*')
    {
        t = build_token(TokenType::Mul, "*");
    }  else if (input_text[curr_pos] == '/')
    {
        t = build_token(TokenType::Div, "/");
    } else if (input_text[curr_pos] == '(')
    {
        t = build_token(TokenType::LParen, "(");
    } else if (input_text[curr_pos] == ')')
    {
        t = build_token(TokenType::RParen, ")");
    } else if (curr_pos < input_text.length())
    {
        t = build_token(TokenType::Err, std::string(input_text.substr(curr_pos)));
    } else 
    {   
        t = build_token(TokenType::Eof, "");
    }

    return t;
}

Token Lexer::build_token(TokenType type, std::string value)
{
    int token_length = static_cast<int>(value.length());
    Token token = Token{ type, value, line, offset, offset + token_length - 1 };
    ++look;
    curr_pos = look;
    offset += token_length;
    return token;
}

Token Lexer::lexnum()
{
    while (std::isdigit(input_text[look]) || input_text[look] == '.')
    {
        if (input_text[look] == '.') 
        {
            return lexfloat();
        }
        ++look;
    }
    --look;
    Token next_token = build_token(TokenType::Int, std::string(input_text.substr(curr_pos, look - curr_pos + 1)));
    return next_token;
}

Token Lexer::lexfloat()
{
    ++look;
    while (std::isdigit(input_text[look]))
    {
        look++;
    }
    --look;
    Token next_token = build_token(TokenType::Float, std::string(input_text.substr(curr_pos, look - curr_pos + 1)));
    return next_token;
}

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    return os << type_name(t.type) << "{" << t.value << "} ";
}
