#include "OpLocal.h"

QByteArray OpLocal::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << id << namespaceName<< dataType;

	return code;
}
