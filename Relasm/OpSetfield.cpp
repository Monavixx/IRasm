#include "OpSetfield.h"

QByteArray OpSetfield::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << name;

	return code;
}
