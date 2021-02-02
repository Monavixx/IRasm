#include "OpJmpif.h"

OpJmpif::OpJmpif(const QString& nameTag) : nameTag(nameTag)
{
}

QByteArray OpJmpif::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << tags->operator[](nameTag);

	return code;
}
