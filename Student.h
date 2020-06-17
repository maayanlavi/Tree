#pragma once
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
class Student
{
public:
	Student() :_name(NULL), _age(0) {};
	Student(const char* name, int age);
	Student(const Student& student);
	~Student() { delete[] _name; }
	void save(ofstream& out) const;
	void load(ifstream& in);
	const char* getName() const { return _name; }
	int getAge() const { return _age; }
	void setName(const char* _name);

	bool operator==(const Student& student) const;
private:
	char* _name;
	int _age;
};

