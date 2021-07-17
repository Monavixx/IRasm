#pragma once

#include <array>
#include <sstream>

using ubyte = unsigned char;

/**
 * @brief library namespace for working with byte array
 * 
 */
namespace balib
{
    template<typename T>
    concept OutputStream = requires(T t) { t.write((char*)nullptr, std::streamsize{}); };

    /**
     * @brief Splits a number into an array of bytes
     * 
     * @param[in] num the number to be converted into a byte array
     * @return the number passed in parameters, as an array of bytes
     */
    template<class NumType>
    constexpr std::array<ubyte, sizeof(NumType)> numToBytes(NumType num) noexcept
    {
        std::array<ubyte, sizeof(NumType)> arrayOfByte;
        for (ubyte i = 0; i < sizeof(NumType); i++)
            arrayOfByte[sizeof(NumType) - 1 - i] = (num >> (i * 8));
        return arrayOfByte;
    }

    /**
     * @brief calls the parameter data method data() and writes the result to the stream
     * 
     * @param[in] outputStream the stream to which the data is written
     * @param[in] data data structure that has a method data(), the result of which will be written to the stream
     */
    void writeStdArray(auto& outputStream, const auto& data)
    {
        outputStream.write(reinterpret_cast<const char*>(data.data()), sizeof(data[0]) * data.size());
    }
};