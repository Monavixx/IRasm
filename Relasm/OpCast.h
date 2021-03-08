#pragma once
#include "OpBase.h"

class OpCast : public OpBase
{
public:
	OpCast(const QString& dataType) : dataType(dataType) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 25;
	QString dataType;
};

