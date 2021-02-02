#pragma once
#include "OpBase.h"

class OpGetarr : public OpBase
{
public:
	OpGetarr() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 18;
};

