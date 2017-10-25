#pragma once
#include "TestPr.h"
#include "stdafx.h"
#include "Controller.h"

class View
{
	Controller cnt;
public:
	View() {};
	View(Controller& c)
	{
		cnt = c;
	}
	INT_PTR CALLBACK ButtonEvents(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case IDC_PUSH:
			{
				cnt.Push(GetDlgItemInt(hDlg, IDC_EDIT_PUSH, NULL, true));
				SetDlgItemText(hDlg, IDC_EDIT_PUSH, L" ");
				break;
			}
			case IDC_POP:
			{
				this->Display(cnt.Pop(), hDlg, IDC_EDIT_POP);
				break;
			}
			case IDC_DISPLAY:
			{
				this->Display(cnt.Display(), hDlg, IDC_STATIC_DISPLAY);
				break;
			}
			case IDC_TOSTRING:
			{
				this->Display(cnt.Display(), hDlg, IDC_EDIT_TOSTRING);
				break;
			}
			case IDC_SUM:
			{
				this->Display(cnt.sum(), hDlg, IDC_STATIC_SUM);
				break;
			}
			case IDOK:
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			case IDCANCEL:
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			}
			break;
		}
		return (INT_PTR)FALSE;
	}
	void Display(wstring str, HWND h, int IDC)
	{
		SetDlgItemText(h, IDC, str.c_str());
	}
};