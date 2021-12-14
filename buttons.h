#pragma once

#include <windows.h>

#define IDB_NEW_TASK 3
#define IDB_UPD_TASK 4
#define IDB_DEL_TASK 5
#define IDB_DEL_DONE 6
#define IDB_GET_TODAY 7

extern HINSTANCE hInst;

HWND CreateNewTaskButton(HWND hWndParent);

HWND CreateUpdateTaskButton(HWND hWndParent);

HWND CreateDeleteTaskButton(HWND hWndParent);

HWND CreateDeleteDoneTasksButton(HWND hWndParent);

HWND CreateGetTodayTasksButton(HWND hWndParent);
