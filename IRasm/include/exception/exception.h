#pragma once

#include <exception>
#include <string>


using namespace std::string_literals;

/**
 * @brief generic exception class taking std::string
 */
class all_exception : public std::exception
{
public:
    /**
     * @brief the constructor setting the error message
     * 
     * \param msg error message
     */
    all_exception(std::string&& msg) : msg{ std::move(msg) }
    {
    }

    /**
     * @brief method that returns an error message
     * 
     * \return error message
     */
    const char* what() const noexcept override
    {
        return msg.c_str();
    }
private:
    std::string msg;
};

/**
 * @brief the class of exceptions that are thrown when an unexpected character is encountered
 */
class unexpected_character_exception : public all_exception
{
public:
    unexpected_character_exception(std::string&& msg)
        : all_exception{ "unexpected_character_exception: "s + move(msg) }
    {
    }
};

/**
 * @brief the class of exceptions that are thrown when the program does not find the expected character
 */
class expected_character_exception : public all_exception
{
public:
    expected_character_exception(std::string&& msg)
        : all_exception( "expected_character_exception: "s + move(msg) )
    {
    }
};

class syntax_instruction_error_exception : public all_exception
{
public:
    syntax_instruction_error_exception(std::string&& msg)
        : all_exception("syntax_instruction_error_exception: "s + move(msg))
    {
    }
};