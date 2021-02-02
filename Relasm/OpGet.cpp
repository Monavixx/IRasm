#include "OpGet.h"

QByteArray OpGet::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << id;

	return code;
}
