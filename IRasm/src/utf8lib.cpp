#include "..\include\utf8lib.h"

size_t utf8::size(const std::string& str) noexcept
{
    size_t sz = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if ((str[i] & 0b11000000) != 0b10000000) {
            ++sz;
        }
    }

    return sz;
}

std::string utf8::index(const std::string& str, size_t index)
{
    std::string res;
    size_t sz = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        if ((str[i] & 0b11000000) != 0b10000000) {
            ++sz;
        }
        if (sz == index) {
            res.push_back(str[i]);
        }
        else if (sz > index) {
            return res;
        }
    }
    res.shrink_to_fit();
    return res;
}
