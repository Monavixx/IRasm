#pragma once
#include "OpBase.h"

class OpDup : public OpBase
{
public:
	OpDup() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 13;
};

