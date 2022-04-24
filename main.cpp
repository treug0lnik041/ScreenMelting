#include <cstdint>
#include <Windows.h>

uint64_t width, height;
int interval = 100;

LRESULT CALLBACK wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		HDC desktop = GetDC(HWND_DESKTOP);
		HDC window = GetDC(hWnd);

		BitBlt(window, 0, 0, width, height, desktop, 0, 0, SRCCOPY);

		ReleaseDC(hWnd, window);
		ReleaseDC(HWND_DESKTOP, desktop);

		SetTimer(hWnd, 0, interval, 0);

		ShowWindow(hWnd, SW_SHOW);
	}
	break;
	case WM_PAINT:
	{
		ValidateRect(hWnd, 0);
	}
	break;
	case WM_TIMER:
	{
		HDC wndw = GetDC(hWnd);

		int x = (rand() % width) - 100;
		int y = (rand() % 15);

		int _width = rand() % 200;

		BitBlt(wndw, x, y, _width, height, wndw, x, 0, SRCCOPY);

		ReleaseDC(hWnd, wndw);
	}
	break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);

		PostQuitMessage(0);
	}
	break;

	return 0;
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	width = GetSystemMetrics(SM_CXSCREEN);
	height = GetSystemMetrics(SM_CYSCREEN);

	WNDCLASS wndClass = {0, wndproc, 0, 0, hInstance, 0, LoadCursorW(0, IDC_ARROW), 0, 0, L"ScreenMelting"};

	if (RegisterClass(&wndClass))
	{
		HWND hWnd = CreateWindowExW(WS_EX_TOPMOST, L"ScreenMelting", 0, WS_POPUP, 0, 0, width, height, HWND_DESKTOP, 0, hInstance, 0);

		if (hWnd)
		{
			srand(GetTickCount64());

			MSG msg = { 0 };
			while (msg.message != WM_QUIT)
			{
				if (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessageW(&msg);
				}
			}
		}
	}
}