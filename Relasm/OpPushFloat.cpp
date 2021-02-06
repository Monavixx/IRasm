#include "OpPushFloat.h"

QByteArray OpPushFloat::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << data;

	return code;
}
