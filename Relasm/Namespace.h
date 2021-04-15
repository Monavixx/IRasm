#pragma once
#include "Class.h"

class Namespace
{
public:
	inline Namespace(const QString& name) : name(name) {}
	inline void AddClass(Class* newClass) { classes.push_back(newClass); }
	inline QString GetName() const { return name; }
	inline QString& GetName() { return name; }
	inline QList<Class*>& GetClasses() { return classes; }
	inline QList<Class*> GetClasses() const { return classes; }
	Class* GetClass(const QString& name)
	{
		auto classIterator = std::find_if(classes.begin(), classes.end(), [&](Class* _class) {
			return _class->GetName() == name;
			});
		if (classIterator == classes.end())
			return nullptr;
		return *classIterator;
	}
	QByteArray Compile();
private:
	QString name;
	QList<Class*> classes;
	static inline quint8 byteOpCode = 39;
};

