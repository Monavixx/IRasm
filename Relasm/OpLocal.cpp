#include "OpLocal.h"

QByteArray OpLocal::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << id << dataType;

	return code;
}
