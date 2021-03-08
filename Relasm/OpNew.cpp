#include "OpNew.h"

OpNew::OpNew(const QString& isStd, const QString& dataType, const QList<QString>& parameters)
	:isStd(flagStd[isStd]), dataType(dataType), parameters(parameters)
{
}

QByteArray OpNew::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << quint8(isStd) << dataType;
	for (auto& item : parameters)
	{
		ds << item;
	}

	return code;
}
