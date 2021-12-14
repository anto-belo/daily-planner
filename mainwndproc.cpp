#include "mainwndproc.h"

void _WM_CREATE_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	hLVTasks = CreateView(hWnd);
	InitView(hLVTasks);

	CreateNewTaskButton(hWnd);
	CreateUpdateTaskButton(hWnd);
	CreateDeleteTaskButton(hWnd);
	CreateDeleteDoneTasksButton(hWnd);
	//CreateGetTodayTasksButton(hWnd);
}

void _WM_COMMAND_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	UpdateCheckStates(hLVTasks);
	switch (LOWORD(wParam)) {
	case IDM_FILE_SAVE:
		_file_save();
		break;
	case IDM_PROGRAM_ABOUT:
		_program_about(hWnd);
		break;
	case IDB_NEW_TASK:
		_new_task(hWnd);
		break;
	case IDB_UPD_TASK:
		_upd_task(hWnd);
		break;
	case IDB_DEL_TASK:
		_del_task(hWnd);
		break;
	case IDB_DEL_DONE:
		_del_done();
		break;
	case IDB_GET_TODAY:
		_get_today(hWnd);
		break;
	}
}

void _WM_HOTKEY_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	UpdateCheckStates(hLVTasks);
	switch (wParam) {
	case HK_CTRL_N:
		_new_task(hWnd);
		break;
	case HK_CTRL_S:
		_file_save();
		break;
	}
}

void _WM_NOTIFY_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HandleWM_NOTIFY(hLVTasks, lParam);
}

void _WM_CLOSE_MAIN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (changed == TRUE || isUnsavedChecks() == TRUE) {
		switch (MessageBox(hWnd, L"You have unsaved changes. Save before quit?",
			L"Warning!", MB_YESNOCANCEL | MB_ICONQUESTION)) {
		case IDYES:
			UpdateCheckStates(hLVTasks);
			_file_save();
		case IDNO:
			DestroyWindow(hWnd);
			break;
		}
	}
	else {
		DestroyWindow(hWnd);
	}
}

void _file_save() {
	repo.savePlanner();
	changed = FALSE;
}

void _program_about(HWND hWnd) {
	MessageBox(hWnd, L"Anton Belousov (c)2021\nDaily Planner v0.0.1", L"About", MB_OK | MB_ICONINFORMATION);
}

void _new_task(HWND hWnd) {
	DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT_TASK), hWnd, EditDlgProc);
}

void _upd_task(HWND hWnd) {
	int i = ListView_GetSelectionMark(hLVTasks);
	if (i == -1) {
		MessageBox(hWnd, L"You haven't selected any task!", L"Error!", MB_OK | MB_ICONERROR);
	}
	else {
		chosenTaskIndex = i;
		DialogBox(hInst, MAKEINTRESOURCE(IDD_EDIT_TASK), hWnd, EditDlgProc);
	}
}

void _del_task(HWND hWnd) {
	int i = ListView_GetSelectionMark(hLVTasks);
	if (i == -1) {
		MessageBox(hWnd, L"You haven't selected any task!", L"Error!", MB_OK | MB_ICONERROR);
	}
	else {
		repo.remove(i);
		UpdateView(hLVTasks);
		changed = TRUE;
	}
}

void _del_done() {
	if (repo.removeDone() == TRUE) {
		UpdateView(hLVTasks);
		changed = TRUE;
	}
}

void _get_today(HWND hWnd) {
	LPWSTR today = GetCurrentDate();
	wcscat_s(today, 100, L".txt");
	LPWSTR filePath = getSaveFilePath(hWnd, today);
	if (filePath != nullptr) {
		if (repo.saveToday(filePath, today) != TRUE) {
			MessageBox(hWnd, L"You don't have any tasks for today", L"Info", MB_OK | MB_ICONASTERISK);
		}
	}
}

BOOL isUnsavedChecks() {
	for (int i = 0; i < repo.size(); i++) {
		PlannerEntry* pe = repo.get(i);
		BOOL currentCheckState = ListView_GetCheckState(hLVTasks, i);
		if (pe->isDone() != currentCheckState) {
			return TRUE;
		}
	}
	return FALSE;
}
