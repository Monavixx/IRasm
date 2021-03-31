#pragma once
#include "OpBase.h"

class OpCle : public OpBase
{
public:
	OpCle() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 37;
};

