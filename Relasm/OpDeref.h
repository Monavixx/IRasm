#pragma once
#include "OpBase.h"

class OpDeref : public OpBase
{
public:
	OpDeref() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 28;
};

