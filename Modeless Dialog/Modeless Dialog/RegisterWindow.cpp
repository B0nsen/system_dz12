
#include "RegisterWindow.h"
#include <iostream>


CRegisterWindow* CRegisterWindow::ptr = NULL;
HWND CRegisterWindow::hAddDialog = NULL;

CRegisterWindow::CRegisterWindow(void)
{
	ptr = this;
}

CRegisterWindow::~CRegisterWindow(void)
{

}

void CRegisterWindow::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CRegisterWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_REGISTER_LOGIN);
	hEdit2 = GetDlgItem(hwnd, IDC_REGISTER_PASSWORD);
	return TRUE;
}


void CRegisterWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	char str[50];
	std::ofstream login("Login.txt");
	std::ofstream password("Password.txt");
	if (!login.is_open() || !password.is_open())
	{
		return;
	}
	if (id == IDC_REGISTER_CONFIRM)
	{
		GetWindowText(hEdit1, (LPWSTR)str, 50);
		MessageBox(hwnd, (LPWSTR)str, L"1", MB_OK);
		login << str;
		login << '\n';
		GetWindowText(hEdit2, (LPWSTR)str, 50);
		password << str;
		password << '\n';
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
	else if (id == IDC_REGISTER_CANCEL)
	{
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CRegisterWindow::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}



