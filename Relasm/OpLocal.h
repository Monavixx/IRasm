#pragma once
#include "OpBase.h"
#include "Method.h"

class OpLocal : public OpBase
{
public:
	OpLocal(const QString& id, const QString& dataType, Method* method) : id(method->currentId), dataType(dataType)
	{
		this->method = method;
		method->names[id] = method->currentId;
		method->currentId++;
	}
	QByteArray Compile() override;

private:
	int id;
	QString dataType;
	static inline quint8 byteOpCode = 11;
};

