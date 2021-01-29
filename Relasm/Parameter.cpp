#include "Parameter.h"

Parameter::Parameter(const QString& dataType, const QString& name) : dataType(dataType), name(name)
{
}

QByteArray Parameter::Compile() const
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);
	ds << dataType.toUtf8();
	ds << name.toUtf8();
	return code;
}
