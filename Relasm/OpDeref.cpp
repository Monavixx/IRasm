#include "OpDeref.h"

QByteArray OpDeref::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;

	return code;
}
