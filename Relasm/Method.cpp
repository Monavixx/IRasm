#include "Method.h"

Method::Method(const QString& accessModifier, const QString& isStatic, const QString& dataType, const QString& namespaceName, const QString& declClass, const QString& name, const QList<Parameter>& parameters)
	: accessModifier(flagAccessModifier[accessModifier]), isStatic(flagStatic[isStatic]), dataType(dataType), declClass(declClass), name(name), parameters(parameters), namespaceName(namespaceName)
{
	for (auto& item : this->parameters)
	{
		names[item.GetName()] = currentId;
		++currentId;
	}
}

QByteArray Method::Compile() const
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode;
	ds << quint8(accessModifier) << quint8(isStatic);
	ds << dataType;
	ds << namespaceName;
	ds << declClass;
	ds << name;
	ds << int(parameters.size());
	for (auto& item : parameters)
	{
		//ds << item.Compile();
		QByteArray compiledOpCode = item.Compile();
		for (int i = 0; i < compiledOpCode.size(); ++i)
		{
			ds << (quint8)compiledOpCode.at(i);
		}
	}

	//body
	QByteArray byteArrayBody;
	QDataStream dsBody(&byteArrayBody, QIODevice::WriteOnly);
	for (auto& item : body)
	{
		QByteArray compiledOpCode = item->Compile();
		for (int i = 0; i < compiledOpCode.size(); ++i)
		{
			dsBody << (quint8)compiledOpCode.at(i);
		}
	}
	ds << int(byteArrayBody.size());
	for (int i = 0; i < byteArrayBody.size(); ++i)
	{
		ds << (quint8)byteArrayBody.at(i);
	}

	return code;
}

void Method::Add(OpBase* opCode)
{
	opCode->SetTags(&tags);
	body.push_back(opCode);
}

void Method::AddTag(const QString& nameTag)
{
	tags[nameTag] = body.size();
}
