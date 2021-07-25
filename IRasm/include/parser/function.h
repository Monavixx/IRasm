#pragma once

#include <string>
#include <vector>

#include "local.h"
#include "opcode.h"
#include "parameter.h"


/**
 * @brief a class that stores all information about functions in irasm
 */
class Function
{
public:
    /**
     * @brief a constructor that takes all information about a function
     * 
     * @param name function name
     * @param parameters function parameter list
     * @param opcodes function instruction list
     * @param function local variable list
     * @param maxstack maximum stack size
     */
    Function(std::string_view name, std::vector<Parameter>&& parameters, std::vector<OpCode>&& opcodes = {}, std::vector<Local>&& locals = {}, size_t maxstack = 0)
        : name{ name }, parameters{ std::move(parameters) }, opcodes{ std::move(opcodes) }, locals{ std::move(locals) }, maxstack{ maxstack }
    {
    }

    /*std::vector<OpCode>& get_opcodes() noexcept { return opcodes; }
    std::vector<OpCode> get_opcodes() const noexcept { return opcodes; }
    std::vector<Parameter>& get_parameters() noexcept { return parameters; }
    std::vector<Parameter> get_parameters() const noexcept { return parameters; }
    std::vector<Local>& get_locals() noexcept { return locals; }
    std::vector<Local> get_locals() const noexcept { return locals; }
    std::string& get_name() noexcept { return name; }
    std::string get_name() const noexcept { return name; }
    size_t get_maxstack() const noexcept { return maxstack; }*/

private:
    std::vector<OpCode> opcodes;
    std::string name;
    std::vector<Parameter> parameters;
    std::vector<Local> locals;
    size_t maxstack;
};