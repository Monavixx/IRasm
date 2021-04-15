#pragma once
#include "AccessModifier.h"
#include "IsStatic.h"
#include <QtCore>

class Field
{
public:
	Field(const QString& accessModifier, const QString& isStatic, const QString& dataType, const QString& namespaceName, const QString& declClassName, const QString& name)
	:accessModifier(flagAccessModifier[accessModifier]), isStatic(flagStatic[isStatic]), dataType(dataType), declClassName(declClassName), name(name), namespaceName(namespaceName){}
	QByteArray Compile();

private:
	static inline quint8 byteOpCode = 30;

	AccessModifier accessModifier;
	bool isStatic;
	QString dataType;
	QString namespaceName;
	QString declClassName;
	QString name;

	static inline QHash<QString, IsStatic> flagStatic = {
		{"instance", INSTANCE},
		{"static", STATIC}
	};
	static inline QHash<QString, AccessModifier> flagAccessModifier = {
		{"private", PRIVATE},
		{"public", PUBLIC},
		{"protected", PROTECTED}
	};
};

