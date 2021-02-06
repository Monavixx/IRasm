#pragma once
#include "OpBase.h"

class OpMul : public OpBase
{
public:
	OpMul() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 23;
};

