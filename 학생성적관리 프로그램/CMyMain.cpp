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

	HWND a_RefHwnd = CreateWindow(_T("button"), _T("�Է�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 10, 100, 30, a_hWnd, (HMENU)IDC_INPUTSHOWBTN, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("������"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 10, 100, 30, a_hWnd, (HMENU)IDC_SORTTEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 290, 10, 100, 30, a_hWnd, (HMENU)IDC_DELETETEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	a_RefHwnd = CreateWindow(_T("button"), _T("���ø�ϼ���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 450, 10, 100, 30, a_hWnd, (HMENU)IDC_EDITTEXT, hInst, NULL);
	m_WinList.push_back(a_RefHwnd);

	//------ �÷��� �ִ� ����Ʈ ��Ʈ�� �����
	// �÷��� �ִ� ����Ʈ ��Ʈ�� ����� #include <CommCtrl.h> �ʿ�
	//// Ȯ�彺Ÿ�� ����
	// | LVS_SHOWSELALWAYS <-- ��Ŀ���� ��Ȱ��ȭ �Ǿ�� ���û��°� ���̵��� �ϴ� �ɼ�
	// | LVS_SINGLESEL <--- �̱� ���� �ɼ� ����Ʈ�� ��Ƽ����
	m_hListView = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 20, 100, 540, 400, g_hWnd, (HMENU)IDC_LISTVIEW, hInst, NULL);
	//// Ȯ�彺Ÿ�� ����
	ListView_SetExtendedListViewStyle(m_hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_CENTER;
	COL.cx = 140;
	COL.pszText = (LPWSTR)L"�л��̸�";		// ù ��° ���
	COL.iSubItem = 0;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"��������";		// �� ��° ���
	COL.iSubItem = 1;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"��������";		// �� ��° ���
	COL.iSubItem = 2;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);		// ����°���� (WPARAM)2 �÷� �ε��� ---> �� ���� ���� ���� �տ������� ���´�. Ŭ���� �������� ���´�.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"��������";		// �� ��° ���
	COL.iSubItem = 3;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);		// �׹�°���� (WPARAM)3 �÷� �ε��� ---> �� ���� ���� ���� �տ������� ���´�. Ŭ���� �������� ���´�.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"����";		// �ټ� ��° ���
	COL.iSubItem = 4;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);		// �ټ���°���� (WPARAM)4 �÷� �ε��� ---> �� ���� ���� ���� �տ������� ���´�. Ŭ���� �������� ���´�.
	COL.cx = 80;
	COL.pszText = (LPWSTR)L"���";		// ���� ��° ���
	COL.iSubItem = 5;
	SendMessage(m_hListView, LVM_INSERTCOLUMN, 5, (LPARAM)&COL);		// ���� ��° ��� (WPARAM)5 �÷� �ε��� ---> �� ���� ���� ���� �տ������� ���´�. Ŭ���� �������� ���´�.
	//------ �÷��� �ִ� ����Ʈ ��Ʈ�� �����

	ReStoreListCtrl();
}

void CMyMain::MainUpdate()
{
}

void CMyMain::MainRender(HDC a_MainDC)
{
	if (0 <= g_SelChangeIdx && g_SelChangeIdx < g_StList.size()) {
		static TCHAR a_Temp[256];
		_stprintf_s(a_Temp, _T("%s : ����(%d) ����(%d) ����(%d) ����(%d) ����(%.2f)"), g_StList[g_SelChangeIdx].m_Name, g_StList[g_SelChangeIdx].m_Kor, g_StList[g_SelChangeIdx].m_Eng, g_StList[g_SelChangeIdx].m_Math, g_StList[g_SelChangeIdx].m_Total, g_StList[g_SelChangeIdx].m_Avg);
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
		// �޴� ������ ���� �м��մϴ�.
		switch (wmld) {
		case IDC_INPUTSHOWBTN:		// �л� �߰� ��ư
		{
			g_BtnState = INPUT_ST;
			g_SelChangeIdx = -1;		// ���� ���� ���� ǥ���� �ʱ�ȭ�� ���Ͽ�...
			InvalidateRect(g_hWnd, NULL, TRUE);		// ���� ���� ���� ǥ���� �ʱ�ȭ�� ���Ͽ�...

			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, (DLGPROC)CInputDlg::InputDlgProc);
		}
		break;

		case IDC_SORTTEXT:		// ���������� �����Ϥ��� ��ư
		{
			sort(g_StList.begin(), g_StList.end(), MyDownCompare);
			ReStoreListCtrl();		// ����Ʈ�� �ٽ� �׷��ְ�

			g_SelChangeIdx = -1;		// ���� ���� ���� ǥ���� �ʱ�ȭ�� ���Ͽ�...
			InvalidateRect(g_hWnd, NULL, TRUE);		// ���� ���� ���� ǥ���� �ʱ�ȭ�� ���Ͽ�...
		}
		break;

		case IDC_DELETETEXT:		// ���� ��� ���� ��ư
		{
			if (MessageBox(NULL, _T("���� ���� �Ͻðڽ��ϱ�?"), _T("Ȯ��"), MB_YESNO) == IDYES) {
				int a_Idx = ListView_GetNextItem(m_hListView, -1, LVNI_ALL | LVNI_SELECTED);

				// if (a_Idx < 0) �ƹ��͵� ���õǾ� ���� ���� ����
				if (0 <= a_Idx && a_Idx < g_StList.size()) {
					ListView_DeleteItem(m_hListView, a_Idx);

					g_StList.erase(g_StList.begin() + a_Idx);
					SaveList(&g_StList);

					g_SelChangeIdx = -1;
					InvalidateRect(g_hWnd, NULL, TRUE);
				}
			}	// if (MessageBox(NULL, _T("���� ���� �Ͻðڽ��ϱ�?"), _T("Ȯ��"), MB_YESNO) == IDYES)
		}
		break;

		case IDC_EDITTEXT:		// ���� ��� ���� ��ư
		{
			g_BtnState = EDIT_ST;
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), g_hWnd, (DLGPROC)CInputDlg::InputDlgProc);		// ���̾˷α׹ڽ�
		}
		break;
		}	// switch (wmld)
	}	// case WM_COMMAND:
	break;

	//------ ����Ʈ ��Ʈ�� ��带 �������� �� �߻��Ǵ� �޽��� ó�� �κ�
	case WM_NOTIFY:
		g_SelChangeIdx = -1;
		LPNMHDR hdr;
		LPNMLISTVIEW nlv;
		LPNMITEMACTIVATE nla;
		hdr = (LPNMHDR)lParam;
		nlv = (LPNMLISTVIEW)lParam;

		if (hdr->hwndFrom == m_hListView) {		// ���� �����찡 ����Ʈ��Ʈ���̶��
			if (hdr->code = LVN_ITEMCHANGED) {		// �������� ���õ��� ��
				if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED)) {
					g_SelChangeIdx = ListView_GetNextItem(m_hListView, -1, LVNI_ALL | LVNI_SELECTED);
					if (0 <= g_SelChangeIdx) {		// ����Ʈ���� ���� ���õǾ� �ִ� ���¶��...
						InvalidateRect(g_hWnd, NULL, TRUE);
					}
				}	// if (nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
			}	// if (hdr->code = LVN_ITEMCHANGED)
		}
		break;
		//------ ����Ʈ ��Ʈ�� ��带 �������� �� �߻��Ǵ� �޽��� ó�� �κ�
	}	// switch (message)
}	// void CMyMain::On_MessageHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

void CMyMain::ReStoreListCtrl()
{
	ListView_DeleteAllItems(m_hListView);		// �켱 ����Ʈ ��� ����

	// ������ ���
	LVITEM LI;
	LI.mask = LVIF_TEXT;
	LI.state = 0;
	LI.stateMask = 0;

	//------ ��ü ��ȯ
	if (!g_StList.empty()) {
		TCHAR a_strNum[128];
		for (int aa = 0; aa < g_StList.size(); aa++) {
			LI.iItem = aa;
			LI.iSubItem = 0;
			LI.pszText = g_StList[aa].m_Name;		// �л��̸�
			SendMessage(m_hListView, LVM_INSERTITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Kor, a_strNum, 10);		// ��������
			LI.iSubItem = 1;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Eng, a_strNum, 10);		// ��������
			LI.iSubItem = 2;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Math, a_strNum, 10);		// ��������
			LI.iSubItem = 3;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			_itot_s(g_StList[aa].m_Total, a_strNum, 10);		// ����
			LI.iSubItem = 4;
			LI.pszText = a_strNum;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);

			TCHAR a_TotalStr[128];
			_stprintf_s(a_TotalStr, _T("%.2f"), g_StList[aa].m_Avg);		// ���
			LI.iSubItem = 5;
			LI.pszText = a_TotalStr;
			SendMessage(m_hListView, LVM_SETITEM, 0, (LPARAM)&LI);
		}

		SendMessage(m_hListView, WM_VSCROLL, SB_BOTTOM, 0);		// ��ũ�� �� �Ʒ��� ���� �ϱ�...
	}	// if (!m_ItemList.empty())
	//------ ��ü ��ȯ
}

bool CMyMain::MyDownCompare(const Student& a, const Student& b)
{
	return a.m_Total > b.m_Total;		// �������� ����(ū������ ���������� ����)
}

CMyMain g_MyMain;