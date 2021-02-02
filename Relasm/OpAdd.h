#pragma once
#include "OpBase.h"

class OpAdd : public OpBase
{
public:
	OpAdd() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 12;
};

