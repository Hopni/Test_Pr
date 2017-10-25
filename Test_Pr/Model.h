#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
using namespace std;

class Iter;
class Model;

class Visitor
{
public:
	virtual void visit(Model& ref) = 0;
	virtual ~Visitor() = default;
};

class Element
{
public:
	virtual void accept(Visitor& v) = 0;
	virtual ~Element() = default;
};

wstring toString(Model&);

class Model
{
	int *data;
	int size;
	int capacity;
public:
	friend class Iter;
	Model()
	{
		size = 0;
		capacity = 10;
		data = new int[capacity];
	}
	void push_back(int);
	wstring pop_front();
	int get_pos(int);
	wstring display();
	Iter* create_Iter();
};

void Model::push_back(int item)
{
	if (size + 1 <= capacity)
	{
		data[size] = item;
		size++;
	}
	else
	{
		int *buff = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			buff[i] = data[i];
		}
		capacity *= 2;
		data = new int[capacity];
		for (int i = 0; i < size; i++)
		{
			data[i] = buff[i];
		}
		data[size] = item;
		size++;
	}
}

wstring Model::pop_front()
{
	if (size > 0)
	{
		wstring result = to_wstring(data[0]);
		for (int i = 1; i < size; i++)
		{
			data[i - 1] = data[i];
		}
		size--;
		return result;
	}
	else
	{
		return L"Empty";
	}
}

int Model::get_pos(int pos)
{
	if (pos >= 0 && pos < size)
	{
		return data[pos];
	}
}

wstring Model::display()
{
	if (size > 0)
	{
		return toString(*this);
	}
	else
	{
		return L"Empty";
	}
}

class Iter
{
	Model* _ptr;
	int _index;
public:
	Iter(Model* p = NULL)
	{
		_ptr = p;
	}
	void First()
	{
		_index = 0;
	}
	void Next()
	{
		_index++;
	}
	bool isDone()
	{
		return _index == _ptr->size;
	}
	int currentItem()
	{
		return _ptr->get_pos(_index);
	}
};

Iter* Model::create_Iter()
{
	return new Iter(this);
}

class Sum : public Visitor
{
	int sum = 0;
public:
	void visit(Model& ref)
	{
		Iter it(&ref);
		for (it.First(); !it.isDone(); it.Next())
		{
			sum += it.currentItem();
		}
	}
	wstring display()
	{
		return to_wstring(sum);
	}
};


wstring toString(Model& m)
{
	basic_stringstream<TCHAR> str;
	Iter it(&m);
	for (it.First(); !it.isDone(); it.Next())
	{
		str << _T(' ') << it.currentItem();
	}
	return str.str();
}