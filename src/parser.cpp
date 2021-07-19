#include "parser/parser.h"

void Parser::parse()
{
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == Token::Type::ASSEMBLY) {
            if (tokens[++i].type == Token::Type::OPEN_CURLY_BRACE) {
                while (tokens[++i].type != Token::Type::CLOSE_CURLY_BRACE) {
                    if (tokens[i + 1].type == Token::Type::COLON) {
                        if (tokens[i].word == "name") {
                            assembly.name = std::move(tokens[i + 2].word);
                            i += 2;
                        }
                        if (tokens[i].word == "version") {
                            assembly.version = std::move(tokens[i + 2].word);
                            i += 2;
                        }
                    }
                }
            }
        }
        else if (tokens[i].type == Token::Type::INCLUDE_ASSEMBLY) {
            if (tokens[++i].type == Token::Type::OPEN_CURLY_BRACE) {
                while (tokens[++i].type != Token::Type::CLOSE_CURLY_BRACE) {
                    includeAssembly.push_back(std::move(tokens[i].word));
                }
            }
        }
        else if (tokens[i].type == Token::Type::WORD) {
            std::string functionName = tokens[i].word;
            if (tokens[++i].type == Token::Type::LOCALS) {
                if (tokens[++i].type == Token::Type::COLON) {
                    if (tokens[++i].type == Token::Type::OPEN_CURLY_BRACE) {
                        std::vector<Local> locals;
                        while (tokens[++i].type != Token::Type::CLOSE_CURLY_BRACE) {
                            if (tokens[i + 1].type == Token::Type::COLON) {
                                locals.emplace_back(std::move(tokens[i].word), std::move(tokens[i + 2].word));
                            }
                        }
                        if (tokens[++i].type == Token::Type::MAXSTACK) {
                            if (tokens[++i].type == Token::Type::COLON) {
                                size_t maxstack = boost::lexical_cast<size_t>(tokens[++i].word);
                                if (tokens[++i].type == Token::Type::OPEN_CURLY_BRACE) {
                                    std::vector<OpCode> opcodes;
                                    while (tokens[++i].type != Token::Type::CLOSE_CURLY_BRACE) {
                                        if (tokens[i].type == Token::Type::OPCODE) {
                                            std::string opcodeName = tokens[i].word;
                                            std::vector<Token> opcodeTokens;
                                            while (tokens[++i].type != Token::Type::OPCODE && tokens[i].type != Token::Type::CLOSE_CURLY_BRACE) {
                                                opcodeTokens.push_back(tokens[i]);
                                            }
                                            opcodes.emplace_back(opcodeName, opcodeTokens);
                                            --i;
                                        }
                                    }
                                    functions.emplace_back(functionName, opcodes, locals, maxstack);
                                }
                            }
                        }
                    }
                }
            }
            
        }
    }
}