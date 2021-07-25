#pragma once

#include <string>

/**
 * @brief class describing local variables in functions
 */
class Local
{
public:
    /**
     * @brief a constructor that accepts all information
     * 
     * @param dataType local variable data type
     * @param name local variable name
     */
    Local(std::string_view dataType, std::string_view name) : name{name}, dataType{dataType}
    {
    }

private:
    std::string name, dataType;
};