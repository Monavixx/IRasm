#pragma once
#include <QtCore>
#include "AccessModifier.h"
#include "IsStatic.h"
#include "OpBase.h"
#include "Parameter.h"

class Method
{
public:
	Method() {}
	Method(const QString& accessModifier, const QString& isStatic, const QString& dataType, const QString& namespaceName, const QString& declClass, const QString& name, const QList<Parameter>& parameters);
	QByteArray Compile() const;
	void Add(OpBase* opCode);
	void AddTag(const QString& nameTag);
	
	QHash<QString, int> names;
	int currentId = 0;
private:
	AccessModifier accessModifier;
	IsStatic isStatic;
	QString dataType;
	QString namespaceName;
	QString declClass;
	QString name;
	QList<Parameter> parameters;
	QList<OpBase*> body;
	QMap<QString, int> tags;

	
	static inline quint8 byteOpCode = 4;
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

