#include "OpNew.h"

OpNew::OpNew(const QString& namespaceName, const QString& dataType, const QList<Parameter>& parameters)
	: dataType(dataType), parameters(parameters), namespaceName(namespaceName)
{
}

QByteArray OpNew::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << namespaceName << dataType << quint32(parameters.size());
	for (auto& item : parameters)
	{
		ds << item.GetNamespaceName() << item.GetDataType();
	}
	return code;
}
