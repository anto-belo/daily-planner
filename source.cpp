#include "source.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	
	hInst = hInstance;

	const wchar_t CLASS_NAME[] = L"daily-planner-main";

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = (WNDPROC)WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_DATE_CLASSES;
	InitCommonControlsEx(&icex);


	hWndParent = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Daily Planner",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		1000, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);	

	if (!hWndParent) {
		return -1;
	}
	
	RegisterHotKey(hWndParent, HK_CTRL_N, MOD_CONTROL | MOD_NOREPEAT, 0x4E);
	RegisterHotKey(hWndParent, HK_CTRL_S, MOD_CONTROL | MOD_NOREPEAT, 0x53);

	ShowWindow(hWndParent, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		_WM_CREATE_MAIN(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_COMMAND:
		_WM_COMMAND_MAIN(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_HOTKEY:
		_WM_HOTKEY_MAIN(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_NOTIFY:
		_WM_NOTIFY_MAIN(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_CLOSE:
		_WM_CLOSE_MAIN(hWnd, uMsg, wParam, lParam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK EditDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG:
		_WM_INITDIALOG_DLG(hWnd, uMsg, wParam, lParam);
		return TRUE;
	case WM_COMMAND:
		_WM_COMMAND_DLG(hWnd, uMsg, wParam, lParam);
		return TRUE;
	}
	return FALSE;
}
