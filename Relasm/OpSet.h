#pragma once
#include "OpBase.h"

class OpSet : public OpBase
{
public:
	OpSet(int id) : id(id) {}
	QByteArray Compile() override;

private:
	int id;
	static inline quint8 byteOpCode = 10;
};

