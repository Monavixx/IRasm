#pragma once
#include <QtCore>
#include "Method.h"

class Class
{
public:
	Class(const QString& name, bool isMainClass = false);
	QByteArray Compile();
	void Add(const Method& method);
private:
	QString name;
	bool isMainClass;
	QList<Method> methods;
	
	static inline quint8 byteOpCode = 3;
	static inline quint8 byteMainClassOpCode = 1;
};
