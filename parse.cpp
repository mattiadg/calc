#include <set>
#include <utility>

#include "parse.hpp"

std::shared_ptr<CSTNode> Parser::parse_line(const std::vector<Token> & tokens)
{
    return parse_expression(tokens.begin(), tokens.end(), 0, nullptr);
}

std::shared_ptr<CSTNode> Parser::parse_expression(std::vector<Token>::const_iterator tokens_it, std::vector<Token>::const_iterator tokens_end, int precedence, std::shared_ptr<CSTNode> prev)
{
    if(tokens_it != tokens_end)
    {
        auto num_node = expect(nums, *tokens_it++);
        if(tokens_it == tokens_end)
        {
            if (prev != nullptr)
            {
                append_right(prev, num_node);
                return prev;
            }
            
        }
        auto op_node = expect(ops, *tokens_it++);
        std::shared_ptr<CSTNode> top;
        auto curr_prec = prec_table.at(op_node->lex_type);

        if(prev == nullptr)
        {
            op_node->children.push_back(num_node);
            top = op_node;
        } else if (curr_prec > precedence)
        {
            append_right(prev, op_node);
            op_node->children.push_back(num_node);
            top = prev;
        } else {
            append_right(prev, num_node);
            op_node->children.push_back(prev);
            top = op_node;
        }
        return parse_expression(tokens_it, tokens_end, curr_prec, top);
    } else {
        return nullptr;
    }
}

std::shared_ptr<CSTNode> Parser::expect(std::set<TokenType> valid_types, const Token token)
{
    if (auto token_type = valid_types.find(token.type); token_type != valid_types.end())
    {
        return std::make_shared<CSTNode>(token_to_cst(token.type), token.type, token.value);
    } else {
        return nullptr;
    }
}

CSTType token_to_cst(TokenType ttype) 
{
    CSTType ret;
    switch (ttype)
    {
    case TokenType::Int:
        ret = CSTType::Num;
        break;
    case TokenType::Float:
        ret = CSTType::Num;
        break;
    case TokenType::Plus:
        ret = CSTType::Op;
        break;
    case TokenType::Minus:
        ret = CSTType::Op;
        break;
    case TokenType::Mul:
        ret = CSTType::Op;
        break;
    case TokenType::Div:
        ret = CSTType::Op;
        break;
    default:
        break;
    }
    return ret;
}

std::string cst_to_str(CSTType type)
{
    if(type == CSTType::Num)
    {
        return "Num";
    } else if(type == CSTType::Op) 
    {
        return "Op";
    }
    return "Err";
}

void Parser::append_right(std::shared_ptr<CSTNode> tree, std::shared_ptr<CSTNode> new_node)
{
    if (tree->children.size() == 1)
    {
        tree->children.push_back(new_node);
    } else {
        append_right(tree->children[1], new_node);
    }
}

std::ostream& operator<<(std::ostream& os, const CSTNode& node)
{
    os << cst_to_str(node.ast_type) << "(" << node.value << ")[";
    for (auto child_it = node.children.begin(); child_it != node.children.end(); child_it++)
    {
        if (child_it != node.children.begin())
        {
            os << ", ";
        }
        os << **child_it;
    }
    os << "]";
    return os;
}
