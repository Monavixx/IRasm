#pragma once

#include <string>
#include <unordered_map>

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
        COLON,
        ASSEMBLY,
        INCLUDE_ASSEMBLY,
        LOCALS,
        MAXSTACK,
        OPCODE
    };

    Token(auto&& word, size_t numberLine) noexcept : word{std::forward<decltype(word)>(word)}, numberLine{numberLine}
    {
        token_definition();
    }

    void token_definition()
    {
        static std::unordered_map<std::string, Token::Type> tokenTypes {
            {";", Token::Type::SEMICOLON},
            {":", Token::Type::COLON},
            {"{", Token::Type::OPEN_CURLY_BRACE},
            {"}", Token::Type::CLOSE_CURLY_BRACE},
            {"[", Token::Type::OPEN_SQUARE_BRACE},
            {"]", Token::Type::CLOSE_SQUARE_BRACE},
            {"assembly", Token::Type::ASSEMBLY},
            {"include-assembly", Token::Type::INCLUDE_ASSEMBLY},
            {"locals", Token::Type::LOCALS},
            {"maxstack", Token::Type::MAXSTACK}
        };
        static std::vector<std::string> opcodes {
            "pstr",
            "call"
        };
        
        type = tokenTypes.contains(word) ? tokenTypes[word] : (std::find(begin(opcodes), end(opcodes), word) != end(opcodes) ? Token::Type::OPCODE : Token::Type::WORD);
    }

public:
    std::string word;
    size_t numberLine;
    Token::Type type;
};