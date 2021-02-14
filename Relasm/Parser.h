#pragma once
#include <QtCore>
#include "Class.h"
#include "Exit.h"
#include "Signature.h"
#include "Instruction.h"
#include "OpCodes.h"

class Parser
{
public:
	Parser(const QString& code);
	QList<Class*> Parse();
	QList<Instruction> StringListToInstruction(const QStringList& lineOfCode);
	void ExecuteAllCode(const QList<Instruction>& instructions);
	void ExecuteMethod(const QList<Instruction>& instructions);
	QStringList StringToSignature(const QString& strSignature);


	Class* FindClassByName(const QString& name);


	void CreateMainClass();
	void CreateMethod();
	void PushStr();
	void CallMethod();
	void New();
	void CreateClass();
	void Get();
	void Set();
	void Local();
	void Gc();
	void PushInt32();
	void Return();
	void Add();
	void Dup();
	void Jmp();
	void Jmpif();
	void Newarr();
	void Getarr();
	void Setarr();
	void PushBool();
	void PushFloat();
	void Sub();
	void Mul();
	void Div();
	void Cast();
	void MaxStack();

private:
	Method* currentMethod = nullptr;
	QStringList args;

	static void ProccesCode(QStringList& code);

	QString allCode;
	QMap<QString, std::function<void()>> opCodes =
	{
		{"mclass", std::bind(&Parser::CreateMainClass, this)},
		{"method", std::bind(&Parser::CreateMethod, this)},
		{"push.str", std::bind(&Parser::PushStr, this)},
		{"callm", std::bind(&Parser::CallMethod, this)},
		{"new", std::bind(&Parser::New, this)},
		{"class", std::bind(&Parser::CreateClass, this)},
		{"get", std::bind(&Parser::Get, this)},
		{"set", std::bind(&Parser::Set, this)},
		{"local", std::bind(&Parser::Local, this)},
		{"gc", std::bind(&Parser::Gc, this)},
		{"push.int32", std::bind(&Parser::PushInt32, this)},
		{"return", std::bind(&Parser::Return, this)},
		{"add", std::bind(&Parser::Add, this)},
		{"dup", std::bind(&Parser::Dup, this)},
		{"jmp", std::bind(&Parser::Jmp, this)},
		{"jmpif", std::bind(&Parser::Jmpif, this)},
		{"newarr", std::bind(&Parser::Newarr, this)},
		{"getarr", std::bind(&Parser::Getarr, this)},
		{"setarr", std::bind(&Parser::Setarr, this)},
		{"push.bool", std::bind(&Parser::PushBool, this)},
		{"push.float", std::bind(&Parser::PushFloat, this)},
		{"sub", std::bind(&Parser::Sub, this)},
		{"mul", std::bind(&Parser::Mul, this)},
		{"div", std::bind(&Parser::Div, this)},
		{"cast", std::bind(&Parser::Cast, this)},
		{".maxstack", std::bind(&Parser::MaxStack, this)}
	};
	QList<Class*> classes;
};

