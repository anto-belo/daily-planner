#pragma once

#include <windows.h>
#include <commctrl.h>

#include "resource.h"

#include "buttons.h"
#include "todoview.h"
#include "PlannerRepository.h"

#define HK_CTRL_N 1
#define HK_CTRL_S 2

extern HINSTANCE hInst;

extern HWND hLVTasks;

extern PlannerRepository repo;
extern int chosenTaskIndex;

extern BOOL changed;

INT_PTR CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_CREATE_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_COMMAND_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_HOTKEY_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_NOTIFY_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _WM_CLOSE_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void _file_save();

void _program_about(HWND hWnd);

void _new_task(HWND hWnd);

void _upd_task(HWND hWnd);

void _del_task(HWND hWnd);

void _del_done();

void _get_today(HWND hWnd);

BOOL isUnsavedChecks();
