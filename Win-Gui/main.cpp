#include <Windows.h>
#include <cassert>
#include <iostream>

#define IDC_SECRET_BUTTON 100

HWND hEdit;
char buffer[1024];

LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			if(LOWORD(wParam) == IDC_SECRET_BUTTON)
			{
				std::cout << "you suck dick, nachts..." << std::endl;
				GetWindowText(hEdit, buffer, 1024);
				std::cout << buffer << " heh thats sad...xD" << std::endl;
			}
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main()
{
	HINSTANCE hInst = GetModuleHandle(0);
	HWND hWnd;
	HWND hButton;
	WNDCLASS wc;
	MSG msg;

	wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageHandler;
	wc.hInstance = hInst;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "WinApiTest";

	assert(RegisterClass(&wc));

	hWnd = CreateWindow("WinApiTest", "WinApi 32", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInst, 0);
	hButton = CreateWindow("button", "Secret Button", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 70, 200, 50, hWnd, (HMENU)IDC_SECRET_BUTTON, hInst, 0);
	hEdit = CreateWindow("edit", "Please enter dick size here", WS_TABSTOP |WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 200, 50, hWnd, 0, 0, 0);

	ShowWindow(hWnd, 5);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);

	std::cout << "Hello, window created!" << std::endl;

	bool running = true;
	while (running)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				running = false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


	}

	return 0;
}