#include "Parser.h"

Parser::Parser(const QString& code) : code(code)
{
}

QList<Class> Parser::Parse()
{
	return classes;
}

Class* Parser::FindClassByName(const QString& name)
{
	auto classIterator = std::find_if(classes.begin(), classes.end(), [&](const Class& _class) {
		return _class.GetName() == name;
		});
	if (classIterator == classes.end())
		return nullptr;
	return &(*classIterator);
}

void Parser::CreateMainClass(const QStringList& args, Method* method)
{
	Class mainClass(args[0], true);
	classes.push_back(mainClass);
	
}

void Parser::CreateMethod(const QStringList& args, Method* method)
{
	if (method == nullptr)
		Exit("Create method in other method!");
	QString strSignature = args[3];
	Signature signature = Signature::FromString(strSignature);
	QString declClassName = signature.delcClass;
	QString methodName = signature.methodName;
	QList<Parameter> parameters = signature.parameters;

	Method* creatableMethod = new Method(args[0], args[1], args[2], declClassName, methodName, parameters);

	Class* declClass = FindClassByName(declClassName);
	if (declClass == nullptr)
		Exit("CreateMethod: Decl class not found!");

	declClass->Add(creatableMethod);
}

void Parser::PushStr(const QStringList& args, Method* method)
{
}

void Parser::CallMethod(const QStringList& args, Method* method)
{
}

void Parser::New(const QStringList& args, Method* method)
{
}

void Parser::CreateClass(const QStringList& args, Method* method)
{
}

void Parser::Get(const QStringList& args, Method* method)
{
}

void Parser::Set(const QStringList& args, Method* method)
{
}

void Parser::Local(const QStringList& args, Method* method)
{
}

void Parser::Gc(const QStringList& args, Method* method)
{
}

void Parser::PushInt32(const QStringList& args, Method* method)
{
}

void Parser::Return(const QStringList& args, Method* method)
{
}

void Parser::Add(const QStringList& args, Method* method)
{
}

void Parser::Dup(const QStringList& args, Method* method)
{
}

void Parser::Jmp(const QStringList& args, Method* method)
{
}

void Parser::Jmpif(const QStringList& args, Method* method)
{
}
