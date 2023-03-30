#include <set>
#include <utility>

#include "parse.hpp"


std::shared_ptr<CSTNode> Parser::parse_line(const std::vector<Token> & tokens)
{
    auto queue = Queue();
    for (auto t : tokens)
    {
        if(t.type == TokenType::Err)
        {
            std::cout << "Error for token \"" + t.value + "\" at " + std::to_string(t.line) + ":" + std::to_string(t.start) + "-" + std::to_string(t.end);
            exit(1);
        }
        queue.add(t);
    }
    return parse_expression(queue, 0, nullptr);
}

std::shared_ptr<CSTNode> Parser::parse_expression(Queue& queue, int precedence, std::shared_ptr<CSTNode> prev)
{
    if(!queue.empty())
    {
        std::shared_ptr<CSTNode> num_node;
        if (auto lparen_node = expect(lparen, queue.peek()); lparen_node != nullptr)
        {
            num_node = parse_inparens(queue);  
        } else
        {
            num_node = expect(nums, *queue.next());
        }
        if(queue.empty())
        {
            if(prev != nullptr)
            {
                prev->children.push_back(num_node);
            } else 
            {
                prev = num_node;
            }
            return prev;
        }

        if(auto rparen_node = expect(rparen, queue.peek()); rparen_node != nullptr)
        {
            prev->children.push_back(num_node);
            return prev;
        }
        auto op_node = expect(ops, *queue.next());
        auto curr_prec = prec_table.at(op_node->lex_type);
        auto top = concat_nodes(prev, op_node, num_node, curr_prec > precedence);

        return parse_expression(queue, curr_prec, top);
    } else {
        return nullptr;
    }
}

std::shared_ptr<CSTNode> Parser::parse_inparens(Queue& queue)
{
    auto lparen_node = expect(lparen, *queue.next());
    auto num_node = parse_expression(queue, prec_table.at(lparen_node->lex_type), nullptr);
    auto rparen_node = expect(rparen, *queue.next());
    return num_node;
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

std::shared_ptr<CSTNode> Parser::concat_nodes(std::shared_ptr<CSTNode> par1, std::shared_ptr<CSTNode> par2, std::shared_ptr<CSTNode> child, bool greater_than)
{
    std::shared_ptr<CSTNode> top;
    if(par1 == nullptr)
    {
        par2->children.push_back(child);
        top = par2;
    } else if (greater_than)
    {
        append_right(par1, par2);
        par2->children.push_back(child);
        top = par1;
    } else {
        append_right(par1, child);
        par2->children.push_back(par1);
        top = par2;
    }
    return top;
}