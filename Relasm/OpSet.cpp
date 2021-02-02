#include "OpSet.h"


QByteArray OpSet::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << id;

	return code;
}
