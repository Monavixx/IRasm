#pragma once

#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

#include "../token.h"
#include "instruction_handlers.h"

/**
 * @brief a class that stores information about an instruction in a function
 */
class OpCode
{
public:
    /**
     * @brief a constructor that accepts all information
     *
     * @param name instruction name
     * @param tokens list of tokens owned by the instruction
     */
    OpCode(std::string_view name, size_t numberLine, std::vector<Token>&& tokens) : name{ name }, tokens{ std::move(tokens) }, numberLine{numberLine}
    {
    }

    std::string& get_name() noexcept { return name; }
    size_t get_number_line() const noexcept { return numberLine; }
    std::vector<Token>& get_tokens() noexcept { return tokens; }

    void build(Buffer& outputStream, class Function& function);

private:
    std::string name;
    std::vector<Token> tokens;
    size_t numberLine;


public:
    enum class Type : unsigned char
    {
        PSTR = 1,
        CALL
    };

    static inline std::unordered_map<std::string, std::pair<Type, std::function<void(Buffer&, class Function&, OpCode&)>>> metainfoInstructions = {
        {"pstr", {Type::PSTR, ih::pstr}},
        {"call", {Type::CALL, ih::call}},
    };
};