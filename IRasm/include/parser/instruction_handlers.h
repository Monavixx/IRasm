#pragma once

#include <fstream>
#include "buffer.h"
#include "exception/exception.h"

class Function;
class OpCode;

namespace ih
{
	void pstr(Buffer& outputStream, Function& func, OpCode& opcode);
	void call(Buffer& outputStream, Function& func, OpCode& opcode);
};