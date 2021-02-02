#pragma once
#include <QtCore>
#include "Class.h"
#include "OpPushStr.h"
#include "OpJmp.h"
#include "OpJmpif.h"
#include "OpCallMethod.h"
#include "OpNew.h"
#include "OpSet.h"
#include "OpGet.h"
#include "OpLocal.h"
#include "OpPushInt32.h"
#include "OpAdd.h"
#include "OpDup.h"
#include "OpNewarr.h"
#include "OpSetarr.h"
#include "OpGetarr.h"
#include "OpPushBool.h"
#include "OpGc.h"
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
	QList<Class*> classes;
};

