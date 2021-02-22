#include "OpSetpd.h"

QByteArray OpSetpd::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;

	return code;
}
