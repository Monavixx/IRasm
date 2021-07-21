#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "balib.h"
#include "lexer.h"
#include "parser/parser.h"

/**
 * @brief the class responsible for compiling the program
 * @tparam _OutputStream the type of stream to which the compiled data will be written
 */
template<balib::OutputStream _OutputStream>
class Compiler
{
public:
    /**
     * @brief Construct a new Compiler object
     * 
     * @param[in] code(std::string) the code to be compiled
     * @param[in] fout the stream to which the compiled data will be directed
     */
    Compiler(auto&& code, _OutputStream& fout) noexcept : code{std::forward<decltype(code)>(code)}, fout{fout}
    {
    }

    /**
     * @brief Compilation method of the program. The result will be sent to the stream, the ref to which was passed to the constructor
     * 
     */
    void build()
    {
        Lexer lexer{move(code)};
        std::vector<Token> tokens;
        try {
            tokens = lexer.separation();
        }
        catch (const all_exception& e) {
            std::cerr << e.get_message() << '\n';
        }

        Parser parser(move(tokens));

        try {
            parser.parse();
        }
        catch (const all_exception& e) {
            std::cerr << e.get_message() << '\n';
        }
        // Debug
        /*for(auto& item : parser.functions)
        {
            std::cout << item.name << "\n\t" << item.maxstack << "\n\t";
            for(auto& item2 : item.locals)
            {
                std::cout << item2.name << ':' << item2.dataType << "; ";
            }
            for(auto& item2 : item.opcodes)
            {
                std::cout << "\n\t" << item2.name << "\n\t\t";
                for(auto& item3 : item2.tokens)
                {
                    std::cout << item3.word << "; ";
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }*/

        balib::writeStdArray(fout, balib::numToBytes(version));
    }

private:
    std::string code;
    _OutputStream& fout;

    // bytecode version
    constexpr static inline int version = 1;
};