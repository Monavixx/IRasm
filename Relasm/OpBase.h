#pragma once
#include <QtCore>

class OpBase
{
public:
	virtual QByteArray Compile() = 0;
	int GetSize()
	{
		return (isProccessSize == false) ? (size = Compile().size()) : size;
	}
	virtual ~OpBase() {}
	void SetTags(QMap<QString, int>* tags)
	{
		this->tags = tags;
	}
protected:
	QMap<QString, int>* tags;
private:
	bool isProccessSize = false;
	int size;
};