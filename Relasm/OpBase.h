#pragma once
#include <QtCore>

class OpBase
{
public:
	virtual QByteArray Compile() = 0;
	virtual ~OpBase() {}
	void SetTags(QMap<QString, int>* tags)
	{
		this->tags = tags;
	}
	void SetMethod(class Method* method);
protected:
	QMap<QString, int>* tags;
	class Method* method;
};