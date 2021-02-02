#pragma once
#include "OpBase.h"

class OpNewarr : public OpBase
{
public:
	OpNewarr(const QString& dataType) : dataType(dataType) {}
	QByteArray Compile() override;

private:
	QString dataType;
	static inline quint8 byteOpCode = 17;
};

