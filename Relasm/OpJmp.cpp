#include "OpJmp.h"

OpJmp::OpJmp(const QString& nameTag) : nameTag(nameTag)
{
}

QByteArray OpJmp::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << tags->operator[](nameTag);

	return code;
}
