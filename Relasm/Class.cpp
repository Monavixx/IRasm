#include "Class.h"

Class::Class(const QString& namespaceName, const QString& name, bool isMainClass) : name(name), isMainClass(isMainClass), namespaceName(namespaceName)
{
}

QByteArray Class::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	quint8 currentByteOpCode = (isMainClass) ? (byteMainClassOpCode) : (byteOpCode);
	ds << currentByteOpCode << namespaceName << name;

	for (auto& item : methods)
	{
		QByteArray compiledParameter = item->Compile();
		for (int i = 0; i < compiledParameter.size(); ++i)
		{
			ds << (quint8)compiledParameter.at(i);
		}
	}
	for (auto& item : fields)
	{
		QByteArray compiledParameter = item->Compile();
		for (int i = 0; i < compiledParameter.size(); ++i)
		{
			ds << (quint8)compiledParameter.at(i);
		}
	}

	return code;
}

void Class::Add(Method* method)
{
	methods.push_back(method);
}

void Class::Add(Field* field)
{
	fields.push_back(field);
}

QString Class::GetName() const
{
	return name;
}
