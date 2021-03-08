#pragma once
#include "OpBase.h"
#include "IsStatic.h"

class OpCallMethod : public OpBase
{
public:
	OpCallMethod(const QString& isStatic, const QString declClass, const QString name, const QList<QString>& parameters);
	QByteArray Compile() override;

private:
	IsStatic isStatic;
	QString declClass;
	QString name;
	QList<QString> parameters;

	static inline quint8 byteOpCode = 5;
	static inline QHash<QString, IsStatic> flagStatic = {
		{"instance", INSTANCE},
		{"static", STATIC}
	};
};

