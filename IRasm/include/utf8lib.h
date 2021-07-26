#pragma once

#include <string>

namespace utf8
{
    size_t size(const std::string& str) noexcept;
    std::string index(const std::string& str, size_t index);
}