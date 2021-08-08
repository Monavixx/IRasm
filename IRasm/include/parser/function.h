#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "local.h"
#include "opcode.h"
#include "parameter.h"
#include "balib.h"


/**
 * @brief a class that stores all information about functions in irasm
 */
class Function
{
public:
    /**
     * @brief a constructor that takes all information about a function. Also it sets id for parameters and local variables
     * 
     * @param name function name
     * @param parameters function parameter map
     * @param opcodes function instruction list
     * @param locals function local variable map
     * @param maxstack maximum stack size
     */
    Function(std::string_view name, std::unordered_map<std::string, Parameter>&& parameters,
        std::vector<OpCode>&& opcodes, std::unordered_map<std::string, Local>&& locals, size_t maxstack)
        : name{ name }, parameters{ std::move(parameters) }, opcodes{ std::move(opcodes) }, locals{ std::move(locals) }, maxstack{ maxstack }
    {
        for (size_t i = 0; auto& [name, param] : this->parameters) {
            param.set_id(i++);
        }
        for (size_t i = 0; auto& [name, local] : this->locals) {
            local.set_id(i++);
        }
    }

    void build(std::ofstream& outputStream)
    {
        balib::writeString(outputStream, name);
        balib::writeNum(outputStream, parameters.size());
        for (auto& [name, param] : parameters) {
            balib::writeString(outputStream, param.get_data_type());
            balib::writeNum(outputStream, param.get_id());
        }
        balib::writeNum(outputStream, locals.size());
        for (auto& [name, local] : locals) {
            balib::writeString(outputStream, local.get_data_type());
            balib::writeNum(outputStream, local.get_id());
        }
        balib::writeNum(outputStream, maxstack);

        //Buffer opcodesBuffer;

        balib::writeNum(outputStream, opcodes.size());
        for (auto& item : opcodes) {
            item.build(outputStream, *this);
        }
    }

private:
    std::vector<OpCode> opcodes;
    std::string name;
    std::unordered_map<std::string, Parameter> parameters;
    std::unordered_map<std::string, Local> locals;
    size_t maxstack;
};