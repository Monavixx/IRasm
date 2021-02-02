#pragma once
#include "OpBase.h"

class OpJmp : public OpBase
{
public:
	OpJmp(const QString& nameTag);
	QByteArray Compile() override;

private:
	QString nameTag;
	static inline quint8 byteOpCode = 14;
};

