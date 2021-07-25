#pragma once

#include <string>
#include <vector>

#include "../token.h"

/**
 * @brief a class that stores information about an instruction in a function
 */
class OpCode
{
public:
    /**
     * @brief a constructor that accepts all information
     * 
     * @param name instruction name
     * @param tokens list of tokens owned by the instruction
     */
    OpCode(std::string_view name, std::vector<Token>&& tokens) : name{name}, tokens{std::move(tokens)}
    {
    }

public:
    std::string name;
    std::vector<Token> tokens;
};