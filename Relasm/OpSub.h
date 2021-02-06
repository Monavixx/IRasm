#pragma once
#include "OpBase.h"

class OpSub : public OpBase
{
public:
	OpSub() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 22;
};

