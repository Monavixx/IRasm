#pragma once
#include "OpBase.h"

class OpLocal : public OpBase
{
public:
	OpLocal(const QString& id, const QString& dataType) : id(currentId), dataType(dataType)
	{
		names[id] = currentId;
		currentId++;
	}
	QByteArray Compile() override;


	static inline QHash<QString, int> names;
	static inline int currentId = 0;
private:
	int id;
	QString dataType;
	static inline quint8 byteOpCode = 11;
};

