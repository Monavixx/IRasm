#include "OpGetfield.h"

QByteArray OpGetfield::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << name;

	return code;
}
