#pragma once
#include "OpBase.h"
#include "OpLocal.h"
#include "Exit.h"

class OpGet : public OpBase
{
public:
	OpGet(const QString& id)
	{
		if (!OpLocal::names.contains(id))
			Exit("get: variable " + id + " not found");
		this->id = OpLocal::names[id];
	}
	QByteArray Compile() override;

private:
	int id;
	static inline quint8 byteOpCode = 6;
};
