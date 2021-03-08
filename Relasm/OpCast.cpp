#include "OpCast.h"

QByteArray OpCast::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << dataType;

	return code;
}
