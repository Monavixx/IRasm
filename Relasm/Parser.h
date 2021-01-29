#pragma once
#include <QtCore>
#include "Class.h"

class Parser
{
public:
	Parser(const QString& code);
	QList<Class> Parse();


	void CreateMainClass(const QStringList& args);
	void CreateMethod(const QStringList& args);
	void PushStr(const QStringList& args);
	void CallMethod(const QStringList& args);
	void New(const QStringList& args);
	void CreateClass(const QStringList& args);
	void Get(const QStringList& args);
	void Set(const QStringList& args);
	void Local(const QStringList& args);
	void Gc(const QStringList& args);
	void PushInt32(const QStringList& args);
	void Return(const QStringList& args);
	void Add(const QStringList& args);
	void Dup(const QStringList& args);
	void Jmp(const QStringList& args);
	void Jmpif(const QStringList& args);

private:
	QString code;
	QMap<QString, std::function<void(const QStringList& args)>> instructions =
	{
		{"mclass", std::bind(&Parser::CreateMainClass, this, QStringList())},
		{"method", std::bind(&Parser::CreateMethod, this, QStringList())},
		{"push.str", std::bind(&Parser::PushStr, this, QStringList())},
		{"new", std::bind(&Parser::New, this, QStringList())},
		{"class", std::bind(&Parser::CreateClass, this, QStringList())},
		{"get", std::bind(&Parser::Get, this, QStringList())},
		{"set", std::bind(&Parser::Set, this, QStringList())},
		{"local", std::bind(&Parser::Local, this, QStringList())},
		{"gc", std::bind(&Parser::Gc, this, QStringList())},
		{"push.int32", std::bind(&Parser::PushInt32, this, QStringList())},
		{"return", std::bind(&Parser::Return, this, QStringList())},
		{"add", std::bind(&Parser::Add, this, QStringList())},
		{"dup", std::bind(&Parser::Dup, this, QStringList())},
		{"jmp", std::bind(&Parser::Jmp, this, QStringList())},
		{"jmpif", std::bind(&Parser::Jmpif, this, QStringList())},
	};
	QList<Class> classes;
};

