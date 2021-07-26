#include "parser/parser.h"

void Parser::parse()
{
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].get_type() == Token::Type::ASSEMBLY) {
            if (tokens[++i].get_type() == Token::Type::OPEN_CURLY_BRACE) {
                while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                    if (tokens[i + 1].get_type() == Token::Type::COLON) {
                        if (tokens[i].get_word() == "name") {
                            std::string tmp = std::move(tokens[i + 2].get_word());
                            assembly.name = std::string(tmp.begin() + 1, tmp.end() - 1);
                            i += 2;
                        }
                        else if (tokens[i].get_word() == "version") {
                            std::string tmp = std::move(tokens[i + 2].get_word());
                            assembly.version = std::string(tmp.begin() + 1, tmp.end() - 1);
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
                    if (tokens[i + 1].get_type() == Token::Type::COMMA) {
                        ++i;
                    }
                    else if (tokens[i + 1].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                        throw expected_character_exception{ "expected character \",\" on line " + std::to_string(tokens[i].get_number_line()) };
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
        else if (tokens[++i].get_type() == Token::Type::OPEN_BRACE) {
            std::string functionName = tokens[i - 1].get_word();
            std::unordered_map<std::string, Parameter> parameters;

            while (tokens[++i].get_type() != Token::Type::CLOSE_BRACE) {
                if (tokens[i + 1].get_type() == Token::Type::COLON) {
                    parameters[std::move(tokens[i + 2].get_word())] = Parameter(std::move(tokens[i].get_word()));

                    if (tokens[i + 3].get_type() == Token::Type::COMMA) {
                        i += 3;
                    }
                    else if (tokens[i + 3].get_type() != Token::Type::CLOSE_BRACE) {
                        throw expected_character_exception{ "expected character \",\" on line " + std::to_string(tokens[i].get_number_line()) };
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
                            std::unordered_map<std::string, Local> locals;

                            while (tokens[++i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                                if (tokens[i + 1].get_type() == Token::Type::COLON) {
                                    locals[std::move(tokens[i + 2].get_word())] = Local(std::move(tokens[i].get_word()));
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
                                                size_t opcodeNumberLine = tokens[i].get_number_line();
                                                std::vector<Token> opcodeTokens;
                                                while (tokens[++i].get_type() != Token::Type::OPCODE && tokens[i].get_type() != Token::Type::CLOSE_CURLY_BRACE) {
                                                    opcodeTokens.push_back(tokens[i]);
                                                }
                                                opcodes.emplace_back(opcodeName, opcodeNumberLine, std::move(opcodeTokens));
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