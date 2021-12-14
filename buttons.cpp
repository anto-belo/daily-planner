#include "buttons.h"

HWND CreateNewTaskButton(HWND hWndParent) {
	return CreateWindow(
		L"BUTTON",
		L"New task...",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		710, 10, 260, 30,
		hWndParent,
		(HMENU)IDB_NEW_TASK,
		hInst,
		NULL
	);
}

HWND CreateUpdateTaskButton(HWND hWndParent) {
	return CreateWindow(
		L"BUTTON",
		L"Update task...",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		710, 45, 260, 30,
		hWndParent,
		(HMENU)IDB_UPD_TASK,
		hInst,
		NULL
	);
}

HWND CreateDeleteTaskButton(HWND hWndParent) {
	return CreateWindow(
		L"BUTTON",
		L"Delete task",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		710, 80, 260, 30,
		hWndParent,
		(HMENU)IDB_DEL_TASK,
		hInst,
		NULL
	);
}

HWND CreateDeleteDoneTasksButton(HWND hWndParent) {
	return CreateWindow(
		L"BUTTON",
		L"Delete done tasks",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		710, 115, 260, 30,
		hWndParent,
		(HMENU)IDB_DEL_DONE,
		hInst,
		NULL
	);
}

HWND CreateGetTodayTasksButton(HWND hWndParent) {
	return CreateWindow(
		L"BUTTON",
		L"Get today tasks...",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		710, 150, 260, 30,
		hWndParent,
		(HMENU)IDB_GET_TODAY,
		hInst,
		NULL
	);
}
