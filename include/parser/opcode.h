#pragma once

#include <string>

class OpCode
{
public:
    OpCode(std::string_view name) : name{name}
    {
    }

private:
    std::string name;
};