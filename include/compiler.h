#pragma once

#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "balib.h"

/**
 * @brief the class responsible for compiling the program
 * @tparam OutputStream the type of stream to which the compiled data will be written
 */
template<class OutputStream>
class Compiler
{
public:
    /**
     * @brief Construct a new Compiler object
     * 
     * @param[in] code(std::string) the code to be compiled
     * @param fout the stream to which the compiled data will be directed
     */
    Compiler(auto&& code, OutputStream& fout) noexcept : code{std::forward<decltype(code)>(code)}, fout{fout}
    {
    }

    /**
     * @brief Compilation method of the program. The result will be sent to the stream, the ref to which was passed to the constructor 
     * 
     */
    void build() noexcept
    {
        fout.write((char*)balib::intToBytes(version).data(), 4);
    }

private:
    std::string code;
    OutputStream& fout;

    // bytecode version
    constexpr static inline int version = 1;
};