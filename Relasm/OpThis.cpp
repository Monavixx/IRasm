#include "OpThis.h"

QByteArray OpThis::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;

	return code;
}
