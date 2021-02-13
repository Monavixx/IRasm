#pragma once
#include <QtCore>

class Parameter
{
public:
	Parameter(const QString& dataType, const QString& name);
	QByteArray Compile() const;

	QString GetDataType() { return dataType; }
	QString GetName() { return name; }
private:
	QString dataType;
	QString name;
};

