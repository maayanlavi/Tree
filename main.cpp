#include <iostream>
#include <string.h>
#include <fstream>

// Ex1, Ex2, Ex3

void writeStringToStream(std::ofstream& ofs, const char* str)
{
	int length = strlen(str);
	ofs.write((char*)&length, sizeof(length));
	ofs.write(str, length);
}

class Product
{
public:
	Product(char* model, int year) : _model(new char[strlen(model) + 1]), _year(year)
	{
		strcpy(_model, model);
	}
	Product(const Product& p) : _year(p._year), _model(new char[strlen(p._model) + 1])
	{
		strcpy(_model, p._model);
	}
	virtual void saveType(std::ofstream& ofs) = 0;
	virtual void save(std::ofstream& ofs)
	{
		writeStringToStream(ofs, _model);
		ofs.write((char*)&_year, sizeof(_year));
	}
private:
	char* _model;
	int _year;
};

class CellularPhone : public Product
{
public:
	CellularPhone(const Product& p, const char* modem) : Product(p), _modem(new char[strlen(modem) + 1])
	{
		strcpy(_modem, modem);
	}
	CellularPhone(const CellularPhone& c) : Product(c), _modem(new char[strlen(c._modem) + 1])
	{
		strcpy(_modem, c._modem);
	}
	virtual void saveType(std::ofstream& ofs)
	{
		ofs.write("CP", 2);
	}
	virtual void save(std::ofstream& ofs)
	{
		Product::save(ofs);
		writeStringToStream(ofs, _modem);
	}
private:
	char* _modem;
};

class ConsoleSmartWatchCommon : public Product
{
public:
	ConsoleSmartWatchCommon(const Product& p, int capacity, const char* processor)
		: Product(p), _capacity(capacity), _processor(new char[strlen(processor) + 1])
	{
		strcpy(_processor, processor);
	}
	ConsoleSmartWatchCommon(const ConsoleSmartWatchCommon& c) : Product(c), _capacity(c._capacity),
		_processor(new char[strlen(c._processor) + 1])
	{
		strcpy(_processor, c._processor);
	}
	virtual void save(std::ofstream& ofs)
	{
		Product::save(ofs);
		ofs.write((char*)&_capacity, sizeof(_capacity));
		writeStringToStream(ofs, _processor);
	}
	int getCapacity() const { return _capacity; }
private:
	int _capacity;
	char* _processor;
};

class Console : public ConsoleSmartWatchCommon
{
public:
	Console(const ConsoleSmartWatchCommon& c, char** controllers, int size) : ConsoleSmartWatchCommon(c),
		_size(size)
	{
		_controllers = new char* [size];
		for (int i = 0; i < size; ++i)
		{
			_controllers[i] = new char[strlen(controllers[i]) + 1];
			strcpy(_controllers[i], controllers[i]);
		}
	}
	virtual void saveType(std::ofstream& ofs)
	{
		ofs.write("CL", 2);
	}
	virtual void save(std::ofstream& ofs)
	{
		ConsoleSmartWatchCommon::save(ofs);
		ofs.write((char*)&_size, sizeof(_size));
		for (int i = 0; i < _size; ++i)
			writeStringToStream(ofs, _controllers[i]);
	}
private:
	int _size;
	char** _controllers;
};

class SmartWatch : public ConsoleSmartWatchCommon
{
public:
	SmartWatch(ConsoleSmartWatchCommon& c, float screenSize) : ConsoleSmartWatchCommon(c),
		_screenSize(screenSize) {}
	virtual void saveType(std::ofstream& ofs)
	{
		ofs.write("SW", 2);
	}
	virtual void save(std::ofstream& ofs)
	{
		ConsoleSmartWatchCommon::save(ofs);
		ofs.write((char*)&_screenSize, sizeof(_screenSize));
	}
	float getScreenSize() const { return _screenSize; }
private:
	float _screenSize;
};

void saveProducts(std::ofstream& ofs, Product** products, int length)
{
	ofs.write((char*)&length, sizeof(length));
	for (int i = 0; i < length; ++i)
	{
		products[i]->saveType(ofs);
		products[i]->save(ofs);
	}
}

// Ex4 - a

class CountConsoles
{
public:
	CountConsoles() : _count(0) {}
	void operator()(Product* product)
	{
		Console* c = dynamic_cast<Console*>(product);
		if (c != NULL)
			++_count;
	}
	int getCount() const { return _count; }
private:
	int _count;
};

class ScreenSizeAverage
{
public:
	ScreenSizeAverage() : _count(0), _sum(0) {}
	void operator()(Product* product)
	{
		SmartWatch* c = dynamic_cast<SmartWatch*>(product);
		if (c != NULL)
		{
			++_count;
			_sum += c->getScreenSize();
		}
	}
	float getAverage() const { return _sum / _count; }
private:
	int _count;
	float _sum;
};

class CapacitySum
{
public:
	CapacitySum() : _sum(0) {}
	void operator()(Product* product)
	{
		ConsoleSmartWatchCommon* c = dynamic_cast<ConsoleSmartWatchCommon*>(product);
		if (c != NULL)
			_sum += c->getCapacity();
	}
	int getSum() const { return _sum; }
private:
	int _sum;
};

// Ex4 - b

template <class Func>
void forEachProduct(Product** products, int size, Func& f)
{
	for (int i = 0; i < size; ++i)
		f(products[i]);
}

template <class T>
class QueueNode
{
public:
	QueueNode(T* data) : _data(data), _next(NULL) {}
	~QueueNode() { delete _data; }
	void setNext(QueueNode<T>* next) { _next = next; }
	T* getData() const { return _data; }
	QueueNode<T>* getNext() const { return _next; }
private:
	QueueNode<T>* _next;
	T* _data;
};
template <class T>
class Queue
{
public:
	Queue() : _head(NULL), _tail(NULL) {}
	~Queue()
	{
		while (_head != NULL)
		{
			QueueNode<T>* temp = _head;
			_head = _head->getNext();
			delete temp;
		}
	}
	void enqueue(const T& t)
	{
		QueueNode<T>* newItem = new QueueNode<T>(new T(t));
		if (_head == NULL)
			_tail = _head = newItem;
		else
		{
			_tail->setNext(newItem);
			_tail = newItem;
		}
	}
	const T& top()
	{
		if (_head == NULL)
			throw "Empty queue";
		return *_head->getData();
	}
	void dequeue()
	{
		if (_head == NULL)
			throw "Empty queue";
		QueueNode<T>* temp = _head;
		_head = _head->getNext();
		delete temp;
	}
	bool isEmpty() const { return _head == NULL; }
private:
	QueueNode<T>* _head, * _tail;
};
