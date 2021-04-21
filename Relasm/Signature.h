#pragma once
#include <QtCore>
#include "Parameter.h"

struct MethodData
{
	QString namespaceName;
	QString declClass;
	QString methodName;
	QList<Parameter> parameters;
	static MethodData FromString(const QString& methodData)
	{
		QString namespaceName;
		QString declClass;
		QString methodName;
		QList<Parameter> parameters;

		size_t indexOfParameters = methodData.indexOf('(');

		if (indexOfParameters == -1)
			Exit("Error call method");

		QString stringParameters = methodData.mid(indexOfParameters + 1, methodData.size() - indexOfParameters - 2);
		int indexOfStartMethodName = methodData.mid(0, indexOfParameters).lastIndexOf(".") + 1;

		if (indexOfStartMethodName == -1)
			Exit("Error call method");

		QString namespaceAndClass = methodData.mid(0, indexOfStartMethodName - 1);
		methodName = methodData.mid(indexOfStartMethodName, indexOfParameters - indexOfStartMethodName);

		QString currentParameterDataType;
		QString currentParameterName;
		bool isProcessName = false;
		for (int i = 0; i < stringParameters.size(); ++i)
		{
			if (stringParameters[i] == ',')
			{
				size_t indexStartClassName = currentParameterDataType.lastIndexOf('.');
				QString className = currentParameterDataType.mid(indexStartClassName + 1);
				QString namespaceName = currentParameterDataType.mid(0, indexStartClassName);
				parameters.push_back(Parameter(namespaceName, className, currentParameterName));
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
			size_t indexStartClassName = currentParameterDataType.lastIndexOf('.');
			QString className = currentParameterDataType.mid(indexStartClassName + 1);
			QString namespaceName = currentParameterDataType.mid(0, indexStartClassName);
			parameters.push_back(Parameter(namespaceName, className, currentParameterName));
		}

		size_t indexStartNameClass = namespaceAndClass.lastIndexOf('.');
		namespaceName = namespaceAndClass.mid(0, indexStartNameClass);
		declClass = namespaceAndClass.mid(indexStartNameClass+1);

		return MethodData{ namespaceName, declClass, methodName, parameters};
	}
};