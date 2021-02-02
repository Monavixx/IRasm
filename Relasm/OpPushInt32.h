#pragma once
#include "OpBase.h"

class OpPushInt32 : public OpBase
{
public:
	OpPushInt32(int data);
	QByteArray Compile() override;

private:
	int data;

	static inline quint8 byteOpCode = 8;
};

