#pragma once
#include "OpBase.h"

class OpLocal : public OpBase
{
public:
	OpLocal(int id, const QString& dataType) : id(id), dataType(dataType){}
	QByteArray Compile() override;

private:
	int id;
	QString dataType;
	static inline quint8 byteOpCode = 11;
};

