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
 */
class Compiler
{
public:
    /**
     * @brief constructor accepting source code and output stream
     * 
     * @param code the code to be compiled
     * @param fout the stream to which the compiled data will be directed
     */
    Compiler(std::string&& code, std::ofstream& fout) noexcept : code{std::move(code)}, fout{fout}
    {
    }

    /**
     * @brief Compilation method of the program. The result will be sent to the stream, the ref to which was passed to the constructor
     * 
     */
    void build();

private:
    std::string code;
    std::ofstream& fout;

    // bytecode version
    constexpr static inline int version = 1;
};



void Compiler::build()
{
    Lexer lexer{ move(code) };
    std::vector<Token> tokens;
    try {
        tokens = lexer.separation();
    }
    catch (const std::exception& e) {
        print(stderr, "{}", e.what());
    }

    Parser parser(move(tokens));
    try {
        parser.parse();
    }
    catch (const std::exception& e) {
        print(stderr, "{}", e.what());
    }

    balib::writeNum(fout, version);
    balib::writeString(fout, parser.get_assembly().name);
    balib::writeString(fout, parser.get_assembly().version);
    balib::writeNum(fout, parser.get_include_assembly().size());
    for (auto& item : parser.get_include_assembly()) {
        balib::writeString(fout, item);
    }
    balib::writeNum(fout, parser.get_functions().size());
    try {
        for (auto& item : parser.get_functions()) {
            item.build(fout);
        }
    }
    catch (const std::exception& e) {
        print(stderr, "{}", e.what());
    }
}
