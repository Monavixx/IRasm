#include "Namespace.h"

QByteArray Namespace::Compile()
{
	QByteArray code;
	QDataStream ds(&code, QIODevice::WriteOnly);

	ds << byteOpCode << name;

	for (auto& item : classes)
	{
		QByteArray compiledParameter = item->Compile();
		for (int i = 0; i < compiledParameter.size(); ++i)
		{
			ds << (quint8)compiledParameter.at(i);
		}
	}
	return code;
}
