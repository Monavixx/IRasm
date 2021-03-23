#pragma once
#include "OpBase.h"

class OpThis : public OpBase
{
public:
	OpThis() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 33;
};

