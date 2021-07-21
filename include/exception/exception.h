#pragma once

#include <exception>
#include <string>

class all_exception : public std::exception
{
public:
    all_exception(auto&& msg) : msg{std::forward<decltype(msg)>(msg)}
    {
    }

    std::string get_message() const noexcept
    {
        return msg;
    }
private:
    std::string msg;
};

class unexpected_character_exception : public all_exception
{
public:
    using all_exception::all_exception;
};

class expected_character_exception : public all_exception
{
public:
    using all_exception::all_exception;
};