#pragma once
#include "OpBase.h"

class OpNew : public OpBase
{
public:
	OpNew(const QString& isStd, const QString& dataType, const QList<QString>& parameters);
	QByteArray Compile() override;

private:
	bool isStd;
	QString dataType;
	QList<QString> parameters;

	static inline quint8 byteOpCode = 2;

	static inline QHash<QString, quint8> flagStd = {
		{"usr", false},
		{"std", true}
	};
};

