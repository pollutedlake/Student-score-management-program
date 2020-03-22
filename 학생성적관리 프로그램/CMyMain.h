#pragma once

#include <vector>
using namespace std;

#define IDC_LISTVIEW		1150		// ����Ʈ ��Ʈ�� ID

#define IDC_INPUTSHOWBTN	1100		// ��ư��Ʈ�� ID
#define IDC_SORTTEXT		1101
#define IDC_DELETETEXT		1102
#define IDC_EDITTEXT		1103

class Student;

class CMyMain
{
	vector<HWND> m_WinList;

public:
	HWND m_hListView = NULL;		// ����Ʈ�� �ڵ� ���� �ϴ� ����

public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(HINSTANCE hInst, HWND a_hWnd);		// �ʱ�ȭ �Լ�
	void MainUpdate();									// ������ ���� ���κ�
	void MainRender(HDC a_MainDC);						// ������ ������ �κ�
	void MainDestroy();

	void On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// ���� ������ �޽����� ����ä�� ó���� �ֱ� ���� �Լ�

	void ReStoreListCtrl();

	static bool MyDownCompare(const Student& a, const Student& b);
};

extern CMyMain g_MyMain;