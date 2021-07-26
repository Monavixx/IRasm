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
    Local(std::string_view dataType) : dataType{dataType}, id{0}
    {
    }

    Local() = default;

    void set_id(size_t id) noexcept { this->id = id; }
    size_t get_id() const noexcept { return id; }
    std::string& get_data_type() noexcept { return dataType; }

private:
    std::string dataType;
    size_t id;
};