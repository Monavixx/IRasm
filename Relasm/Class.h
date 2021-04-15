#pragma once
#include <QtCore>
#include "Method.h"
#include "Field.h"

class Class
{
public:
	Class(const QString& namespaceName, const QString& name, bool isMainClass = false);
	QByteArray Compile();
	void Add(Method* method);
	void Add(Field* field);
	QString GetName() const;
private:
	QString namespaceName;
	QString name;
	bool isMainClass;
	QList<Method*> methods;
	QList<Field*> fields;
	
	static inline quint8 byteOpCode = 3;
	static inline quint8 byteMainClassOpCode = 1;
};

