// TestPrConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include <iostream>
using namespace std;

int main()
{
	Model a;
	a.Push_Front(5);
	a.Push_Front(7);
	a.Push_Front(10);
	cout << a.pop_back() << endl;
	cout << a.pop_back() << endl;
	cout << a.pop_back() << endl;
	cout << a.pop_back() << endl;
}

