#pragma once

#include <string>

class Local
{
public:
    Local(std::string_view name, std::string_view dataType) : name{name}, dataType{dataType}
    {
    }

public:
    std::string name, dataType;
};