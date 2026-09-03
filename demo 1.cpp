#include <windows.h>
RECT rc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_WAIT);
	wc.lpszClassName = "koshka";
	wc.lpfnWndProc = WndProc;
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(0,"koshka","DEMO",NULL,CW_USEDEFAULT,CW_USEDEFAULT,680,480,NULL,NULL,hInstance,NULL);
	SetWindowPos(hwnd,NULL,680,480,0,0, SWP_NOZORDER | SWP_NOSIZE );
	HHOOK hook1 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
	HHOOK hook2 = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
	if (code >= 0) {
		return 1;
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam) {
	if (code >= 0) {
		return 1;
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}