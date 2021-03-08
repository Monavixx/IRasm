#pragma once
#include "OpBase.h"

class OpNew : public OpBase
{
public:
	OpNew(const QString& dataType, const QList<QString>& parameters);
	QByteArray Compile() override;

private:
	QString dataType;
	QList<QString> parameters;

	static inline quint8 byteOpCode = 2;
};

