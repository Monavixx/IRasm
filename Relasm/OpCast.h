#pragma once
#include "OpBase.h"

class OpCast : public OpBase
{
public:
	OpCast(const QString& isStd, const QString& dataType) : dataType(dataType), isStd(flagStd[isStd]) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 25;
	QString dataType;
	bool isStd;

	static inline QHash<QString, quint8> flagStd = {
		{"usr", false},
		{"std", true}
	};
};

