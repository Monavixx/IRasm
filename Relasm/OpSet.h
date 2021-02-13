#pragma once
#include "OpBase.h"
#include "Exit.h"
#include "Method.h"

class OpSet : public OpBase
{
public:
	OpSet(const QString& id, Method* method)
	{
		this->method = method;
		if (!method->names.contains(id))
			Exit("set: variable " + id + " not found");
		this->id = method->names[id];
	}
	QByteArray Compile() override;

private:
	int id;
	static inline quint8 byteOpCode = 10;
};

