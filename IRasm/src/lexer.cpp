#include "lexer.h"

std::vector<Token> Lexer::separation()
{
    constexpr auto sepsContains = [seps = std::array{
        ';',
        ':',
        '{',
        '}',
        '[',
        ']',
        ')',
        '(',
        ','}
    ](char sep) constexpr {
        return std::find(begin(seps), end(seps), sep) != end(seps);
    };

    code.erase(std::remove(code.begin(), code.end(), '\r'), code.end());

    std::vector<Token> tokens;
    size_t currentLine = 1,
        amountOpenCurlyBraces = 0,
        amountOpenSquareBraces = 0,
        lastLineOpenQuote = 1;
    std::string temp;
    bool isOpenQuote = false;
    unsigned char amountSlash = 0;
    bool isComment = false;
    
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i] == '\n') {
            ++currentLine;
            amountSlash = 0;
            isComment = false;
        }
        else if (code[i] == '/' && !isOpenQuote) {
            ++amountSlash;
            if (amountSlash == 2) {
                isComment = true;
            }
        }
        if (!isComment)
        {
            if (sepsContains(code[i]) && !isOpenQuote) {
                if (!temp.empty()) {
                    tokens.emplace_back(move(temp), currentLine);
                }
                tokens.emplace_back(std::string(1, code[i]), currentLine);

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
                    if (amountOpenSquareBraces != 0) {
                        throw expected_character_exception{ "expected character \"]\" on line " + std::to_string(currentLine) };
                    }
                }
                else if (code[i] == ';') {
                    if (amountOpenSquareBraces != 0) {
                        throw expected_character_exception{ "expected character \"]\" on line " + std::to_string(currentLine) };
                    }
                }
                continue;
            }
            else if ((code[i] == ' ' || code[i] == '\t' || code[i] == '\n') && !isOpenQuote) {
                if (!temp.empty()) {
                    tokens.emplace_back(std::move(temp), currentLine);
                }
                continue;
            }
            else if (code[i] == '"') {
                bool isntempt = !temp.empty();
                temp += '"';
                isOpenQuote = !isOpenQuote;
                if (isOpenQuote) {
                    lastLineOpenQuote = currentLine;
                    if (isntempt) {
                        tokens.emplace_back(std::move(temp), currentLine);
                    }
                }
                continue;
            }
            else if (!(code[i] == '/' && !isOpenQuote)) {
                temp += code[i];
            }
        }
    }
    if (isOpenQuote) {
        throw expected_character_exception{"expected symbol '\"' on line " + std::to_string(lastLineOpenQuote)};
    }

    return tokens;
}