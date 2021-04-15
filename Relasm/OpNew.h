#pragma once
#include "OpBase.h"
#include "Parameter.h"

class OpNew : public OpBase
{
public:
	OpNew(const QString& namespaceName, const QString& dataType, const QList<Parameter>& parameters);
	QByteArray Compile() override;

private:
	QString dataType;
	QString namespaceName;
	QList<Parameter> parameters;

	static inline quint8 byteOpCode = 2;
};

