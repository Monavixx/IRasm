#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "balib.h"

using rbyte = unsigned char;

class Compiler
{
public:
    Compiler(auto&& code, std::ofstream&& fout) noexcept : code{std::forward<decltype(code)>(code)}, fout{std::forward<std::ofstream>(fout)}
    {
    }

    void build() noexcept;

private:
    std::string code;
    std::ofstream fout;
    constexpr static inline int version = 1;
};