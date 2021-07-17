#pragma once

#include <string>


class Token
{
public:
    enum class Type : unsigned char
    {
        WORD,
        OPEN_CURLY_BRACE,
        CLOSE_CURLY_BRACE,
        OPEN_SQUARE_BRACE,
        CLOSE_SQUARE_BRACE,
        SEMICOLON,
        COLON
    };

    Token(auto&& word, size_t numberLine) noexcept : word{std::forward<decltype(word)>(word)}, numberLine{numberLine}
    {
        token_definition();
    }

    void token_definition()
    {
        if (word == ";") {
            type = Token::Type::SEMICOLON;
        }
        else if (word == ":") {
            type = Token::Type::COLON;
        }
        else if (word == "{") {
            type = Token::Type::OPEN_CURLY_BRACE;
        }
        else if (word == "}") {
            type = Token::Type::CLOSE_CURLY_BRACE;
        }
        else if (word == "[") {
            type = Token::Type::OPEN_SQUARE_BRACE;
        }
        else if (word == "]") {
            type = Token::Type::CLOSE_SQUARE_BRACE;
        }
        else {
            type = Token::Type::WORD;
        }
    }

public:
    std::string word;
    size_t numberLine;
    Token::Type type;
};