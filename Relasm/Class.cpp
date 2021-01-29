#include "Class.h"

Class::Class(const QString& name, bool isMainClass) : name(name), isMainClass(isMainClass)
{
}

QByteArray Class::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	quint8 currentByteOpCode = (isMainClass) ? (byteMainClassOpCode) : (byteOpCode);
	ds << currentByteOpCode << name.toUtf8();

	for (auto& item : methods)
	{
		QByteArray compiledParameter = item.Compile();
		for (int i = 0; i < compiledParameter.size(); ++i)
		{
			ds << (quint8)compiledParameter.at(i);
		}
	}

	return code;
}

void Class::Add(const Method& method)
{
	methods.push_back(method);
}
