#pragma once
#include "OpBase.h"

class OpCb : public OpBase
{
public:
	OpCb() {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 36;
};

