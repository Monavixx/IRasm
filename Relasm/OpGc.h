#pragma once
#include "OpBase.h"

class OpGc : public OpBase
{
public:
	OpGc() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 16;
};

