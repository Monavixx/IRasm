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
	Parser(const QString& code, const QString& pathToFile);
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
	void Ref();
	void Deref();
	void Setpd();
	void Import();
	void Field();
	void Getfield();
	void Setfield();
	void This();
	void Ce();
	void Cl();
	void Cb();
	void Cle();
	void Cbe();
private:
	Method* currentMethod = nullptr;
	QStringList args;

	static void ProccesCode(QStringList& code);

	QString allCode;
	QString pathToFile;
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
		{".maxstack", std::bind(&Parser::MaxStack, this)},
		{"ref", std::bind(&Parser::Ref, this)},
		{"deref", std::bind(&Parser::Deref, this)},
		{"setpd", std::bind(&Parser::Setpd, this)},
		{"import", std::bind(&Parser::Import, this)},
		{"field", std::bind(&Parser::Field, this)},
		{"getfield", std::bind(&Parser::Getfield, this)},
		{"setfield", std::bind(&Parser::Setfield, this)},
		{"this", std::bind(&Parser::This, this)},
		{"ce", std::bind(&Parser::Ce, this)},
		{"cl", std::bind(&Parser::Cl, this)},
		{"cb", std::bind(&Parser::Cb, this)},
		{"cle", std::bind(&Parser::Cle, this)},
		{"cbe", std::bind(&Parser::Cbe, this)}
	};
	QList<Class*> classes;
};

