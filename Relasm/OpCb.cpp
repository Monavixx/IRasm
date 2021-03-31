#include "OpCb.h"

QByteArray OpCb::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;

	return code;
}
