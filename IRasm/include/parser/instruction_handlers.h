#pragma once

#include <fstream>
#include "exception/exception.h"

class Function;
class OpCode;

namespace ih
{
	void pstr(std::ofstream& outputStream, Function& func, OpCode& opcode);
	void call(std::ofstream& outputStream, Function& func, OpCode& opcode);
};