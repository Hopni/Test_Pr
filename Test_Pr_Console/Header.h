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

struct Node
{
	int info;
	Node *next;
};

class Model : public Element
{
	Node* tail;
	unsigned size = 0;
public:
	friend class Iter;
	Model()
	{
		tail = NULL;
		size = 0;
	}
	Node* create_Node(int);
	void Push_Front(int);
	int pop_back();
	int pop_front();
	int& Get_Pos(unsigned) const;
	unsigned Size() const;
	void Erase(unsigned);
	void Sort();
	bool Search(int) const;
	wstring Display();
	void Clear();
	Iter* createIter();
	void accept(Visitor& v)
	{
		v.visit(*this);
	}
	~Model()
	{
		Clear();
	}
};

Node *Model::create_Node(int value)
{
	Node *temp;
	temp = new(Node);
	if (temp == NULL)
	{
		return 0;
	}
	else
	{
		temp->info = value;
		temp->next = NULL;
		return temp;
	}
}
void Model::Push_Front(int value)
{
		size++;
		Node *temp, *p;
		temp = create_Node(value);
		if (tail == NULL)
		{
			tail = temp;
			tail->next = NULL;
		}
		else
		{
			p = tail;
			tail = temp;
			tail->next = p;
		}
}
int Model::pop_back()
{
	if (size != 0)
	{
		Node *ptr;
		ptr = tail;
		for (int i = 0; i < size - 1; i++)
		{
			ptr = ptr->next;
		}
		int res = ptr->info;
		ptr = NULL;
		size--;
		return res;
	}
	else
	{
		return NULL;
	}
}
int Model::pop_front()
{
	int res = this->Get_Pos(0);
	this->Erase(0);
	return res;
}
int& Model::Get_Pos(unsigned pos) const
{
	int null = int();
	if (tail == NULL)
	{
		return null;
	}

	Node *ptr;
	ptr = tail;
	if (pos >= 0 && pos < size)
	{
		for (int i = 0; i < pos; i++)
		{
			ptr = ptr->next;
		}
		return ptr->info;
	}
	else
	{
		return null;
	}
}

unsigned Model::Size() const
{
	return size;
}
void Model::Sort()
{
	Node *ptr, *s;
	int value;
	if (tail == NULL)
	{
		return;
	}
	ptr = tail;
	while (ptr != NULL)
	{
		for (s = ptr->next; s != NULL; s = s->next)
			if (ptr->info > s->info)
			{
				value = ptr->info;
				ptr->info = s->info;
				s->info = value;
			}
		ptr = ptr->next;
	}
}
void Model::Erase(unsigned pos)
{
	if (tail == NULL)
		return;
	size--;
	Node *s = tail, *ptr = new Node;
	if (pos == 0)
		tail = s->next;
	else
	{
		if (pos > 0 && pos <= size)
		{
			for (auto i = 1; i < pos; i++)
			{
				ptr = s;
				s = s->next;
			}
			ptr->next = s->next;
		}
		else
		{
			size++;
		}
	}
	free(s);
}

bool Model::Search(int value) const
{
	int pos = 0;
	bool flag = false;
	if (tail == NULL)
	{
		return false;
	}
	Node *s;
	s = tail;
	while (s != NULL)
	{
		pos++;
		if (s->info == value)
		{
			flag = true;
			return true;
		}
		s = s->next;
	}
	if (!flag)
		return false;
}

wstring Model::Display()
{
	basic_stringstream<TCHAR> str;
	for (int i = 0; i < this->size; i++)
	{
		str << _T(' ') << this->Get_Pos(i);
	}
	return str.str();
}

void Model::Clear()
{
	while (tail != NULL)
		Erase(0);
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
		return _ptr->Get_Pos(_index);
	}
};

Iter* Model::createIter()
{
	return new Iter(this);
}

class Min : public Visitor
{
	double min;
	void visit(Model& ref)
	{
		Iter it(&ref);
		it.First();
		min = it.currentItem();
		for (; !it.isDone(); it.Next())
		{
			if (min > it.currentItem())
			{
				min = it.currentItem();
			}
		}
	}
};

class Max : public Visitor
{
	double max;
	void visit(Model& ref)
	{
		Iter it(&ref);
		it.First();
		max = it.currentItem();
		for (; !it.isDone(); it.Next())
		{
			if (max > it.currentItem())
			{
				max = it.currentItem();
			}
		}
	}
};