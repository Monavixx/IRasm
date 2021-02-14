#pragma once
#include "OpBase.h"

class OpMaxStack : public OpBase
{
public:
	OpMaxStack(int size) : size(size) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 26;
	int size;
};

