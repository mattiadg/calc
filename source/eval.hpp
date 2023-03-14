#ifndef EVAL_HPP
#define EVAL_HPP

#include <string>

#include "parse.hpp"

class Value 
{
    public:
    Value() : type{"object"} {};
    Value(std::string _t) : type{_t} {};
    virtual std::string tostring();
    std::string type; 
};

class IntValue : public Value
{
    public:
    IntValue(int _v) : Value("int"), value{_v}  {};
    virtual std::string tostring() {return std::to_string(value);}
    int value;
};

class FloatValue : public Value
{
    public:
    FloatValue(float _v) : Value("float") , value{_v}{};
    virtual std::string tostring() {return std::to_string(value);}
    float value;
};


std::string eval(std::shared_ptr<CSTNode> tree);  // Tree descent evaluation

std::shared_ptr<Value> recur(std::shared_ptr<CSTNode> tree);
std::shared_ptr<Value> eval_leaf(std::shared_ptr<CSTNode> leaf);
std::shared_ptr<Value> eval_op(std::shared_ptr<CSTNode> node, std::vector<std::shared_ptr<Value>>& args);

std::string min_supertype(std::string, std::string);

/** Built-in Operations*/
std::unique_ptr<Value> plus(std::shared_ptr<Value>, std::shared_ptr<Value>);
std::unique_ptr<Value> minus(std::shared_ptr<Value>, std::shared_ptr<Value>);
std::unique_ptr<Value> mul(std::shared_ptr<Value>, std::shared_ptr<Value>);
std::unique_ptr<Value> div(std::shared_ptr<Value>, std::shared_ptr<Value>);

#endif