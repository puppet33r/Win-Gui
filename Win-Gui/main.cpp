#include <Windows.h>
#include<cassert>

LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
	HWND hWnd;
	WNDCLASS wc;
	MSG msg;

	wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MessageHandler;
	wc.hInstance = hInst;
	wc.lpszClassName = "WinApiTest";

	assert(RegisterClass(&wc));

	hWnd = CreateWindow("WinApiTest", "WinApi 32", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInst, 0);

	ShowWindow(hWnd, nCmdShow);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	UpdateWindow(hWnd);

	while (true)
	{
		BOOL result = GetMessage(&msg, 0, 0, 0);
		if (result > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else
		{
			return result;
		}
	}

	return 0;
}