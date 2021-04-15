#pragma once
#include "OpBase.h"
#include "IsStatic.h"
#include "Parameter.h"

class OpCallMethod : public OpBase
{
public:
	OpCallMethod(const QString& isStatic, const QString& namespaceName, const QString& declClass, const QString& name, const QList<Parameter>& parameters);
	QByteArray Compile() override;

private:
	IsStatic isStatic;
	QString namespaceName;
	QString declClass;
	QString name;
	QList<Parameter> parameters;

	static inline quint8 byteOpCode = 5;
	static inline QHash<QString, IsStatic> flagStatic = {
		{"instance", INSTANCE},
		{"static", STATIC}
	};
};

