#pragma once
#include "header.h"

class CMainWindow
{
public:
	CMainWindow(void);
public:
	~CMainWindow(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMainWindow* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hEdit1, hStatic1;
	static std::fstream file;
};
