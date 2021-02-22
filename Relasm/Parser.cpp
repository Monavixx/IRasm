#include "Parser.h"

Parser::Parser(const QString& code) : allCode(code)
{
}

QList<Class*> Parser::Parse()
{
	QStringList code = allCode.split('\n');
	ProccesCode(code);
	
	QList<Instruction> instructions = StringListToInstruction(code);

	ExecuteAllCode(instructions);

	return classes;
}

QList<Instruction> Parser::StringListToInstruction(const QStringList& lineOfCode)
{
	QList<Instruction> instructions;
	for (int i = 0; i < lineOfCode.size(); ++i)
	{
		int index = lineOfCode[i].indexOf(' ');
		QString opcode = lineOfCode[i].mid(0, index);
		QString args = lineOfCode[i].mid(index + 1);
		instructions << Instruction{ opcode, args };
	}
	return instructions;
}

void Parser::ExecuteAllCode(const QList<Instruction>& instructions)
{
	for (int i = 0; i < instructions.size(); ++i)
	{
		QString instructionName = instructions[i].name;
		if (instructionName[0] == '\t') continue;
		bool isOpenQuate = false;
		int amountOpenBraces = 0;
		QString currentArg;
		QStringList args;
		for (int j = 0; j < instructions[i].args.size(); ++j)
		{
			if (instructions[i].args[j] == '\"')
			{
				isOpenQuate = !isOpenQuate;
				currentArg.push_back(instructions[i].args[j]);
			}
			else if (instructions[i].args[j] == ' ' && !isOpenQuate && amountOpenBraces == 0)
			{
				args.push_back(currentArg);
				currentArg = "";
			}
			else
			{
				currentArg.push_back(instructions[i].args[j]);
			}


			if (instructions[i].args[j] == '(') ++amountOpenBraces;
			if (instructions[i].args[j] == ')') --amountOpenBraces;
		}
		bool isHasCode = false;
		if (!(currentArg == "" && args.isEmpty()))
		{
			isHasCode = currentArg.back() == ':';
			args.push_back(isHasCode ? currentArg.mid(0, currentArg.size() - 1) : currentArg);
		}

		if (isHasCode)
		{
			QString code;
			++i;
			while (true)
			{
				if (instructions.size() - 1 >= i)
				{
					if (instructions[i].name[0] == '\t')
					{
						code += instructions[i].name.mid(1) + " " + instructions[i].args + "\n";
						++i;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			args.push_back(code);
			if(i < instructions.size() - 1)
				--i;
		}

		if (opCodes.contains(instructionName))
		{
			this->args = args;
			opCodes[instructionName]();
		}
	}
}

void Parser::ExecuteMethod(const QList<Instruction>& instructions)
{
	for (int i = 0; i < instructions.size(); ++i)
	{
		QString instructionName = instructions[i].name;

		if (QRegExp("[a-zA-Z0-9]+:").exactMatch(instructionName))
		{
			currentMethod->AddTag(instructionName.mid(0, instructionName.size() - 1));
			continue;
		}

		bool isOpenQuate = false;
		QString currentArg;
		QStringList args;
		for (int j = 0; j < instructions[i].args.size(); ++j)
		{
			if (instructions[i].args[j] == '\"')
			{
				isOpenQuate = !isOpenQuate;
				currentArg.push_back(instructions[i].args[j]);
			}
			else if (instructions[i].args[j] == ' ' && !isOpenQuate)
			{
				args.push_back(currentArg);
				currentArg = "";
			}
			else
			{
				currentArg.push_back(instructions[i].args[j]);
			}
		}
		if (!(currentArg == "" && args.isEmpty()))
		{
			args.push_back(currentArg);
		}

		if (opCodes.contains(instructionName))
		{
			this->args = args;
			opCodes[instructionName]();
		}
	}
	currentMethod = nullptr;
}

QStringList Parser::StringToSignature(const QString& strSignature)
{
	QString className;
	QString methodName;
	QStringList parameters;

	int indexOfParameters = strSignature.indexOf("(");

	if (indexOfParameters == -1)
		Exit("Error call method");

	QString stringParameters = strSignature.mid(indexOfParameters + 1, strSignature.size() - indexOfParameters - 2);
	int indexOfStartMethodName = strSignature.mid(0, indexOfParameters).lastIndexOf(".") + 1;

	if (indexOfStartMethodName == -1)
		Exit("Error call method");

	className = strSignature.mid(0, indexOfStartMethodName - 1);
	methodName = strSignature.mid(indexOfStartMethodName, indexOfParameters - indexOfStartMethodName);

	QString currentParameter;
	for (int i = 0; i < stringParameters.size(); ++i)
	{
		if (stringParameters[i] == ',')
		{
			parameters.push_back(currentParameter);
			currentParameter = "";
		}
		else
		{
			currentParameter.push_back(stringParameters[i]);
		}
	}
	if (!currentParameter.isEmpty())
	{
		parameters.push_back(currentParameter);
	}

	return QStringList{ className, methodName } + parameters;
}

void Parser::ProccesCode(QStringList& code)
{
	code.removeAll("");
	for (auto& item : code)
	{
		bool isPartMethod = item[0] == "\t";
		item.replace(QRegExp("[ \f\t\v\u00A0]+"), " ");
		item.remove('\n');
		item.remove('\r');
		if (isPartMethod)
		{
			item.remove(0, 1);
			item.push_front("\t");
		}
		item.replace(", ", ",");
		item.replace(" :", ":");

		bool isOpenQuate = false;
		int index = item.size();
		for (int i = 0; i < item.size(); ++i)
		{
			if (item[i] == "\"") isOpenQuate = !isOpenQuate;
			if (item[i] == ';')
			{
				index = i;
				break;
			}
		}
		item = item.mid(0, index);
	}
	code.removeAll("");
	code.removeAll("\t");
}

Class* Parser::FindClassByName(const QString& name)
{
	auto classIterator = std::find_if(classes.begin(), classes.end(), [&](Class* _class) {
		return _class->GetName() == name;
		});
	if (classIterator == classes.end())
		return nullptr;
	return *classIterator;
}

void Parser::CreateMainClass()
{
	if(currentMethod != nullptr)
		Exit("mclass: must be out method");
	Class* mainClass = new Class(args[0], true);
	classes.push_back(mainClass);
}

void Parser::CreateMethod()
{
	if (currentMethod != nullptr)
		Exit("method: must be out method");
	QString strSignature = args[3];
	MethodData signature = MethodData::FromString(strSignature);
	QString declClassName = signature.delcClass;
	QString methodName = signature.methodName;
	QList<Parameter> parameters = signature.parameters;

	Method* creatableMethod = new Method(args[0], args[1], args[2], declClassName, methodName, parameters);

	Class* declClass = FindClassByName(declClassName);
	if (declClass == nullptr)
		Exit("method: decl class not found!");

	declClass->Add(creatableMethod);
	currentMethod = creatableMethod;

	ExecuteMethod(StringListToInstruction(args[4].split('\n')));
}

void Parser::PushStr()
{
	if (currentMethod == nullptr)
		Exit("push.str: must be in method");
	currentMethod->Add(new OpPushStr(args[0].mid(1, args[0].size() - 2)));
}

void Parser::CallMethod()
{
	if (currentMethod == nullptr)
		Exit("callm: must be in method");

	QString strSignature = args[2];
	QStringList signature = StringToSignature(strSignature);
	currentMethod->Add(new OpCallMethod(args[0], args[1], signature[0], signature[1], signature.mid(2)));
}

void Parser::New()
{
	if (currentMethod == nullptr)
		Exit("new: must be in method");

	QString strSignature = args[2];
	QStringList signature = StringToSignature(strSignature);
	currentMethod->Add(new OpCallMethod(args[0], args[1], signature[0], signature[1], signature.mid(2)));
}

void Parser::CreateClass()
{
	if (currentMethod != nullptr)
		Exit("class: must be out method");
	Class* mainClass = new Class(args[0]);
	classes.push_back(mainClass);
}

void Parser::Get()
{
	if (currentMethod == nullptr)
		Exit("get: must be in method");
	currentMethod->Add(new OpGet(args[0], currentMethod));
}

void Parser::Set()
{
	if (currentMethod == nullptr)
		Exit("set: must be in method");
	currentMethod->Add(new OpSet(args[0], currentMethod));
}

void Parser::Local()
{
	if (currentMethod == nullptr)
		Exit("local: must be in method");
	currentMethod->Add(new OpLocal(args[0], args[1], currentMethod));
}

void Parser::Gc()
{
	if (currentMethod == nullptr)
		Exit("gc: must be in method");
	currentMethod->Add(new OpGc);
}

void Parser::PushInt32()
{
	if (currentMethod == nullptr)
		Exit("pushInt32: must be in method");
	currentMethod->Add(new OpPushInt32(args[0].toInt()));
}

void Parser::Return()
{
	if (currentMethod == nullptr)
		Exit("return: must be in method");
	currentMethod->Add(new OpReturn);
}

void Parser::Add()
{
	if (currentMethod == nullptr)
		Exit("add: must be in method");
	currentMethod->Add(new OpAdd);
}

void Parser::Dup()
{
	if (currentMethod == nullptr)
		Exit("dup: must be in method");
	currentMethod->Add(new OpDup);
}

void Parser::Jmp()
{
	if (currentMethod == nullptr)
		Exit("jmp: must be in method");
	currentMethod->Add(new OpJmp(args[0]));
}

void Parser::Jmpif()
{
	if (currentMethod == nullptr)
		Exit("jmpif: must be in method");
	currentMethod->Add(new OpJmpif(args[0]));
}

void Parser::Newarr()
{
	if (currentMethod == nullptr)
		Exit("newarr: must be in method");
	currentMethod->Add(new OpNewarr(args[0]));
}

void Parser::Getarr()
{
	if (currentMethod == nullptr)
		Exit("getarr: must be in method");
	currentMethod->Add(new OpGetarr);
}

void Parser::Setarr()
{
	if (currentMethod == nullptr)
		Exit("setarr: must be in method");
	currentMethod->Add(new OpSetarr);
}

void Parser::PushBool()
{
	if (currentMethod == nullptr)
		Exit("push.bool: must be in method");
	currentMethod->Add(new OpPushBool(args[0]));
}

void Parser::PushFloat()
{
	if (currentMethod == nullptr)
		Exit("push.float: must be in method");
	currentMethod->Add(new OpPushFloat(args[0].toFloat()));
}

void Parser::Sub()
{
	if (currentMethod == nullptr)
		Exit("sub: must be in method");
	currentMethod->Add(new OpSub);
}

void Parser::Mul()
{
	if (currentMethod == nullptr)
		Exit("mul: must be in method");
	currentMethod->Add(new OpMul);
}

void Parser::Div()
{
	if (currentMethod == nullptr)
		Exit("div: must be in method");
	currentMethod->Add(new OpDiv);
}

void Parser::Cast()
{
	if (currentMethod == nullptr)
		Exit("cast: must be in method");
	currentMethod->Add(new OpCast(args[0], args[1]));
}

void Parser::MaxStack()
{
	if (currentMethod == nullptr)
		Exit(".maxstack: must be in method");
	currentMethod->Add(new OpMaxStack(args[0].toInt()));
}

void Parser::Ref()
{
	if (currentMethod == nullptr)
		Exit("ref: must be in method");
	currentMethod->Add(new OpRef(args[0]));
}

void Parser::Deref()
{
	if (currentMethod == nullptr)
		Exit("deref: must be in method");
	currentMethod->Add(new OpDeref);
}

void Parser::Setpd()
{
	if (currentMethod == nullptr)
		Exit("setpd: must be in method");
	currentMethod->Add(new OpSetpd);
}
