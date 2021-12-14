#pragma once

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "resource.h"

#include "todoview.h"
#include "PlannerRepository.h"
#include "PlannerEntry.h"

extern HWND hLVTasks;

extern PlannerRepository repo;
extern int chosenTaskIndex;

extern BOOL changed;

void _WM_INITDIALOG_DLG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_COMMAND_DLG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void fillEditDlg(HWND hWnd);
