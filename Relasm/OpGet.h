#pragma once
#include "OpBase.h"
#include "Exit.h"
#include "Method.h"

class OpGet : public OpBase
{
public:
	OpGet(const QString& id, Method* method)
	{
		if (!method->names.contains(id))
			Exit("get: variable " + id + " not found");
		this->id = method->names[id];
	}
	QByteArray Compile() override;

private:
	int id;
	static inline quint8 byteOpCode = 6;
};

