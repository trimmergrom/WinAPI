#include<Windows.h>
#include"resource.h"

CONST CHAR g_szLoginDefaultMessage[] = "������� �����";
CONST CHAR g_szPasswordDefaultMessage[] = "������� ������";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//MessageBox(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), "Hello World!", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP | MB_DEFBUTTON3 | MB_APPLMODAL);
	//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//��������� �������� ����������, ������������ ��������� ��������� ����. 
		//���� case ������������ ������ ��� ������ �������.
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		/*HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);*/
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)g_szLoginDefaultMessage);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)g_szPasswordDefaultMessage);
	}
	break;
	case WM_COMMAND:	//������������ ������� ������ � ����� ��������� � ��������� ����.
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE] = {};
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);


		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "���� ������ ������ OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
			//------------------------
		case IDC_BUTTON_COPY:
		{
			/*CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);*/
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		//------------------------
		case IDC_EDIT_LOGIN:
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				/*	CONST INT SIZE = 256;
					CHAR sz_buffer[SIZE] = {};
					HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);*/
				SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strcmp(sz_buffer, g_szLoginDefaultMessage) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			else if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				/*CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);*/
				SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strlen(sz_buffer) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_szLoginDefaultMessage);
			}
			break;
		}
	}
	break;
	case WM_CLOSE:		//������������ ������� �� �������.
		EndDialog(hwnd, 0);
	}
	return FALSE;
}