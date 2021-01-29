#pragma once
#include <QtCore>

class Parameter
{
public:
	Parameter(const QString& dataType, const QString& name);
	QByteArray Compile() const;
private:
	QString dataType;
	QString name;
};

