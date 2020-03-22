#include"framework.h"
#include "CMyMain.h"
#include "resource.h"
#include "CInputDlg.h"
#include "GlobalValue.h"
#include <CommCtrl.h>
#include <algorithm>

CMyMain::CMyMain()
{
}

CMyMain::~CMyMain()
{
}

void CMyMain::MainInit(HINSTANCE hInst, HWND a_hWnd)
{
	LoadList(&g_StList);

	HWND a_RefHwnd = CreateWindow(_T("button"), _T("입력"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 100, 30, a_hWnd, (HMENU)IDC_INPUTSHOWBTN, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("총점순"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 10, 100, 30, a_hWnd, (HMENU)IDC_SORTTEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("삭제"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 290, 10, 100, 30, a_hWnd, (HMENU)IDC_DELETETEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("선택목록수정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450, 10, 100, 30, a_hWnd, (HMENU)IDC_EDITTEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	//------ 컬럼이 있는 리스트 컨트롤 만들기
	// 컬럼이 있는 리스트 컨트롤 만들기 #include <CommCtrl.h> 필요
	//// 확장스타일 적용
	// | LVS_SHOWSELALWAYS <-- 포커스가 비활성화 되어라도 선택상태가 보이도록 하는 옵션
	// | LVS_SINGLESEL <--- 싱글 선택 옵션 디폴트는 멀티선택
	m_hListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 20, 100, 540, 400, g_hWnd, (HMENU)IDC_LISTVIEW, hInst, NULL);
	//// 확장스타일 적용
	ListView_SetExtendedListViewStyle(m_hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_CENTER;
	COL.cx = 140;
	COL.pszText = (LPWSTR)L"학생이름";		// 첫 번째 헤더
	COL.iSubItem = 0;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"국어점수";		// 두 번째 헤더
	COL.iSubItem = 1;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"영어점수";		// 세 번째 헤더
	COL.iSubItem = 2;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);		// 세번째인자 (WPARAM)2 컬럼 인덱스 ---> 이 값이 작을 수록 앞에서부터 나온다. 클수록 뒤쪽으로 나온다.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"수학점수";		// 네 번째 헤더
	COL.iSubItem = 3;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);		// 네번째인자 (WPARAM)3 컬럼 인덱스 ---> 이 값이 작을 수록 앞에서부터 나온다. 클수록 뒤쪽으로 나온다.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"총점";		// 다섯 번째 헤더
	COL.iSubItem = 4;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);		// 다섯번째인자 (WPARAM)4 컬럼 인덱스 ---> 이 값이 작을 수록 앞에서부터 나온다. 클수록 뒤쪽으로 나온다.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"평균";		// 여섯 번째 헤더
	COL.iSubItem = 5;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 5, (LPARAM)&COL);		// 여섯 번째 헤더 (WPARAM)5 컬럼 인덱스 ---> 이 값이 작을 수록 앞에서부터 나온다. 클수록 뒤쪽으로 나온다.
	//------ 컬럼이 있는 리스트 컨트롤 만들기

	ReStoreListCtrl();
}

void CMyMain::MainUpdate()
{
}

void CMyMain::MainRender(HDC a_MainDC)
{
	if (0 <= g_SelChangeIdx && g_SelChangeIdx < g_StList.size()) {
		static TCHAR a_Temp[256];
		_stprintf_s(a_Temp, _T("%s : 국어(%d) 영어(%d) 수학(%d) 총점(%d) 형균(%.2f)"), g_StList[g_SelChangeIdx].m_Name, g_StList[g_SelChangeIdx].m_Kor, g_StList[g_SelChangeIdx].m_Eng, g_StList[g_SelChangeIdx].m_Math, g_StList[g_SelChangeIdx].m_Total, g_StList[g_SelChangeIdx].m_Avg);
		TextOut(a_MainDC, 600, 100, a_Temp, _tcslen(a_Temp));
	}	// if (0 <= g_SelChangeIdx && g_SelChangeIdx < g_StList.size())
}

void CMyMain::MainDestroy()
{
	if (0 < (int)m_WinList.size()) {
		for (int ii = 0; ii < m_WinList.size(); ii++) {
			if (IsWindow(m_WinList[ii])) {
				DestroyWindow(m_WinList[ii]);
				m_WinList[ii] = NULL;
			}
		}
		m_WinList.clear();
	}   // if (0 < (int)m_WinList.size())

	if (IsWindow(m_hListView)) {
		DestroyWindow(m_hListView);
		m_hListView = NULL;
	}
}

void CMyMain::On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND:
	{
		int wmld = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmld) {
		case IDC_INPUTSHOWBTN:		// 학생 추가 버튼
		{
			g_BtnState = INPUT_ST;
			g_SelChangeIdx = -1;		// 선택 상태 정보 표시의 초기화를 위하여...
			InvalidateRect(g_hWnd, NULL, TRUE);		// 선택 상태 정보 표시의 초기화를 위하여...

			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, (DLGPROC)CInputDlg::InputDlgProc);
		}
		break;

		case IDC_SORTTEXT:		// 총점순으로 정렬하ㅏ기 버튼
		{
			sort(g_StList.begin(), g_StList.end(), MyDownCompare);
			ReStoreListCtrl();		// 리스트뷰 다시 그려주고

			g_SelChangeIdx = -1;		// 선택 상태 정보 표시의 초기화를 위하여...
			InvalidateRect(g_hWnd, NULL, TRUE);		// 선택 상태 정보 표시의 초기화를 위하여...
		}
		break;

		case IDC_DELETETEXT:		// 선택 목록 삭제 버튼
		{
			if (MessageBox(NULL, _T("정말 삭제 하시겠습니까?"), _T("확인"), MB_YESNO) == IDYES) {
				int a_Idx = ListView_GetNextItem(m_hListView, -1, LVNI_ALL | LVNI_SELECTED);

				// if (a_Idx < 0) 아무것도 선택되어 있지 않은 상태
				if (0 <= a_Idx && a_Idx < g_StList.size()) {
					ListView_DeleteItem(m_hListView, a_Idx);

					g_StList.erase(g_StList.begin() + a_Idx);
					SaveList(&g_StList);

					g_SelChangeIdx = -1;
					InvalidateRect(g_hWnd, NULL, TRUE);
				}
			}	// if (MessageBox(NULL, _T("정말 삭제 하시겠습니까?"), _T("확인"), MB_YESNO) == IDYES)
		}
		break;

		case IDC_EDITTEXT:		// 선택 목록 수정 버튼
		{
			g_BtnState = EDIT_ST;
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, (DLGPROC)CInputDlg::InputDlgProc);		// 다이알로그박스
		}
		break;
		}	// switch (wmld)
	}	// case WM_COMMAND:
	break;

	//------ 리스트 컨트롤 노드를 선택했을 때 발생되는 메시지 처리 부분
	case WM_NOTIFY:
		g_SelChangeIdx = -1;
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		LPNMITEMACTIVATE nla;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		if (hdr->hwndFrom == m_hListView) {		// 현재 윈도우가 리스트컨트롤이라면
			if (hdr->code = LVN_ITEMCHANGED) {		// 아이템이 선택됐을 때
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					g_SelChangeIdx = ListView_GetNextItem(m_hListView, -1, LVNI_ALL | LVNI_SELECTED);
					if (0 <= g_SelChangeIdx) {		// 리스트에서 뭔가 선택되어 있는 상태라면...
						InvalidateRect(g_hWnd, NULL, TRUE);
					}
				}	// if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
			}	// if (hdr->code = LVN_ITEMCHANGED)
		}
		break;
		//------ 리스트 컨트롤 노드를 선택했을 때 발생되는 메시지 처리 부분
	}	// switch (message)
}	// void CMyMain::On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

void CMyMain::ReStoreListCtrl()
{
	ListView_DeleteAllItems(m_hListView);		// 우선 리스트 모두 삭제

	// 아이템 등록
	LVITEM LI;
	LI.mask = LVIF_TEXT;
	LI.state = 0;
	LI.stateMask = 0;

	//------ 전체 순환
	if (!g_StList.empty()) {
		TCHAR a_strNum[128];
		for (int aa = 0; aa < g_StList.size(); aa++) {
			LI.iItem = aa;
			LI.iSubItem = 0;
			LI.pszText = g_StList[aa].m_Name;		// 학생이름
			SendMessage(m_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Kor, a_strNum, 10);		// 국어점수
			LI.iSubItem = 1;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Eng, a_strNum, 10);		// 영어점수
			LI.iSubItem = 2;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Math, a_strNum, 10);		// 수학점수
			LI.iSubItem = 3;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Total, a_strNum, 10);		// 총점
			LI.iSubItem = 4;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			TCHAR a_TotalStr[128];
			_stprintf_s(a_TotalStr, _T("%.2f"), g_StList[aa].m_Avg);		// 평균
			LI.iSubItem = 5;
			LI.pszText = a_TotalStr;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
		}

		SendMessage(m_hListView, WM_VSCROLL, SB_BOTTOM, 0);		// 스크롤 맨 아래로 가게 하기...
	}	// if (!m_ItemList.empty())
	//------ 전체 순환
}

bool CMyMain::MyDownCompare(const Student& a, const Student& b)
{
	return a.m_Total > b.m_Total;		// 내림차순 정렬(큰값에서 작은값으로 정렬)
}

CMyMain g_MyMain;