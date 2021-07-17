#pragma once

#include <array>

using rbyte = unsigned char;

/**
 * @brief library namespace for working with byte array
 * 
 */
namespace balib
{
    /**
     * @brief Splits a number into an array of bytes
     * 
     * @param[in] paramInt the number to be converted into a byte array
     * @return the number passed in parameters, as an array of bytes
     */
    std::array<rbyte, 4> intToBytes(int paramInt) noexcept;
};