#pragma once
#include <QtCore>

class Parameter
{
public:
	Parameter(const QString& namespaceName="", const QString& dataType="", const QString& name="");
	QByteArray Compile() const;

	inline QString& GetDataType() { return dataType; }
	inline QString& GetNamespaceName() { return namespaceName; }
	inline QString& GetName() { return name; }

	inline QString GetDataType() const { return dataType; }
	inline QString GetNamespaceName() const { return namespaceName; }
	inline QString GetName() const { return name; }

	inline void SetDataType(const QString& dataType) { this->dataType = dataType; }
	inline void SetNamespaceName(const QString& namespaceName) { this->namespaceName = namespaceName; }
	inline void SetName(const QString& name) { this->name = name; }

private:
	QString namespaceName;
	QString dataType;
	QString name;
};

