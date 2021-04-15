#pragma once
#include "OpBase.h"
#include "Method.h"

class OpLocal : public OpBase
{
public:
	OpLocal(const QString& id, const QString& namespaceName, const QString& dataType, Method* method) : id(method->currentId), dataType(dataType), namespaceName(namespaceName)
	{
		this->method = method;
		method->names[id] = method->currentId;
		method->currentId++;
	}
	QByteArray Compile() override;

private:
	int id;
	QString namespaceName;
	QString dataType;
	static inline quint8 byteOpCode = 11;
};

