#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <memory>

#include "lex.hpp"

class Queue 
{
    public:
    Queue(): pos{0} {};
    ~Queue() = default;

    Token peek();
    std::shared_ptr<Token> next();
    void go_back();
    
    void add(Token);
    bool empty();

    private:
    std::vector<Token> tokens;
    long unsigned int pos;

};

#endif