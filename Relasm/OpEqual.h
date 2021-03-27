#pragma once
#include "OpBase.h"

class OpEqual : public OpBase
{
public:
	OpEqual() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 34;
};

