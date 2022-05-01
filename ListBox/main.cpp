#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* string[] = { "This", "is", "my", "first", "List", "Box", "1024", "256" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShou)
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
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}		
		SendMessage(hListBox, LB_SETCURSEL, 4, 0);		
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDADD_BUTTON:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, DlgProc, 0);
		}
		break;
		case IDOK_INPUT:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			HWND parent = GetParent(hwnd);
			HWND hList1 = GetDlgItem(parent, IDC_LIST1);
			SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			EndDialog(hwnd, 0);
		}
		break;
		case IDOK:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
				CHAR sz_msg[SIZE] = {};
				sprintf(sz_msg, "You take %d, number %s", i, sz_buffer);
				MessageBox(hwnd, sz_msg, "Info", MB_OK | MB_ICONINFORMATION);
			}
			break;		
		case IDDELETE:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);				
			}
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}

