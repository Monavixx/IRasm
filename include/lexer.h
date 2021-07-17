#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "token.h"
#include "exception/lexer_exception.h"

class Lexer
{
public:
    Lexer(auto&& code) noexcept : code{forward<decltype(code)>(code)}
    {
    }
    std::vector<Token> separation() const;

private:
    std::string code;
};