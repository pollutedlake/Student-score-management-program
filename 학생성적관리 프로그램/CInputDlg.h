#pragma once
class CInputDlg
{
	int m_SelIndex = -1;

public:
	CInputDlg();
	~CInputDlg();

public:
	void On_Initdialog(HWND hDlg);
	void On_IDOK(HWND hDlg);
	void On_MessageHook(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static INT_PTR CALLBACK InputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

extern CInputDlg g_InputDlg;