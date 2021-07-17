#pragma once

#include "exception/exception.h"

class lexer_exception : public all_exception
{
public:
    using all_exception::all_exception;
};

class expected_character_exception : public lexer_exception
{
public:
    using lexer_exception::lexer_exception;
};