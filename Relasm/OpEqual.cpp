#include "OpEqual.h"

QByteArray OpEqual::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;

	return code;
}
