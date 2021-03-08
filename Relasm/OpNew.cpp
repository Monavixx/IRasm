#include "OpNew.h"

OpNew::OpNew(const QString& dataType, const QList<QString>& parameters)
	: dataType(dataType), parameters(parameters)
{
}

QByteArray OpNew::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << dataType;
	for (auto& item : parameters)
	{
		ds << item;
	}

	return code;
}
