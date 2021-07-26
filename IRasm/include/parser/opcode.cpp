#include "opcode.h"
#include "function.h"

void OpCode::build(Buffer& outputStream, Function& function)
{
	balib::writeNum(outputStream, static_cast<byte>(metainfoInstructions[name].first));
	metainfoInstructions[name].second(outputStream, function, *this);
}