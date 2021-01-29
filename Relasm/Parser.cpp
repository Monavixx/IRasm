#include "Parser.h"

Parser::Parser(const QString& code) : code(code)
{
}

QList<Class> Parser::Parse()
{
	return classes;
}

void Parser::CreateMainClass(const QStringList& args)
{
	Class mainClass(args[0], true);
	classes.push_back(mainClass);
}

void Parser::CreateMethod(const QStringList& args)
{
	QString declClass = signature[0];
	QString methodName = signature[1];
	QStringList parameters = signature.mid(2);

	Method method(args[0], args[1], args[2], declClass, methodName, parameters);
}
