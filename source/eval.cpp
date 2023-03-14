#include <iostream>
#include <sstream>

#include "eval.hpp"
#include "lex.hpp"
#include "parse.hpp"


std::string Value::tostring()
{
    return "object";
}

std::string eval(std::shared_ptr<CSTNode> tree) {   
    auto value = recur(tree);
    std::string return_value{value->tostring()};
    return return_value;
}

std::shared_ptr<Value> recur(std::shared_ptr<CSTNode> node)
{
    if(node->children.empty())
    {
        auto x = eval_leaf(node);
        return x;
    }

    std::vector<std::shared_ptr<Value>> child_v{};
    for (auto child : node->children)
    {
        child_v.push_back(recur(child));
    }
    return eval_op(node, child_v);
}

std::shared_ptr<Value> eval_leaf(std::shared_ptr<CSTNode> leaf)
{
    if(leaf->lex_type == TokenType::Int)
    {
        auto val = std::make_shared<IntValue>(std::stoi(leaf->value));
        return val;
    } else
    {
        auto val = std::make_shared<FloatValue>(std::stof(leaf->value));
        return val;
    }
}

std::shared_ptr<Value> eval_op(std::shared_ptr<CSTNode> op_node, std::vector<std::shared_ptr<Value>> & args)
{
    std::shared_ptr<Value> val; 
    switch (op_node->lex_type)
    {
    case TokenType::Plus:
        val = plus(args[0], args[1]);
        break;
    case TokenType::Minus:
        val = minus(args[0], args[1]);
        break;
    case TokenType::Mul:
        val = mul(args[0], args[1]);
        break;
    case TokenType::Div:
        val = div(args[0], args[1]);
        break;
    default:
        break;
    };
    return val;
}

std::unique_ptr<Value> plus(std::shared_ptr<Value> v1, std::shared_ptr<Value> v2)
{
    std::string type {min_supertype(v1->type, v2->type)};
    if(type == "int")
    {
        auto val {std::make_unique<IntValue>(static_cast<IntValue&>(*v1).value + static_cast<IntValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "float")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value + static_cast<FloatValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "int")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value + static_cast<IntValue&>(*v2).value)};
        return val;
    } else
    {
        auto val {std::make_unique<FloatValue>(static_cast<IntValue&>(*v1).value + static_cast<FloatValue&>(*v2).value)};
        return val;
    }
}

std::unique_ptr<Value> minus(std::shared_ptr<Value> v1, std::shared_ptr<Value> v2)
{
    std::string type {min_supertype(v1->type, v2->type)};
    if(type == "int")
    {
        auto val {std::make_unique<IntValue>(static_cast<IntValue&>(*v1).value - static_cast<IntValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "float")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value - static_cast<FloatValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "int")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value - static_cast<IntValue&>(*v2).value)};
        return val;
    } else
    {
        auto val {std::make_unique<FloatValue>(static_cast<IntValue&>(*v1).value - static_cast<FloatValue&>(*v2).value)};
        return val;
    }
}

std::unique_ptr<Value> mul(std::shared_ptr<Value> v1, std::shared_ptr<Value> v2)
{
    std::string type {min_supertype(v1->type, v2->type)};
    if(type == "int")
    {
        auto val {std::make_unique<IntValue>(static_cast<IntValue&>(*v1).value * static_cast<IntValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "float")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value * static_cast<FloatValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "int")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value * static_cast<IntValue&>(*v2).value)};
        return val;
    } else
    {
        auto val {std::make_unique<FloatValue>(static_cast<IntValue&>(*v1).value * static_cast<FloatValue&>(*v2).value)};
        return val;
    }
}

std::unique_ptr<Value> div(std::shared_ptr<Value> v1, std::shared_ptr<Value> v2)
{
    std::string type {min_supertype(v1->type, v2->type)};
    if(type == "int")
    {
        auto val {std::make_unique<IntValue>(static_cast<IntValue&>(*v1).value / static_cast<IntValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "float")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value / static_cast<FloatValue&>(*v2).value)};
        return val;
    } else if(v1->type == "float" && v2->type == "int")
    {
        auto val {std::make_unique<FloatValue>(static_cast<FloatValue&>(*v1).value / static_cast<IntValue&>(*v2).value)};
        return val;
    } else
    {
        auto val {std::make_unique<FloatValue>(static_cast<IntValue&>(*v1).value / static_cast<FloatValue&>(*v2).value)};
        return val;
    }
}


std::string min_supertype(std::string t1, std::string t2)
{
    if(t1 == "int")
    {
        return t2;
    } else {
        return "float";
    }
}