#ifndef PARSE_HPP
#define PARSE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "lex.hpp"
#include "queue.hpp"


enum class CSTType {Num, Op};

struct CSTNode
{
    CSTType ast_type;
    TokenType lex_type;
    std::string value;
    std::vector<std::shared_ptr<CSTNode>> children;

    CSTNode(CSTType type, TokenType l_type, std::string val) :ast_type{type}, lex_type{l_type}, value{val} {};
};

CSTType token_to_cst(TokenType);
std::string cst_to_str(CSTType);

const std::set<TokenType> nums {TokenType::Int, TokenType::Float};
const std::set<TokenType> ops {TokenType::Plus, TokenType::Minus, TokenType::Mul, TokenType::Div};
const std::set<TokenType> lparen {TokenType::LParen};
const std::set<TokenType> rparen {TokenType::RParen};

const std::map<TokenType, int> prec_table { {TokenType::Plus, 1}, {TokenType::Minus, 1}, {TokenType::Mul, 2}, {TokenType::Div, 2}, {TokenType::LParen, 0}, {TokenType::RParen, 5}};

class Parser
{
    public:
    Parser() {};

    std::shared_ptr<CSTNode> parse_line(const std::vector<Token>&);
    std::shared_ptr<CSTNode> parse_expression(Queue& queue, int precedence, std::shared_ptr<CSTNode> prev);

    private:
    std::shared_ptr<CSTNode> expect(std::set<TokenType>, const Token);
    void append_right(std::shared_ptr<CSTNode>, std::shared_ptr<CSTNode>);
    std::shared_ptr<CSTNode> concat_nodes(std::shared_ptr<CSTNode>, std::shared_ptr<CSTNode>, std::shared_ptr<CSTNode>, bool);
    std::shared_ptr<CSTNode> parse_inparens(Queue& queue);
};

std::ostream& operator<<(std::ostream& os, const CSTNode& node);

#endif