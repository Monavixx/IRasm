#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "token.h"
#include "exception/exception.h"

/**
 * class that processes the source code of the program. Creates a list of tokens as a result
 */
class Lexer
{
public:
    /**
     * @brief constructor accepting the source code of the program
     * 
     * \param code source code of the program
     */
    Lexer(std::string&& code) noexcept : code{std::move(code)}
    {
    }

    /**
     * @brief a processing method that returns a list of tokens as a result
     * 
     * \return list of tokens
     */
    std::vector<Token> separation();

private:
    std::string code;
};