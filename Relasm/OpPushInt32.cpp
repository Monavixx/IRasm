#include "OpPushInt32.h"

OpPushInt32::OpPushInt32(int data) : data(data)
{
}

QByteArray OpPushInt32::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << data;

	return code;
}
