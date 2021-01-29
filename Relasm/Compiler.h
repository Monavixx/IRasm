#pragma once
#include <QtCore>
#include "Class.h"
#include "OpPushStr.h"
#include "OpCallMethod.h"
#include "ConsoleTextStream.h"
#include "Exit.h"

class Compiler
{
public:
	Compiler(QStringList arguments);
	void Start();
	void Parse();
	void Compile();

private:
	QStringList arguments;
	QFile executebleFile;
	QDataStream ds;
	QList<Class> classes;
};

