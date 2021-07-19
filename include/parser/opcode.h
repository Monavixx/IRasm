#pragma once

#include <string>
#include <vector>

#include "../token.h"

class OpCode
{
public:
    OpCode(std::string_view name, const std::vector<Token>& tokens) : name{name}, tokens{tokens}
    {
    }

public:
    std::string name;
    std::vector<Token> tokens;
};