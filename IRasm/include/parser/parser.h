#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "token.h"
#include "function.h"
#include "opcode.h"
#include "../exception/exception.h"

#include <boost/lexical_cast.hpp>

/**
 * @brief a class that processes a list of tokens and stores all data in itself
 */
class Parser
{
public:
    /**
     * @brief a constructor that takes a list of tokens to be processed
     * 
     * \param tokens list of tokens to be processed
     */
    Parser(std::vector<Token>&& tokens) : tokens{std::move(tokens)}
    {
    }

    /**
     * @brief method that starts processing
     * 
     */
    void parse();

public:
    /**
     * @brief structure storing assembly information
     */
    struct _Assembly
    {
        std::string name;
        std::string version;
    };

private:
    std::vector<Token> tokens;
    std::vector<Function> functions;
    _Assembly assembly;

    // a list of assemblies to include at runtime
    std::vector<std::string> includeAssembly;
};