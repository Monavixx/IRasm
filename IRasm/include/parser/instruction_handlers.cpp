#include "instruction_handlers.h"
#include "function.h"
#include <fmt/core.h>

void ih::pstr(std::ofstream& outputStream, Function& func, OpCode& opcode)
{
	if (opcode.get_tokens().size() == 1) {
		std::string& txt = opcode.get_tokens()[0].get_word();
		if (txt.starts_with('"') && txt.ends_with('"')) {
			balib::writeString(outputStream, std::string(txt.begin() + 1, txt.end() - 1));
		}
	}
	else {
		throw syntax_instruction_error_exception("pstr must take 1 argument! on line " + std::to_string(opcode.get_number_line()));
	}
}

void ih::call(std::ofstream& outputStream, Function& func, OpCode& opcode)
{
	auto& tokens = opcode.get_tokens();
	if (tokens[0].get_type() == Token::Type::OPEN_SQUARE_BRACE) {
		balib::writeString(outputStream, tokens[1].get_word()); // assembly name

		if (tokens[2].get_type() == Token::Type::CLOSE_SQUARE_BRACE) {
			balib::writeString(outputStream, tokens[3].get_word()); // function name

			if (tokens[4].get_type() == Token::Type::OPEN_BRACE) {
				std::vector<std::string> parameters;

				size_t i = 5;
				while (tokens[i].get_type() != Token::Type::CLOSE_BRACE) {
					parameters.push_back(std::move(tokens[i++].get_word()));
				}

				balib::writeNum(outputStream, parameters.size());
				for (auto& item : parameters) {
					balib::writeString(outputStream, item);
				}
			}
		}
	}
}
