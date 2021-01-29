#pragma once
#include "OpBase.h"
#include "IsStatic.h"

class OpCallMethod : public OpBase
{
public:
	OpCallMethod(const QString& isStatic, const QString& isStd, const QString& dataType, const QString declClass, const QString name, const QList<QString>& parameters);
	QByteArray Compile() override;

private:
	IsStatic isStatic;
	bool isStd;
	QString dataType;
	QString declClass;
	QString name;
	QList<QString> parameters;

	static inline quint8 byteOpCode = 5;
	static inline QHash<QString, IsStatic> flagStatic = {
		{"instance", INSTANCE},
		{"static", STATIC}
	};
	static inline QHash<QString, quint8> flagStd = {
		{"usr", 0},
		{"std", 1}
	};
};

