#include "OpCallMethod.h"

OpCallMethod::OpCallMethod(const QString& isStd, const QString& isStatic, const QString declClass, const QString name, const QList<QString>& parameters)
	:isStatic(flagStatic[isStatic]), isStd(flagStd[isStd]), declClass(declClass), name(name), parameters(parameters)
{
}

QByteArray OpCallMethod::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;
	ds << quint8(isStd);
	ds << quint8(isStatic);
	ds << declClass;
	ds << name;
	ds << int(parameters.size());
	for (auto& item : parameters)
	{
		ds << item;
	}

	return code;
}
