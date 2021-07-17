#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "token.h"

class Lexer
{
public:
    Lexer(auto&& code) noexcept : code{forward<decltype(code)>(code)}
    {
    }
    std::vector<Token> separation() const noexcept;

private:
    std::string code;
};