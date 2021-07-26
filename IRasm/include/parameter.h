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
	Parameter(std::string_view dataType) : dataType(dataType), id(0)
	{
	}

	Parameter() = default;

	void set_id(size_t id) noexcept { this->id = id; }
	size_t get_id() const noexcept { return id; }
	std::string& get_data_type() noexcept { return dataType; }

private:
	std::string dataType;
	size_t id;
};
