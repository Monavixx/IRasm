#pragma once
#include "OpBase.h"

class OpPushFloat : public OpBase
{
public:
	OpPushFloat(float data) : data(data) {}
	QByteArray Compile() override;

private:
	float data;

	static inline quint8 byteOpCode = 21;
};


