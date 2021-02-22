#pragma once
#include "OpBase.h"

class OpSetpd : public OpBase
{
public:
	OpSetpd() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 29;
};

