#pragma once
#include "OpBase.h"

class OpPushBool : public OpBase
{
public:
	OpPushBool(const QString& data) : data(dataMap[data]) {}
	QByteArray Compile() override;

private:
	bool data;
	static inline quint8 byteOpCode = 20;

	static inline QMap<QString, bool> dataMap = {
		{"true", true},
		{"false", false}
	};
};

