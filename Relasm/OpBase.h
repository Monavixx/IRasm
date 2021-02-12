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
protected:
	QMap<QString, int>* tags;
};