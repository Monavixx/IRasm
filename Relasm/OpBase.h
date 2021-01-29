#pragma once
#include <QtCore>

class OpBase
{
public:
	virtual QByteArray Compile() = 0;
};