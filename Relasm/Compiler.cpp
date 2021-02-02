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
	Class* mainClass = new Class("MainClass", true);
	Method* mainMethod = new Method("public", "static", "void", "MainClass", "Main", {});
	
	mainMethod->Add(new OpLocal(1, "Relax.Array"));
	mainMethod->Add(new OpPushInt32(3));
	mainMethod->Add(new OpNewarr("Relax.Int32"));
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpDup);
	mainMethod->Add(new OpSet(1));

	mainMethod->Add(new OpPushInt32(0));
	mainMethod->Add(new OpPushInt32(98));
	mainMethod->Add(new OpSetarr);

	mainMethod->Add(new OpPushInt32(1));
	mainMethod->Add(new OpPushInt32(-8));
	mainMethod->Add(new OpSetarr);

	mainMethod->Add(new OpPushInt32(2));
	mainMethod->Add(new OpPushInt32(1));
	mainMethod->Add(new OpSetarr);

	mainMethod->Add(new OpPushInt32(0));
	mainMethod->Add(new OpGetarr);
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", {"Relax.Int32"}));
	mainMethod->Add(new OpPushStr("\n"));
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.String" }));

	mainMethod->Add(new OpPushInt32(1));
	mainMethod->Add(new OpGetarr);
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.Int32" }));
	mainMethod->Add(new OpPushStr("\n"));
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.String" }));

	mainMethod->Add(new OpPushInt32(2));
	mainMethod->Add(new OpGetarr);
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.Int32" }));
	mainMethod->Add(new OpPushStr("\n"));
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.String" }));

	mainMethod->Add(new OpPushInt32(1));
	mainMethod->Add(new OpGetarr);
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.Int32" }));
	mainMethod->Add(new OpPushStr("\n"));
	mainMethod->Add(new OpCallMethod("static", "std", "void", "Relax.Console", "Write", { "Relax.String" }));


	mainClass->Add(mainMethod);
	classes.push_back(mainClass);
}

void Compiler::Compile()
{
	for (auto& item : classes)
	{
		QByteArray compiledClass = item->Compile();
		for (int i = 0; i < compiledClass.size(); ++i)
		{
			ds << (quint8)compiledClass.at(i);
		}
	}
}
