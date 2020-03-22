#pragma once

#include <vector>
using namespace std;

#define IDC_LISTVIEW		1150		// 리스트 컨트롤 ID

#define IDC_INPUTSHOWBTN	1100		// 버튼컨트롤 ID
#define IDC_SORTTEXT		1101
#define IDC_DELETETEXT		1102
#define IDC_EDITTEXT		1103

class Student;

class CMyMain
{
	vector<HWND> m_WinList;

public:
	HWND m_hListView = NULL;		// 리스트뷰 핸들 저장 하는 변수

public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(HINSTANCE hInst, HWND a_hWnd);		// 초기화 함수
	void MainUpdate();									// 게임의 연산 담당부분
	void MainRender(HDC a_MainDC);						// 게임의 렌더링 부분
	void MainDestroy();

	void On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// 메인 윈도우 메시지를 가로채서 처리해 주기 위한 함수

	void ReStoreListCtrl();

	static bool MyDownCompare(const Student& a, const Student& b);
};

extern CMyMain g_MyMain;