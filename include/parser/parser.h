#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "token.h"
#include "function.h"
#include "opcode.h"

class Parser
{
public:
    Parser(auto&& tokens) : tokens{std::forward<decltype(tokens)>(tokens)}
    {
    }
    void parse() const;

private:
    std::vector<Token> tokens;
    std::vector<Function> functions;
};