#pragma once

#include <windows.h>
#include <commctrl.h>

#include "resource.h"

#include "PlannerRepository.h"

#define LV_COLUMN_C 6

extern BOOL changed;

HWND CreateView(HWND hWndParent);

BOOL InitView(HWND hLV);

BOOL InitViewColumns(HWND hLV);

BOOL InitViewItems(HWND hLV, int cItems);

void HandleWM_NOTIFY(HWND hLV, LPARAM lParam);

void UpdateView(HWND hLV);

void UpdateCheckStates(HWND hLV);
