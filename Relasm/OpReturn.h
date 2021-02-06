#pragma once
#include "OpBase.h"

class OpReturn : public OpBase
{
public:
	OpReturn() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 9;
};

