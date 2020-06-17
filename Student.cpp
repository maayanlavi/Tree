#include "Student.h"


Student::Student(const char* name, int age) :_name(NULL), _age(age)
{
	setName(name);
}

Student::Student(const Student& student) : _name(NULL)
{
	_age = student._age;
	setName(student._name);
}

void Student::save(ofstream& out) const
{
	int nameSize = strlen(_name);
	out.write((char*)&nameSize, sizeof(nameSize));
	out.write(_name, nameSize);
	out.write((char*)&_age, sizeof(_age));
}

void Student::load(ifstream& in)
{
	int nameSize;
	in.read((char*)&nameSize, sizeof(nameSize));
	_name = new char[nameSize + 1];
	in.read(_name, nameSize);
	_name[nameSize] = '\0';
	in.read((char*)&_age, sizeof(_age));
}

void Student::setName(const char* name)
{
	if (_name != name) {
		if (_name != NULL)
			delete[] _name;
		if (name != NULL)
			_name = _strdup(name);
		else
			_name = NULL;
	}
}

bool Student::operator==(const Student& student) const
{
	if ((strcmp(_name, student._name) == 0) && (_age == student._age))
		return true;
	else
		return false;
}
