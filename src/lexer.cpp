#include "lexer.h"

std::vector<Token> Lexer::separation() const noexcept
{
    constexpr std::array<char, 6> seps {
        ';',
        ':',
        '{',
        '}',
        '[',
        ']'
    };
    constexpr auto sepsContains{[seps] (char sep) constexpr {
        return std::find(begin(seps), end(seps), sep) != end(seps);
    }};
    
    std::vector<Token> tokens;
    size_t currentLine = 1,
        amountOpenCurlyBraces = 0,
        amountOpenSquareBraces = 0;
    std::string temp;
    bool isOpenQuote = false;
    
    for (size_t i = 0; i < code.size(); ++i) {
        if (sepsContains(code[i]) && !isOpenQuote) {
            tokens.emplace_back(move(temp), currentLine);
            tokens.emplace_back(std::string{code[i]}, currentLine);

            if (code[i] == '[') {
                ++amountOpenSquareBraces;
            }
            else if (code[i] == ']') {
                --amountOpenSquareBraces;
            }
            else if (code[i] == '{') {
                ++amountOpenCurlyBraces;
            }
            else if (code[i] == '}') {
                --amountOpenCurlyBraces;
            }
            continue;
        }
        else if ((code[i] == ' ' || code[i] == '\t' || code[i] == '\n') && !isOpenQuote) {
            if (!temp.empty()) {
                tokens.emplace_back(move(temp), currentLine);
            }
            if (code[i] == '\n') {
                ++currentLine;
            }
            continue;
        }
        else if (code[i] == '"') {
            isOpenQuote = !isOpenQuote;
            if (isOpenQuote) {
                tokens.emplace_back(move(temp), currentLine);
            }
            continue;
        }
        else {
            temp += code[i];
        }
    }

    for(auto& item : tokens)
    {
        std::cout  << '[' << item.numberLine << ']' << item.word << '\n';
    }

    return tokens;
}