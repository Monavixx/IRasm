#include "OpCallMethod.h"

OpCallMethod::OpCallMethod(const QString& isStatic, const QString& namespaceName, const QString& declClass, const QString& name, const QList<Parameter>& parameters)
	:isStatic(flagStatic[isStatic]), declClass(declClass), name(name), parameters(parameters), namespaceName(namespaceName)
{
}

QByteArray OpCallMethod::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;
	ds << quint8(isStatic);
	ds << namespaceName;
	ds << declClass;
	ds << name;
	ds << int(parameters.size());
	for (auto& item : parameters)
	{
		ds << item.GetNamespaceName() << item.GetDataType();
	}

	return code;
}
