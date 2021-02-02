#include "OpPushBool.h"

QByteArray OpPushBool::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << (quint8)data;

	return code;
}
