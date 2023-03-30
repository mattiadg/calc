#include "queue.hpp"

Token Queue::peek()
{
    return tokens[pos];
}

std::shared_ptr<Token> Queue::next()
{
    return std::make_shared<Token>(tokens[pos++]);
}

void Queue::go_back()
{
    pos--;
}

void Queue::add(Token token)
{
    tokens.push_back(token);
}

bool Queue::empty()
{
    return pos >= tokens.size();
}