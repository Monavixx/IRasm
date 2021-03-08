#include "OpCast.h"

QByteArray OpCast::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << (quint8)isStd << dataType;

	return code;
}
