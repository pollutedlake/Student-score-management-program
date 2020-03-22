#include "framework.h"
#include "GlobalValue.h"
#pragma warning(disable: 4996)

vector<Student> g_StList;

HINSTANCE g_hInst;
HWND g_hWnd = NULL;

int g_SelChangeIdx = -1;
EditState g_BtnState = INPUT_ST;

void LoadList(vector<Student>* a_SdtList)
{
	//------ 파일 로딩
	FILE* a_rPF = fopen("MySave.abc", "rb");
	if (a_rPF != NULL) {
		int Count = 0;
		fread(&Count, sizeof(int), 1, a_rPF);

		Student a_Node;
		for (int aa = 0; aa < Count; aa++) {
			int a_strCount = 0;
			fread(&a_strCount, sizeof(int), 1, a_rPF);
			if (0 < a_strCount) {
				fread(a_Node.m_Name, a_strCount, 1, a_rPF);
			}

			fread(&a_Node.m_Kor, sizeof(int), 1, a_rPF);
			fread(&a_Node.m_Eng, sizeof(int), 1, a_rPF);
			fread(&a_Node.m_Math, sizeof(int), 1, a_rPF);
			a_Node.m_Total = a_Node.m_Kor + a_Node.m_Eng + a_Node.m_Math;
			a_Node.m_Avg = a_Node.m_Total / 3.0f;
			a_SdtList->push_back(a_Node);
		}	// for (int aa = 0; aa < Count; aa++)

		fclose(a_rPF);
	}	// if (a_rPF != NULL)
	//------ 파일 로딩
}

void SaveList(vector<Student>* a_SdtList)
{
	//------ 파일 저장
	FILE* a_wPF = fopen("MySave.abc", "wb");
	if (a_wPF != NULL) {
		int Count = (*a_SdtList).size();
		fwrite(&Count, sizeof(int), 1, a_wPF);

		for (int aa = 0; aa < Count; aa++) {
			int a_StrCount = (_tcslen((*a_SdtList)[aa].m_Name) + 1) * sizeof(TCHAR);		// _tcslen(a_GetStr) 문자열의 길이 (+ 1) '\0'길이 추가 의미 sizeof(TCHAR) == 2Byte
			if (256 < a_StrCount) {
				a_StrCount = 256;
			}
			fwrite(&a_StrCount, sizeof(int), 1, a_wPF);
			fwrite((*a_SdtList)[aa].m_Name, a_StrCount, 1, a_wPF);

			fwrite(&(*a_SdtList)[aa].m_Kor, sizeof(int), 1, a_wPF);
			fwrite(&(*a_SdtList)[aa].m_Eng, sizeof(int), 1, a_wPF);
			fwrite(&(*a_SdtList)[aa].m_Math, sizeof(int), 1, a_wPF);
		}

		fclose(a_wPF);		// fopen() 짝
	}
	//------ 파일 저장
}
