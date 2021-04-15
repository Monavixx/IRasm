#include "Parser.h"

Parser::Parser(const QString& code, const QString& pathToFile) : allCode(code), pathToFile(pathToFile)
{
}

QList<Namespace*> Parser::Parse()
{
	QStringList code = allCode.split('\n');
	ProccesCode(code);
	
	QList<Instruction> instructions = StringListToInstruction(code);

	ExecuteAllCode(instructions);

	return namespaces;
}

QList<Instruction> Parser::StringListToInstruction(const QStringList& lineOfCode)
{
	QList<Instruction> instructions;
	for (int i = 0; i < lineOfCode.size(); ++i)
	{
		int index = lineOfCode[i].indexOf(' ');
		if (index != -1)
		{
			QString opcode = lineOfCode[i].mid(0, index);
			QString args = lineOfCode[i].mid(index + 1);
			instructions << Instruction{ opcode, args };
		}
		else
		{
			instructions << Instruction{ lineOfCode[i], "" };
		}
	}
	return instructions;
}

void Parser::ExecuteAllCode(const QList<Instruction>& instructions)
{
	for (int i = 0; i < instructions.size(); ++i)
	{
		QString instructionName = instructions[i].name;
        if (instructionName[0] == '\t' || instructionName[0] == ' ') continue;
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
					if (instructions[i].name[0] == '\t' || instructions[i].name[0] == ' ')
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
			args.push_back(code.mid(0, code.size()-1));
			//if(i < instructions.size() - 1)
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

		if (QRegExp("[a-zA-Z0-9_]+:").exactMatch(instructionName))
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
	QString namespaceName;
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

	QString namespaceAndClassName = strSignature.mid(0, indexOfStartMethodName - 1);
	size_t indexStartClassName = namespaceAndClassName.lastIndexOf('.');
	namespaceName = namespaceAndClassName.mid(0, indexStartClassName);
	className = namespaceAndClassName.mid(indexStartClassName + 1);
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

	return QStringList{ namespaceName, className, methodName } + parameters;
}

void Parser::ProccesCode(QStringList& code)
{
	code.removeAll("");
	for (auto& item : code)
	{
		bool isPartMethod = item[0] == "\t" || item[0] == " ";
		item.replace(QRegExp("[ \t]+"), " ");
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


void Parser::CreateMainClass()
{
	if(currentMethod != nullptr)
		Exit("mclass: must be out method");
	QString className, namespaceName;
	size_t indexStartClassName = args[0].lastIndexOf('.');
	className = args[0].mid(indexStartClassName + 1);
	namespaceName = args[0].mid(0, indexStartClassName);
	Namespace* declNamespace = GetNamespace(namespaceName);
	Class* mainClass = new Class(namespaceName, className, true);
	declNamespace->AddClass(mainClass);
}

void Parser::CreateMethod()
{
	if (currentMethod != nullptr)
		Exit("method: must be out method");
	QString strSignature = args[3];
	MethodData signature = MethodData::FromString(strSignature);
	QString namespaceName = signature.namespaceName;
	QString declClassName = signature.declClass;
	QString methodName = signature.methodName;
	QList<Parameter> parameters = signature.parameters;

	Namespace* declNamespace = GetNamespace(namespaceName);
	if (declNamespace == nullptr)
		Exit("method: namespace not found!");
	Class* declClass = declNamespace->GetClass(declClassName);
	if (declClass == nullptr)
		Exit("method: class not found!");

	Method* creatableMethod = new Method(args[0], args[1], args[2], namespaceName, declClassName, methodName, parameters);

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

	QString namespaceName, className, methodName;
	QList<Parameter> parameters;

	args[1] = "Relax.Console.Print(Relax.String)";
	QStringList splittedString = args[1].split('(');
	QString methodPath = splittedString[0], parametersString = splittedString[1].mid(0, splittedString[1].size() - 1);
	//method name
	size_t indexStartMethodName = methodPath.lastIndexOf('.');
	methodName = methodPath.mid(indexStartMethodName + 1);

	//class name
	QString namespaceAndClass = methodPath.mid(0, indexStartMethodName);
	size_t indexStartClassName = namespaceAndClass.lastIndexOf('.');
	className = namespaceAndClass.mid(indexStartClassName + 1);

	//namespace
	namespaceName = namespaceAndClass.mid(0, indexStartClassName);

	//parameters
	QStringList parametersList = parametersString.split(',');
	for (auto& item : parametersList)
	{
		Parameter param;
		size_t paramindexStartClassName = item.lastIndexOf('.');
		param.SetDataType(item.mid(paramindexStartClassName + 1));
		param.SetNamespaceName(item.mid(0, paramindexStartClassName));
		parameters.push_back(param);
	}

	currentMethod->Add(new OpCallMethod(args[0], namespaceName, className, methodName, parameters));
}

void Parser::New()
{
	if (currentMethod == nullptr)
		Exit("new: must be in method");

	QString namespaceName, className, strParameters, strSignature = args[0];

	QStringList splittedSignature = strSignature.split('(');
	QString namespaceAndClass = splittedSignature[0];

	size_t indexStartClassName = namespaceAndClass.lastIndexOf('.');
	namespaceName = namespaceAndClass.mid(0, indexStartClassName);
	className = namespaceAndClass.mid(indexStartClassName + 1);

	strParameters = splittedSignature[1].mid(0, splittedSignature[1].size() - 1);

	QStringList parametersStrList;
	if (strParameters.contains(','))
		parametersStrList = strParameters.split(',');
	else if(!strParameters.isEmpty())
		parametersStrList = QStringList{ strParameters };


	QList<Parameter> parameters;
	for (auto& item : parametersStrList)
	{
		Parameter param;
		size_t paramindexStartClassName = item.lastIndexOf('.');
		param.SetDataType(item.mid(paramindexStartClassName + 1));
		param.SetNamespaceName(item.mid(0, paramindexStartClassName));
		parameters.push_back(param);
	}


	currentMethod->Add(new OpNew(namespaceName, className, parameters));
}

void Parser::CreateClass()
{
	if (currentMethod != nullptr)
		Exit("mclass: must be out method");
	QString className, namespaceName;
	size_t indexStartClassName = args[0].lastIndexOf('.');
	className = args[0].mid(indexStartClassName + 1);
	namespaceName = args[0].mid(0, indexStartClassName);
	Namespace* declNamespace = GetNamespace(namespaceName);
	Class* mainClass = new Class(namespaceName, className);
	declNamespace->AddClass(mainClass);
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

	size_t indexStartClassName = args[1].lastIndexOf('.');
	QString className = args[1].mid(indexStartClassName + 1);
	QString namespaceName = args[1].mid(0, indexStartClassName);
	currentMethod->Add(new OpLocal(args[0], namespaceName, className, currentMethod));
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
	
	QStringList splitedFloat = args[0].split('.');
	int num = splitedFloat[0].toInt(), fracPart = splitedFloat[1].toInt();
	currentMethod->Add(new OpPushFloat(num, fracPart));
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
	currentMethod->Add(new OpCast(args[0]));
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

void Parser::Import()
{
	if (currentMethod != nullptr)
		Exit("import: cannot be in method");
	QString moduleFilename = pathToFile + "/" + args[0];
	QFile moduleFile(moduleFilename);
	if (!moduleFile.open(QIODevice::ReadOnly))
	{
		Exit("module " + moduleFilename + " not exists");
	}
	Parser moduleParser(moduleFile.readAll(), QFileInfo(moduleFile).path());
	namespaces += moduleParser.Parse();
}

void Parser::Field()
{
	if (currentMethod != nullptr)
		Exit("field: cannot be in method");

	QString namespaceName, declClassName, name;
	size_t lastIndex = args[3].lastIndexOf(".");
	QString namespaceAndClass = args[3].mid(0, lastIndex);

	size_t indexStartClassName = namespaceAndClass.lastIndexOf('.');
	namespaceName = namespaceAndClass.mid(0, indexStartClassName);
	declClassName = namespaceAndClass.mid(indexStartClassName + 1);

	name = args[3].mid(lastIndex + 1);

	
	size_t indexStartDataType = args[2].lastIndexOf('.');
	QString dataTypeClassName = args[2].mid(indexStartDataType);

	Namespace* declNamespace = GetNamespace(namespaceName);
	Class* declClass = declNamespace->GetClass(declClassName);
	declClass->Add(new ::Field(args[0], args[1], dataTypeClassName, namespaceName, declClassName, name));
}

void Parser::Getfield()
{
	if (currentMethod == nullptr)
		Exit("getfield: must be in method");
	currentMethod->Add(new OpGetfield(args[0]));
}

void Parser::Setfield()
{
	if (currentMethod == nullptr)
		Exit("setfield: must be in method");
	currentMethod->Add(new OpSetfield(args[0]));
}

void Parser::This()
{
	if (currentMethod == nullptr)
		Exit("this: must be in method");
	currentMethod->Add(new OpThis);
}

void Parser::Ce()
{
	if (currentMethod == nullptr)
		Exit("ce: must be in method");
	currentMethod->Add(new OpCe);
}

void Parser::Cl()
{
	if (currentMethod == nullptr)
		Exit("cl: must be in method");
	currentMethod->Add(new OpCl);
}

void Parser::Cb()
{
	if (currentMethod == nullptr)
		Exit("cb: must be in method");
	currentMethod->Add(new OpCb);
}

void Parser::Cle()
{
	if (currentMethod == nullptr)
		Exit("cle: must be in method");
	currentMethod->Add(new OpCle);
}

void Parser::Cbe()
{
	if (currentMethod == nullptr)
		Exit("cbe: must be in method");
	currentMethod->Add(new OpCbe);
}

void Parser::CreateNamespace()
{
	if (currentMethod != nullptr)
		Exit("namespace: must be out method");
	namespaces.push_back(new Namespace(args[0]));
}
