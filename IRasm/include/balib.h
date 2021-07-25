#pragma once

#include <array>
#include <sstream>

using byte = unsigned char;

/**
 * @brief library namespace for working with byte array
 * 
 */
namespace balib
{
    /**
     * @brief splits a number into an array of bytes
     * 
     * @tparam NumType data type of the number to be converted
     * @param num the number to be converted into a byte array
     * @return the number passed in parameters, as an array of bytes
     */
    template<class NumType>
    constexpr std::array<byte, sizeof(NumType)> numToBytes(const NumType num) noexcept
    {
        std::array<byte, sizeof(NumType)> arrayOfByte;
        for (byte i = 0; i < sizeof(NumType); i++)
            arrayOfByte[sizeof(NumType) - 1 - i] = (num >> (i * 8));
        return arrayOfByte;
    }

    /**
     * @brief calls the parameter data method data() and writes the result to the stream
     * 
     * @param outputStream the stream to which the data is written
     * @param data data structure that has a method data(), the result of which will be written to the stream
     */
    void writeStdArray(auto& outputStream, const auto& data)
    {
        outputStream.write(reinterpret_cast<const char*>(data.data()), sizeof(data[0]) * data.size());
    }

    /**
     * @brief converts a number to an array of bytes and then writes it to the output stream
     * 
     * @param outputStream the stream to which the resulting byte array will be written
     * @param num the number to be converted to a byte array
     */
    void writeNum(auto& outputStream, const auto num)
    {
        balib::writeStdArray(outputStream, balib::numToBytes(num));
    }

    void writeString(auto& outputStream, const std::string& str)
    {
        balib::writeNum(outputStream, (int)str.size());
        balib::writeStdArray(outputStream, str);
    }
};
