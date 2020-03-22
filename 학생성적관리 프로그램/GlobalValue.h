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

extern int g_SelChangeIdx;		// 입력 다이알로그 띄울 때 메인 DC리스트에 선택되어 있는 인덱스를 넘기기 위한 용도
extern EditState g_BtnState;	// 입력 다이알로그 띄울 때 어떤 모드로 띄운건지를 나타내는 변수

void LoadList(vector<Student>* a_SdtList);
void SaveList(vector<Student>* a_SdtList);
