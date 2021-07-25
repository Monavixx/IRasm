#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include <fmt/core.h>

#include "balib.h"
#include "lexer.h"
#include "parser/parser.h"

using namespace std::string_literals;

/**
 * @brief the class responsible for compiling the program
 * @tparam _OutputStream the type of stream to which the compiled data will be written
 */
template<class _OutputStream>
class Compiler
{
public:
    /**
     * @brief constructor accepting source code and output stream
     * 
     * @param code the code to be compiled
     * @param fout the stream to which the compiled data will be directed
     */
    Compiler(std::string&& code, _OutputStream& fout) noexcept : code{std::move(code)}, fout{fout}
    {
    }

    /**
     * @brief Compilation method of the program. The result will be sent to the stream, the ref to which was passed to the constructor
     * 
     */
    void build();

private:
    std::string code;
    _OutputStream& fout;

    // bytecode version
    constexpr static inline int version = 1;
};



template<class _OutputStream>
inline void Compiler<_OutputStream>::build()
{
    Lexer lexer{ move(code) };
    std::vector<Token> tokens;
    try {
        tokens = lexer.separation();
    }
    catch (const all_exception& e) {
        fmt::print(stderr, "{}", e.what() + '\n');
    }

    Parser parser(move(tokens));
    try {
        parser.parse();
    }
    catch (const all_exception& e) {
        fmt::print(stderr, "{}", e.what() + '\n');
    }

    balib::writeNum(fout, version);
}
