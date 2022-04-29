#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"


CONST CHAR* string[] = { "This", "is", "my", "first", "Combo", "Box" };
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR LpCmdLine, int nCmdShou)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)string[i]);
			}
		}
			break;
	case WM_COMMAND: 
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, WM_GETTEXT, 8, (LPARAM)sz_buffer);
			CHAR sz_msg[SIZE] = {};
			sprintf(sz_msg, "You take %d, number %s", i, sz_buffer);
			MessageBox(hwnd, sz_msg, "Info", MB_OK | MB_ICONINFORMATION);
		}
		break;
		/*case IDC_ADD:

		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			for (int i = 0; i < sizeof(string) / sizeof(string[0])+1; i++)
			{
				SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)string[i]);
			}
		}*/
			
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}

	}		
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}

	return FALSE;
}