#pragma once
#include "OpBase.h"

class OpGetfield : public OpBase
{
public:
	OpGetfield(const QString& name) : name(name) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 31;
	QString name;
};

