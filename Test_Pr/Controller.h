#pragma once
#include "TestPr.h"
#include "stdafx.h"
#include "Model.h"

class Controller
{
	Model model;
public:
	Controller() {};
	Controller(Model& m)
	{
		model = m;
	}
	wstring Push(double item)
	{
		model.push_back(item);
		return model.display();
	}
	wstring Pop()
	{
		return model.pop_front();
	}
	wstring Display()
	{
		return model.display();
	}
	wstring sum()
	{
		Sum s;
		s.visit(model);
		return s.display();
	}
};