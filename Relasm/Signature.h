#pragma once
#include <QtCore>
#include "Parameter.h"

struct Signature
{
	QString delcClass;
	QString methodName;
	QList<Parameter> parameters;
	static Signature FromString(const QString& signature)
	{
		QString declClass;
		QString methodName;
		QList<Parameter> parameters;

		int indexOfParameters = signature.indexOf("(");

		if (indexOfParameters == -1)
			Exit("Error call method");

		QString stringParameters = signature.mid(indexOfParameters + 1, signature.size() - indexOfParameters - 2);
		int indexOfStartMethodName = signature.mid(0, indexOfParameters).lastIndexOf(".") + 1;

		if (indexOfStartMethodName == -1)
			Exit("Error call method");

		declClass = signature.mid(0, indexOfStartMethodName - 1);
		methodName = signature.mid(indexOfStartMethodName, indexOfParameters - indexOfStartMethodName);

		QString currentParameterDataType;
		QString currentParameterName;
		bool isProcessName = false;
		for (int i = 0; i < stringParameters.size(); ++i)
		{
			if (stringParameters[i] == ',')
			{
				parameters.push_back(Parameter(currentParameterDataType, currentParameterName));
				currentParameterDataType.clear();
				currentParameterName.clear();
				isProcessName = false;
			}
			else if (stringParameters[i] == ' ')
			{
				isProcessName = true;
			}
			else
			{
				if (isProcessName)
					currentParameterName.push_back(stringParameters[i]);
				else
					currentParameterDataType.push_back(stringParameters[i]);
			}
		}
		if (!currentParameterName.isEmpty() && !currentParameterDataType.isEmpty())
		{
			parameters.push_back(Parameter(currentParameterDataType, currentParameterName));
		}

		return Signature{ declClass, methodName, parameters };
	}
};