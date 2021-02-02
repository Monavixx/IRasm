#pragma once
#include <QtCore>
#include "Class.h"
#include "Exit.h"
#include "Signature.h"

class Parser
{
public:
	Parser(const QString& code);
	QList<Class> Parse();

	Class* FindClassByName(const QString& name);


	void CreateMainClass(const QStringList& args, Method* method);
	void CreateMethod(const QStringList& args, Method* method);
	void PushStr(const QStringList& args, Method* method);
	void CallMethod(const QStringList& args, Method* method);
	void New(const QStringList& args, Method* method);
	void CreateClass(const QStringList& args, Method* method);
	void Get(const QStringList& args, Method* method);
	void Set(const QStringList& args, Method* method);
	void Local(const QStringList& args, Method* method);
	void Gc(const QStringList& args, Method* method);
	void PushInt32(const QStringList& args, Method* method);
	void Return(const QStringList& args, Method* method);
	void Add(const QStringList& args, Method* method);
	void Dup(const QStringList& args, Method* method);
	void Jmp(const QStringList& args, Method* method);
	void Jmpif(const QStringList& args, Method* method);

private:
	QString code;
	QMap<QString, std::function<void(const QStringList&, Method*)>> instructions =
	{
		{"mclass", std::bind(&Parser::CreateMainClass, this, QStringList(), new Method)},
		{"method", std::bind(&Parser::CreateMethod, this, QStringList(), new Method)},
		{"push.str", std::bind(&Parser::PushStr, this, QStringList(), new Method)},
		{"new", std::bind(&Parser::New, this, QStringList(), new Method)},
		{"class", std::bind(&Parser::CreateClass, this, QStringList(), new Method)},
		{"get", std::bind(&Parser::Get, this, QStringList(), new Method)},
		{"set", std::bind(&Parser::Set, this, QStringList(), new Method)},
		{"local", std::bind(&Parser::Local, this, QStringList(), new Method)},
		{"gc", std::bind(&Parser::Gc, this, QStringList(), new Method)},
		{"push.int32", std::bind(&Parser::PushInt32, this, QStringList(), new Method)},
		{"return", std::bind(&Parser::Return, this, QStringList(), new Method)},
		{"add", std::bind(&Parser::Add, this, QStringList(), new Method)},
		{"dup", std::bind(&Parser::Dup, this, QStringList(), new Method)},
		{"jmp", std::bind(&Parser::Jmp, this, QStringList(), new Method)},
		{"jmpif", std::bind(&Parser::Jmpif, this, QStringList(), new Method)},
	};
	QList<Class> classes;
};

