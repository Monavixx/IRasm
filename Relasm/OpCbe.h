#pragma once
#include "OpBase.h"

class OpCbe : public OpBase
{
public:
	OpCbe() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 38;
};

