#pragma once
#include "OpBase.h"

class OpGet : public OpBase
{
public:
	OpGet(int id) : id(id) {}
	QByteArray Compile() override;

private:
	int id;
	static inline quint8 byteOpCode = 6;
};

