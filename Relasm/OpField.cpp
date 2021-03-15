#include "OpField.h"

QByteArray OpField::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << quint8(accessModifier) << quint8(isStatic) << dataType << declClassName << name;

	return code;
}