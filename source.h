#pragma once
#pragma comment(lib, "comctl32.lib")

#include <windows.h>
#include <commctrl.h>

#include "resource.h"

#include "mainwndproc.h"
#include "editdlgproc.h"
#include "PlannerRepository.h"

HINSTANCE hInst;

HWND hWndParent;
HWND hLVTasks;

PlannerRepository repo;
int chosenTaskIndex = -1;

BOOL changed = FALSE;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
