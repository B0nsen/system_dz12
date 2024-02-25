
#include "LoginWindow.h"
#include "MainWindow.h"
#include "header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

CLoginWindow* CLoginWindow::ptr = NULL;
HWND CLoginWindow::hAddDialog = NULL;

CLoginWindow::CLoginWindow(void)
{
	ptr = this;
}

CLoginWindow::~CLoginWindow(void)
{

}

void CLoginWindow::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CLoginWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEdit1 = GetDlgItem(hwnd, IDC_LOGIN_LOGIN);
	hEdit2 = GetDlgItem(hwnd, IDC_LOGIN_PASSWORD);
	return TRUE;
}


void CLoginWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	_TCHAR login_char[50], password_char[50];
	_TCHAR temp[50];
	char file_login[50], file_password[50];
	bool isLogined = false;
	std::ifstream login("Login.txt");
	std::ifstream password("Password.txt");

	if (id == IDC_LOGIN_CONFIRM)
	{
		GetWindowText(hEdit1, (LPWSTR)login_char, 50);
		GetWindowText(hEdit2, (LPWSTR)password_char, 50);
		while (!login.eof())
		{
			login >> file_login;
			password >> file_password;

			//ƒанный блок кода был вз€т из интернета
			wchar_t wstr[50];
			wchar_t wstr2[50];
			size_t convertedChars;
			mbstowcs_s(&convertedChars, wstr, file_login, _TRUNCATE);
			mbstowcs_s(&convertedChars, wstr2, file_password, _TRUNCATE);


			MessageBox(hwnd, (LPCWSTR)login_char, (LPCWSTR)wstr, MB_OK);
			if (!_tcscmp(login_char, wstr) && !_tcscmp(password_char, wstr2))
			{
				isLogined = true;
				MessageBox(hwnd, L"Login", L"2", MB_OK);
				break;
			}
		}
		if (!isLogined)
		{
			MessageBox(hwnd, L"Login", L"Login failed", MB_OK);
		}
	}
	else if (id == IDC_LOGIN_CANCEL)
	{
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CLoginWindow::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}