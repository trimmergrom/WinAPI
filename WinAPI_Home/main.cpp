//#ifndef UNICODE
//#define UNICODE
//#endif 
#include<Windows.h>
#include"resource.h"

CONST CHAR g_szLoginDefoultMessage[] = "Enter Login";
CONST CHAR g_szPasswordDefoultMessage[] = "Enter Password";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	/*MessageBox(NULL, "Hello World!", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP | MB_DEFBUTTON3|	MB_SYSTEMMODAL);*/
	/*MessageBox(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), "Hello World!", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP | MB_DEFBUTTON3 | MB_APPLMODAL);*/
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:// Elements Interfase
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		/*HWND hLogin = GetDlgItem(hwnd, IDC_EDIT1_Login);
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT2_Password);*/
		SendMessage(GetDlgItem(hwnd, IDC_EDIT1_Login), WM_SETTEXT, 0, (LPARAM)g_szLoginDefoultMessage);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT2_Password), WM_SETTEXT, 0, (LPARAM)g_szPasswordDefoultMessage);
	}
		break;
	case WM_COMMAND:   //push buttons
		switch (LOWORD(wParam))
		{
		case IDOK: MessageBox(hwnd, "Push OK", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
			break;
			/////////////////////////////////////
		case IDC_BUTTON_Copy:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT1_Login);
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT2_Password);
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
			/////////////////////////////////////
		case IDC_EDIT1_Login:
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hLogin = GetDlgItem(hwnd, IDC_EDIT1_Login);				
				SendMessage(hLogin, WM_SETTEXT, SIZE, (LPARAM)sz_buffer);
				if(strcmp(sz_buffer, g_szLoginDefoultMessage)==0)
				SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			else if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				HWND hLogin = GetDlgItem(hwnd, IDC_EDIT1_Login);
				SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strlen(sz_buffer) == 0)SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)g_szLoginDefoultMessage);

			}
			break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0); // push "X"
	}
	return FALSE;
}

