#pragma once
#include "OpBase.h"

class OpJmpif : public OpBase
{
public:
	OpJmpif(const QString& nameTag);
	QByteArray Compile() override;

private:
	QString nameTag;
	static inline quint8 byteOpCode = 15;
};

