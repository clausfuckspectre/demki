#include <windows.h>

RECT rc;

int x = 800;
int y = 600;

int sWidth = 0;
int sHeight = 0;

int xPos = 0;
int yPos = 0;

HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int sWidth = GetSystemMetrics(SM_CXSCREEN);
	int sHeight = GetSystemMetrics(SM_CYSCREEN);

	int xPos = (sWidth - x) / 2;
	int yPos = (sHeight - y) / 2;

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_WAIT);
	wc.lpszClassName = "koshka";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = hbrush;
	RegisterClassEx(&wc);

	HWND hwnd = CreateWindowEx(0, "koshka", "DEMO", WS_POPUP, xPos, yPos, x, y, NULL, NULL, hInstance, NULL);

	HHOOK hook1 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
	HHOOK hook2 = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	UnhookWindowsHookEx(hook1);
	UnhookWindowsHookEx(hook2);

	DeleteObject(hbrush);

	return (int)msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		SetTextColor(hdc, RGB(128, 0, 128));
		DrawText(hdc, "Create by @cIau5", -1, &rc, DT_RIGHT | DT_BOTTOM | DT_SINGLELINE);

		SetTextColor(hdc, RGB(128, 0, 128));
		DrawText(hdc, "GitHub:ClausFuckSpectre", -1, &rc, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

		rc.left -= 60;

		FrameRect(hdc, &rc, hbrush);

		SetTextColor(hdc, RGB(255, 0, 0));
		DrawText(hdc, "Fuck", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rc.right += 60;

		SetTextColor(hdc, RGB(0, 0, 0));
		DrawText(hdc, "the", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		rc.right += 80;

		SetTextColor(hdc, RGB(0, 255, 255));
		DrawText(hdc, "tolerant", -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		EndPaint(hwnd, &ps);
		break;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);

}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code >= 0)

		return 1;

	return CallNextHookEx(NULL, code, wParam, lParam);

}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code >= 0)

		return 1;

	return CallNextHookEx(NULL, code, wParam, lParam);
}