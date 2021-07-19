#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "token.h"
#include "function.h"
#include "opcode.h"

#include <boost/lexical_cast.hpp>

class Parser
{
public:
    Parser(auto&& tokens) : tokens{std::forward<decltype(tokens)>(tokens)}
    {
    }
    void parse();

public:
    struct _Assembly
    {
        std::string name;
        std::string version;
    };

public:
    std::vector<Token> tokens;
    std::vector<Function> functions;
    _Assembly assembly;
    std::vector<std::string> includeAssembly;
};