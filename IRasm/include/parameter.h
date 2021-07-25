#pragma once

#include <string>

/**
 * @brief class describing the function parameter
 */
class Parameter
{
public:
	/**
	 * @brief a constructor that accepts all information
	 * 
	 * @param dataType parameter data type
	 * @param name parameter name
	 */
	Parameter(std::string_view dataType, std::string_view name) : dataType(dataType), name(name)
	{
	}

private:
	std::string dataType, name;
};
