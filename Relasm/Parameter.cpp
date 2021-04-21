#include "Parameter.h"

Parameter::Parameter(const QString& namespaceName, const QString& dataType, const QString& name) : namespaceName(namespaceName), dataType(dataType), name(name)
{
}

QByteArray Parameter::Compile() const
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);
	ds << namespaceName;
	ds << dataType;
	ds << name;
	return code;
}
