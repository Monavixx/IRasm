#pragma once
#include "OpBase.h"

class OpCl : public OpBase
{
public:
	OpCl() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 35;
};

