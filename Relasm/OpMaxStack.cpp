#include "OpMaxStack.h"

QByteArray OpMaxStack::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << size;

	return code;
}
