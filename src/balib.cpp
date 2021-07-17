#include "balib.h"


std::array<rbyte, 4> balib::intToBytes(int paramInt) noexcept
{
    std::array<rbyte, 4> arrayOfByte;
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}