// TestPr.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestPr.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

// Forward declarations of functions included in this code module:

Model model;
Controller cnt(model);
View view(cnt);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);
	return NULL;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return view.ButtonEvents(hDlg, message, wParam, lParam);
}
