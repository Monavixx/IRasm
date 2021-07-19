#pragma once

#include <string>
#include <vector>

#include "local.h"
#include "opcode.h"

class Function
{
public:
    Function(std::string_view name, const std::vector<OpCode>& opcodes = {}, const std::vector<Local>& locals = {}, size_t maxstack = 0)
     : name{name}, opcodes{opcodes}, locals{locals}, maxstack{maxstack}
    {
    }

public:
    std::vector<OpCode> opcodes;
    std::string name;
    std::vector<Local> locals;
    size_t maxstack;
};