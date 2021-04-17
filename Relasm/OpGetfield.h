#pragma once
#include "OpBase.h"
#include "IsStatic.h"

class OpGetfield : public OpBase
{
public:
	OpGetfield(const QString& isStatic, const QString& name) : isStatic(flagStatic[isStatic]), name(name) {}
	OpGetfield(const QString& isStatic, const QString& namespaceName, const QString& className, const QString& name) : isStatic(flagStatic[isStatic]), namespaceName(namespaceName), className(className), name(name) {}
	QByteArray Compile() override;

private:
	static inline quint8 byteOpCode = 31;
	QString className;
	QString namespaceName;
	QString name;

	IsStatic isStatic;

	static inline QHash<QString, IsStatic> flagStatic = {
		{"instance", INSTANCE},
		{"static", STATIC}
	};
};

