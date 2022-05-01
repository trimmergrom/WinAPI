#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource.h"

#define IDC_STATIC 1000 //resourse for static text

CONST CHAR g_szClassName[] = "MyWindowClass";
CONST CHAR g_szWindowTitle[] = "My First Window";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR LpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; //wc - Window class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.style = 0;
	//wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wc.hIcon = (HICON)LoadImage(hInstance, "char_1.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "char_2.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	
	wc.hCursor = LoadCursor(hInstance, (LPCSTR)IDC_CURSOR1);
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = NULL;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed!", "Error", MB_OK | MB_ICONERROR);
		return NULL;
	}

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_heigth = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * .75;
	int window_heigth = screen_heigth * .75;
	int start_x = screen_width * .125;
	int start_y = screen_heigth * .125;


	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyle
		g_szClassName,
		g_szWindowTitle,
		WS_OVERLAPPEDWINDOW,
		start_x, start_y,
		window_width, window_heigth,		
		NULL,//Parent Window
		NULL,//ID resource Menu, if window is OVERLAPPED or window dote
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed!", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);//drow window

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//CreatWindowExA - ANSI cod
		//CreatWindowExW - Wide (Unicod)

		HWND hStatic = CreateWindowEx
		(
			0,
			"Static",
			"This static string will view size of window and psition window",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			500, 50,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL), //return hInstance
			0
		);
	}
		break;
	case WM_COMMAND:break;
	case WM_SIZE:
	case WM_MOVE:
	{
		CONST INT SIZE = 256;
		CHAR sz_msg[SIZE] = {};
		RECT rect; //rectangl of window
		GetWindowRect(hwnd, &rect);
		int window_width = rect.right - rect.left;
		int window_heigth = rect.bottom - rect.top;
		sprintf(sz_msg, "%s - Size: %i x%i, Position: %i x%i", g_szWindowTitle, window_width, window_heigth, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_msg);
		SendMessage(GetDlgItem(hwnd, IDC_STATIC), WM_SETTEXT, 0, (LPARAM)sz_msg);


	}
		break;
	case WM_CLOSE:
		if(MessageBox(hwnd, "You are realy close?", "Question", MB_YESNO | MB_ICONQUESTION)==IDYES)
			DestroyWindow(hwnd);
			break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}