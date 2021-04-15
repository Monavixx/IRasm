#include "Compiler.h"

Compiler::Compiler(QStringList arguments) : arguments(arguments), executebleFile(arguments[2]), ds(&executebleFile), relasmFile(arguments[1])
{
	
}

void Compiler::Start()
{
	if (!executebleFile.open(QIODevice::WriteOnly))
	{
		Exit("executeble file don't open");
	}
	if (!relasmFile.open(QIODevice::ReadOnly))
	{
		Exit("relasm file don't open");
	}

	ds << (int)version;

	Parse();
	Compile();
}

void Compiler::Parse()
{
	Parser parser(relasmFile.readAll(), QFileInfo(relasmFile).path());
	namespaces = parser.Parse();
}

void Compiler::Compile()
{
	for (auto& item : namespaces)
	{
		QByteArray compiledClass = item->Compile();
		for (int i = 0; i < compiledClass.size(); ++i)
		{
			ds << (quint8)compiledClass.at(i);
		}
	}
}
