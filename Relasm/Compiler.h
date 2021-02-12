#pragma once
#include <QtCore>
#include "Class.h"
#include "OpCodes.h"
#include "ConsoleTextStream.h"
#include "Exit.h"
#include "Parser.h"

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
	QList<Class*> classes;
	QFile relasmFile;

	const int version = 3;
};

