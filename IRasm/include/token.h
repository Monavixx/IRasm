#pragma once

#include <string>
#include <unordered_map>
#include <array>

using namespace std::string_literals;

/**
 * @brief class that stores information about tokens. It also defines the type of token
 */
class Token
{
public:
    /**
     * @brief enumeration of token types
     */
    enum class Type : unsigned char
    {
        WORD,
        OPEN_CURLY_BRACE,
        CLOSE_CURLY_BRACE,
        OPEN_SQUARE_BRACE,
        CLOSE_SQUARE_BRACE,
        OPEN_BRACE,
        CLOSE_BRACE,
        SEMICOLON,
        COLON,
        ASSEMBLY,
        INCLUDE_ASSEMBLY,
        LOCALS,
        MAXSTACK,
        OPCODE,
        COMMA
    };
    
    /**
     * @brief a constructor that takes a token and a line number. It automatically detects the type of token
     * 
     * \param word token word
     * \param numberLine line number on which the token is located
     */
    Token(std::string&& word, size_t numberLine) noexcept : word{std::move(word)}, numberLine{numberLine}
    {
        token_definition();
    }

    Token::Type get_type() const noexcept { return type; }
    size_t get_number_line() const noexcept { return numberLine; }
    std::string& get_word() noexcept { return word; }
    std::string get_word() const noexcept { return word; }

private:
    /**
     * @brief a method that determines the type of token. This method is called automatically in the constructor
     * 
     */
    void token_definition()
    {
        static std::unordered_map<std::string, Token::Type> tokenTypes {
            {";", Token::Type::SEMICOLON},
            {":", Token::Type::COLON},
            {"{", Token::Type::OPEN_CURLY_BRACE},
            {"}", Token::Type::CLOSE_CURLY_BRACE},
            {"[", Token::Type::OPEN_SQUARE_BRACE},
            {"]", Token::Type::CLOSE_SQUARE_BRACE},
            {"(", Token::Type::OPEN_BRACE},
            {")", Token::Type::CLOSE_BRACE},
            {"assembly", Token::Type::ASSEMBLY},
            {"include-assembly", Token::Type::INCLUDE_ASSEMBLY},
            {"locals", Token::Type::LOCALS},
            {"maxstack", Token::Type::MAXSTACK},
            {",", Token::Type::COMMA}
        };
        static const std::array opcodes {
            "pstr"s,
            "call"s
        };
        
        type = tokenTypes.contains(word) ? tokenTypes[word] : (std::find(begin(opcodes), end(opcodes), word) != end(opcodes) ? Token::Type::OPCODE : Token::Type::WORD);
    }

private:
    std::string word;
    size_t numberLine;
    Token::Type type;
};