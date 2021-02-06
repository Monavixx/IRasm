#pragma once
#include "OpBase.h"

class OpDiv : public OpBase
{
public:
	OpDiv() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 24;
};

