#pragma once

#include <vector>
using namespace std;

enum EditState {
	INPUT_ST,
	SORT_ST,
	DELETE_ST,
	EDIT_ST
};

struct Student {
	TCHAR m_Name[256];
	int m_Kor;
	int m_Eng;
	int m_Math;
	int m_Total;
	float m_Avg;
};

extern vector<Student> g_StList;

extern HINSTANCE g_hInst;
extern HWND g_hWnd;

extern int g_SelChangeIdx;		// �Է� ���̾˷α� ��� �� ���� DC����Ʈ�� ���õǾ� �ִ� �ε����� �ѱ�� ���� �뵵
extern EditState g_BtnState;	// �Է� ���̾˷α� ��� �� � ���� �������� ��Ÿ���� ����

void LoadList(vector<Student>* a_SdtList);
void SaveList(vector<Student>* a_SdtList);
