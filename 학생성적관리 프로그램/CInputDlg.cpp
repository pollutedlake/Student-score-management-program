#include "framework.h"
#include "CInputDlg.h"
#include "resource.h"
#include "GlobalValue.h"
#include "CMyMain.h"
#include <CommCtrl.h>

CInputDlg::CInputDlg()
{
}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::On_Initdialog(HWND hDlg)
{
	//--- 부모 윈도우 기준으로 적당한 위치(오른쪽상단)에 가서 붙도록 설정하는 방법
	static RECT a_wRT;
	static POINT g_MainWPos;
	static POINT g_MWTopLeft;
	static POINT g_ChildWPos;
	static POINT g_DlgSize;

	RECT a_dRT;
	GetWindowRect(hDlg, &a_dRT);
	g_DlgSize.x = a_dRT.right - a_dRT.left;
	g_DlgSize.y = a_dRT.bottom - a_dRT.top;

	GetWindowRect(g_hWnd, &a_wRT);
	g_MainWPos.x = a_wRT.left;
	g_MainWPos.y = a_wRT.top;

	g_MWTopLeft.x = 0;
	g_MWTopLeft.y = 0;
	ClientToScreen(g_hWnd, &g_MWTopLeft);

	g_ChildWPos.x = a_wRT.right - g_DlgSize.x;
	g_ChildWPos.y = g_MWTopLeft.y;

	SetWindowPos(hDlg, NULL, g_ChildWPos.x, g_ChildWPos.y, 0, 0, SWP_NOSIZE);
	// MoveWindow : 부모 윈도우 좌표를 기준으로 움직인다.
	// SetWindowPos : 바탕화면 좌표 기중으로 움직인다.
	//--- 부모 윈도우 기준으로 적당한 위치(오른쪽상단)에 가서 붙도록 설정하는 방법

	//------ 리스트 컨트롤 선택상태 초기화 및 다이알로그의 에디트 박스 초기화 부분
	if (g_BtnState == INPUT_ST) {
		// 아이템 번호 == -1 모두 라는 뜻
		ListView_SetItemState(g_MyMain.m_hListView, -1, 0, LVIS_SELECTED | LVIS_FOCUSED);		// <--- 선택 해제

	}
	else if (g_BtnState == EDIT_ST) {
		int a_Idx = ListView_GetNextItem(g_MyMain.m_hListView, -1, LVNI_ALL | LVNI_SELECTED);
		// if (a_Idx < 0) 아무것도 선택되어 있지 않은 상태
		// ---> 리스트 컨트롤로부터 직접 값을 얻어오는 방법
		if (0 <= a_Idx) {
			TCHAR a_NameStr[256];
			TCHAR a_KorStr[256];
			TCHAR a_EngStr[256];
			TCHAR a_MathStr[256];

			ListView_GetItemText(g_MyMain.m_hListView, a_Idx, 0, a_NameStr, 256);
			ListView_GetItemText(g_MyMain.m_hListView, a_Idx, 1, a_KorStr, 256);
			ListView_GetItemText(g_MyMain.m_hListView, a_Idx, 2, a_EngStr, 256);
			ListView_GetItemText(g_MyMain.m_hListView, a_Idx, 3, a_MathStr, 256);

			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_NAME), (LPTSTR)a_NameStr);
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_KOR), (LPTSTR)a_KorStr);
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_ENG), (LPTSTR)a_EngStr);
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MATH), (LPTSTR)a_MathStr);
		}	// if (0 <= a_Idx)

		m_SelIndex = a_Idx;
	}	// if (g_BtnState == EDIT_ST)
	//------ 리스트 컨트롤 선택상태 초기화 및 다이알로그의 에디트 박스 초기화 부분
}	// void CInputDlg::On_Initdialog(HWND hDlg)

void CInputDlg::On_IDOK(HWND hDlg)
{
	TCHAR a_NameStr[256];
	TCHAR a_KorStr[256];
	TCHAR a_EngStr[256];
	TCHAR a_MathStr[256];

	HWND a_hName = GetDlgItem(hDlg, IDC_EDIT_NAME);
	GetWindowText(a_hName, (LPTSTR)a_NameStr, sizeof(a_NameStr));

	GetWindowText(GetDlgItem(hDlg, IDC_EDIT_KOR), (LPTSTR)a_KorStr, sizeof(a_KorStr));
	GetWindowText(GetDlgItem(hDlg, IDC_EDIT_ENG), (LPTSTR)a_EngStr, sizeof(a_EngStr));
	GetWindowText(GetDlgItem(hDlg, IDC_EDIT_MATH), (LPTSTR)a_MathStr, sizeof(a_MathStr));

	if (a_NameStr[0] != '\0' && a_KorStr[0] != '\0' && a_EngStr[0] != '\0' && a_MathStr[0] != '\0' && a_KorStr != _T("") && a_EngStr != _T("") && a_MathStr != _T("")) {
		int a_Kor = _wtoi(a_KorStr);
		int a_Eng = _wtoi(a_EngStr);
		int a_Math = _wtoi(a_MathStr);

		if (0 <= a_Kor && a_Kor <= 100 && 0 <= a_Eng && a_Eng <= 100 && 0 <= a_Math && a_Math <= 100) {
			if (g_BtnState == INPUT_ST) {
				Student a_StNode;
				_tcscpy_s(a_StNode.m_Name, a_NameStr);
				a_StNode.m_Kor = a_Kor;
				a_StNode.m_Eng = a_Eng;
				a_StNode.m_Math = a_Math;
				a_StNode.m_Total = a_Kor + a_Eng + a_Math;
				a_StNode.m_Avg = a_StNode.m_Total / 3.0f;
				g_StList.push_back(a_StNode);

				g_MyMain.ReStoreListCtrl();

				SaveList(&g_StList);
			}
			else if (g_BtnState == EDIT_ST) {
				if (0 <= m_SelIndex) {
					g_StList[m_SelIndex].m_Kor = a_Kor;
					g_StList[m_SelIndex].m_Eng = a_Eng;
					g_StList[m_SelIndex].m_Math = a_Math;
					g_StList[m_SelIndex].m_Total = a_Kor + a_Math + a_Eng;
					g_StList[m_SelIndex].m_Avg = g_StList[m_SelIndex].m_Total / 3.0f;

					TCHAR a_LvKorStr[256];
					TCHAR a_LvEngStr[256];
					TCHAR a_LvMathStr[256];
					TCHAR a_LvTotalStr[256];
					TCHAR a_AvgStr[256];

					_itot_s(g_StList[m_SelIndex].m_Kor, a_LvKorStr, 10);		// 국어점수
					_itot_s(g_StList[m_SelIndex].m_Eng, a_LvEngStr, 10);		// 영어점수
					_itot_s(g_StList[m_SelIndex].m_Math, a_LvMathStr, 10);		// 수학점수
					_itot_s(g_StList[m_SelIndex].m_Total, a_LvTotalStr, 10);	// 총점
					_stprintf_s(a_AvgStr, _T("%.2f"), g_StList[m_SelIndex].m_Avg);		// 평균

					ListView_SetItemText(g_MyMain.m_hListView, m_SelIndex, 1, a_LvKorStr, 256);		// 내용수정
					ListView_SetItemText(g_MyMain.m_hListView, m_SelIndex, 2, a_LvEngStr, 256);
					ListView_SetItemText(g_MyMain.m_hListView, m_SelIndex, 3, a_LvMathStr, 256);
					ListView_SetItemText(g_MyMain.m_hListView, m_SelIndex, 4, a_LvTotalStr, 256);
					ListView_SetItemText(g_MyMain.m_hListView, m_SelIndex, 5, a_AvgStr, 256);

					SaveList(&g_StList);

					InvalidateRect(g_hWnd, NULL, TRUE);
				}	// if (0 <= m_SelIndex)
			}	// else if (g_BtnState == EDIT_ST)
		}	// if (0 <= a_Kor && a_Kor <= 100 &&
	}	// if (a_KorStr != _T("") && a_EngStr != _T("") && a_MathStr != _T(""))
}

void CInputDlg::On_MessageHook(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message) {
		case WM_INITDIALOG:
			On_Initdialog(hDlg);
			break;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				On_IDOK(hDlg);
			}
			break;
	}	// switch (message)
}

INT_PTR CInputDlg::InputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_InputDlg.On_MessageHook(hDlg, message, wParam, lParam);

	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


CInputDlg g_InputDlg;