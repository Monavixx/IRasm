#pragma once
#include "OpBase.h"

class OpCe : public OpBase
{
public:
	OpCe() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 34;
};

