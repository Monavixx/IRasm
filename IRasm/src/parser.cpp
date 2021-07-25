#include "parser/parser.h"

void Parser::parse()
{
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].get_type() == Token::Type::ASSEMBLY) {
            if (tokens[++i].get_type() == Token::Type::OPEN_CURLY_BRACE) {
                while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                    if (tokens[i + 1].get_type() == Token::Type::COLON) {
                        if (tokens[i].get_word() == "name") {
                            assembly.name = std::move(tokens[i + 2].get_word());
                            i += 2;
                        }
                        else if (tokens[i].get_word() == "version") {
                            assembly.version = std::move(tokens[i + 2].get_word());
                            i += 2;
                        }
                        else {
                            throw unexpected_character_exception{"unexpected character \"" + tokens[i].get_word() + "\" on line " + std::to_string(tokens[i].get_number_line())};
                        }
                    }
                    if (tokens.size() == i + 1) {
                        throw expected_character_exception{"expected character \"}\" on line " + std::to_string(tokens[i].get_number_line())};
                    }
                }
            }
            else {
                throw expected_character_exception{"expected character \"{\" on line " + std::to_string(tokens[i].get_number_line())};
            }
        }
        else if (tokens[i].get_type() == Token::Type::INCLUDE_ASSEMBLY) {
            if (tokens[++i].get_type() == Token::Type::OPEN_CURLY_BRACE) {
                while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                    includeAssembly.push_back(std::move(tokens[i].get_word()));

                    if (tokens.size() == i + 1) {
                        throw expected_character_exception{"expected character \"}\" on line " + std::to_string(tokens[i].get_number_line())};
                    }
                }
            }
            else {
                throw expected_character_exception{"expected character \"{\" on line " + std::to_string(tokens[i].get_number_line())};
            }
        }
        else if (tokens[i].get_type() == Token::Type::WORD) {
            std::string functionName = tokens[i].get_word();
            if (tokens[++i].get_type() == Token::Type::OPEN_BRACE) {
                std::vector<Parameter> parameters;
                while (tokens[++i].get_type() != Token::Type::CLOSE_BRACE) {
                    if (tokens[i + 1].get_type() == Token::Type::COLON) {
                        parameters.emplace_back(std::move(tokens[i].get_word()), std::move(tokens[i + 2].get_word()));
                        if (tokens[i + 3].get_type() == Token::Type::COMMA) {
                            i += 3;
                        }
                        else {
                            i += 2;
                        }
                    }
                }
                if (tokens[i].get_type() == Token::Type::CLOSE_BRACE) {
                    if (tokens[++i].get_type() == Token::Type::LOCALS) {
                        if (tokens[++i].get_type() == Token::Type::COLON) {
                            if (tokens[++i].get_type() == Token::Type::OPEN_CURLY_BRACE) {
                                std::vector<Local> locals;
                                while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                                    if (tokens[i + 1].get_type() == Token::Type::COLON) {
                                        locals.emplace_back(std::move(tokens[i].get_word()), std::move(tokens[i + 2].get_word()));
                                    }
                                }
                                if (tokens[++i].get_type() == Token::Type::MAXSTACK) {
                                    if (tokens[++i].get_type() == Token::Type::COLON) {
                                        size_t maxstack = boost::lexical_cast<size_t>(tokens[++i].get_word());
                                        if (tokens[++i].get_type() == Token::Type::OPEN_CURLY_BRACE) {
                                            std::vector<OpCode> opcodes;
                                            while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                                                if (tokens[i].get_type() == Token::Type::OPCODE) {
                                                    std::string opcodeName = tokens[i].get_word();
                                                    std::vector<Token> opcodeTokens;
                                                    while (tokens[++i].get_type() != Token::Type::OPCODE && tokens[i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                                                        opcodeTokens.push_back(tokens[i]);
                                                    }
                                                    opcodes.emplace_back(opcodeName, std::move(opcodeTokens));
                                                    --i;
                                                }
                                            }
                                            functions.emplace_back(functionName, std::move(parameters), std::move(opcodes), std::move(locals), maxstack);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}