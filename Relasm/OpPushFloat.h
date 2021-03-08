#pragma once
#include "OpBase.h"

class OpPushFloat : public OpBase
{
public:
	OpPushFloat(int num, int fracPart) : num(num), fracPart(fracPart) {}
	QByteArray Compile() override;

private:
	int num, fracPart;

	static inline quint8 byteOpCode = 21;
};


