#include "OpNewarr.h"

QByteArray OpNewarr::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << dataType.toUtf8();

	return code;
}
