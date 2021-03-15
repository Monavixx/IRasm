#pragma once
#include "OpBase.h"

class OpSetfield : public OpBase
{
public:
	OpSetfield(const QString& name) : name(name) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 32;
	QString name;
};

