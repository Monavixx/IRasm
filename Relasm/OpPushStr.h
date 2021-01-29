#pragma once
#include "OpBase.h"

class OpPushStr : public OpBase
{
public:
	OpPushStr(const QString& data);
	QByteArray Compile() override;

private:
	QString data;

	static inline quint8 byteOpCode = 7;
};

