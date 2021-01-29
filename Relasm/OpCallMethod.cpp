#include "OpCallMethod.h"

OpCallMethod::OpCallMethod(const QString& isStatic, const QString& isStd, const QString& dataType, const QString declClass, const QString name, const QList<QString>& parameters)
	:isStatic(flagStatic[isStatic]), isStd(flagStd[isStd]), dataType(dataType), declClass(declClass), name(name), parameters(parameters)
{
}

QByteArray OpCallMethod::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;
	ds << quint8(isStatic);
	ds << quint8(isStd);
	ds << dataType.toUtf8();
	ds << declClass.toUtf8();
	ds << name.toUtf8();
	ds << int(parameters.size());
	for (auto& item : parameters)
	{
		ds << item.toUtf8();
	}

	return code;
}
