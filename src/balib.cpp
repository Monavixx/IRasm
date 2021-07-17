#include "balib.h"

unsigned char* balib::intToBytes(int paramInt)
{
    unsigned char* arrayOfByte = new unsigned char[4];
    for (int i = 0; i < 4; i++)
        arrayOfByte[3 - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}