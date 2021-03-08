#include "OpRef.h"

QByteArray OpRef::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << dataType;

	return code;
}
