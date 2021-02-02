#include "OpNew.h"

OpNew::OpNew(const QString& isStd, const QString& dataType, const QList<QString>& parameters)
	:isStd(flagStd[isStd]), dataType(dataType), parameters(parameters)
{
}

QByteArray OpNew::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << quint8(isStd) << dataType.toUtf8();
	for (auto& item : parameters)
	{
		ds << item.toUtf8();
	}

	return code;
}
