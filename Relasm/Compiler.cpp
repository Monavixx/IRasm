#include "Compiler.h"

Compiler::Compiler(QStringList arguments) : arguments(arguments), executebleFile(arguments[2]), ds(&executebleFile)
{
	
}

void Compiler::Start()
{
	if (!executebleFile.open(QIODevice::WriteOnly))
	{
		Exit("executeble file don't open");
	}
	Parse();
	Compile();
}

void Compiler::Parse()
{
	Class mainClass("MainClass", true);
	Method mainMethod("public", "static", "void", "MainClass", "Main", {});
	mainMethod.Add(new OpPushStr("hello world"));
	mainMethod.Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.String" }));
	mainClass.Add(mainMethod);
	classes.push_back(mainClass);
}

void Compiler::Compile()
{
	for (auto& item : classes)
	{
		QByteArray compiledClass = item.Compile();
		for (int i = 0; i < compiledClass.size(); ++i)
		{
			ds << (quint8)compiledClass.at(i);
		}
	}
}
