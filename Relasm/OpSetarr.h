#pragma once
#include "OpBase.h"

class OpSetarr : public OpBase
{
public:
	OpSetarr() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 19;
};

