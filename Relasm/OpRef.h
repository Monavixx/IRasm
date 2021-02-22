#pragma once
#include "OpBase.h"

class OpRef : public OpBase
{
public:
	OpRef(const QString& dataType) : dataType(dataType) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 27;
	QString dataType;
};

