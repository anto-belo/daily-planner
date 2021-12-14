#include "editdlgproc.h"

void _WM_INITDIALOG_DLG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND hTimeFrom = GetDlgItem(hWnd, IDC_TIMEFROM);
	HWND hTimeTo = GetDlgItem(hWnd, IDC_TIMETO);

	DateTime_SetFormat(hTimeFrom, L"HH:mm");
	DateTime_SetFormat(hTimeTo, L"HH:mm");

	if (chosenTaskIndex != -1) {
		fillEditDlg(hWnd);
	}
	else {
		CheckRadioButton(hWnd, IDC_T_EVENT, IDC_T_NOTIFICATION, IDC_T_EVENT);
	}
}

void fillEditDlg(HWND hWnd) {
	HWND hDateFrom = GetDlgItem(hWnd, IDC_DATEFROM);
	HWND hTimeFrom = GetDlgItem(hWnd, IDC_TIMEFROM);
	HWND hDateTo = GetDlgItem(hWnd, IDC_DATETO);
	HWND hTimeTo = GetDlgItem(hWnd, IDC_TIMETO);

	PlannerEntry* chosenEntry = repo.get(chosenTaskIndex);

	SetDlgItemText(hWnd, IDC_EDIT_TITLE, chosenEntry->getTitle());
	LPSYSTEMTIME from = timestampToSysTime(chosenEntry->getDateFrom(), chosenEntry->getTimeFrom());
	DateTime_SetSystemtime(hDateFrom, GDT_VALID, from);
	DateTime_SetSystemtime(hTimeFrom, GDT_VALID, from);
	if (!wcscmp(chosenEntry->getType(), PE_EVENT_T)) {
		CheckRadioButton(hWnd, IDC_T_EVENT, IDC_T_NOTIFICATION, IDC_T_EVENT);
		LPSYSTEMTIME to = timestampToSysTime(chosenEntry->getDateTo(), chosenEntry->getTimeTo());
		DateTime_SetSystemtime(hDateTo, GDT_VALID, to);
		DateTime_SetSystemtime(hTimeTo, GDT_VALID, to);
	}
	else {
		CheckRadioButton(hWnd, IDC_T_EVENT, IDC_T_NOTIFICATION, IDC_T_NOTIFICATION);
		EnableWindow(hDateTo, FALSE);
		EnableWindow(hTimeTo, FALSE);
	}
}

void _WM_COMMAND_DLG(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HWND hDateFrom = GetDlgItem(hWnd, IDC_DATEFROM);
	HWND hTimeFrom = GetDlgItem(hWnd, IDC_TIMEFROM);
	HWND hDateTo = GetDlgItem(hWnd, IDC_DATETO);
	HWND hTimeTo = GetDlgItem(hWnd, IDC_TIMETO);
	HWND hTypeEvent = GetDlgItem(hWnd, IDC_T_EVENT);

	LPWSTR title;
	LPWSTR dateFrom;
	LPWSTR timeFrom;
	LPWSTR dateTo;
	LPWSTR timeTo;

	PlannerEntry* chosenEntry;

	SYSTEMTIME lpst = SYSTEMTIME{ 0 };

	switch (LOWORD(wParam)) {
	case IDC_T_EVENT:
		EnableWindow(hDateTo, TRUE);
		EnableWindow(hTimeTo, TRUE);
		break;
	case IDC_T_NOTIFICATION:
		EnableWindow(hDateTo, FALSE);
		EnableWindow(hTimeTo, FALSE);
		break;
	case IDOK:
		chosenEntry = chosenTaskIndex == -1
			? new PlannerEntry()
			: repo.get(chosenTaskIndex);

		title = new WCHAR[100];
		GetDlgItemText(hWnd, IDC_EDIT_TITLE, title, 100);
		if (wcscmp(title, L"") == 0) {
			MessageBox(hWnd, L"Task title cannot be empty!", L"Error!", MB_OK | MB_ICONERROR);
			break;
		}

		dateFrom = new WCHAR[11]{ 0 };
		dateFrom[10] = '\0';
		DateTime_GetSystemtime(hDateFrom, &lpst);
		SysTimeToDate(&lpst, dateFrom);

		timeFrom = new WCHAR[6]{ 0 };
		timeFrom[5] = '\0';
		DateTime_GetSystemtime(hTimeFrom, &lpst);
		SysTimeToTime(&lpst, timeFrom);

		if (Button_GetCheck(hTypeEvent) == BST_CHECKED) {
			dateTo = new WCHAR[11]{ 0 };
			dateTo[10] = '\0';
			DateTime_GetSystemtime(hDateTo, &lpst);
			SysTimeToDate(&lpst, dateTo);

			timeTo = new WCHAR[6];
			timeTo[5] = '\0';
			DateTime_GetSystemtime(hTimeTo, &lpst);
			SysTimeToTime(&lpst, timeTo);

			if (wcscmp(dateFrom, dateTo) >= 0 && wcscmp(timeFrom, timeTo) >= 0) {
				MessageBox(hWnd, L"Incorrect time interval!", L"Error!", MB_OK | MB_ICONERROR);
				break;
			}

			delete chosenEntry->getDateTo();
			delete chosenEntry->getTimeTo();

			chosenEntry->setDateTo(dateTo);
			chosenEntry->setTimeTo(timeTo);
			chosenEntry->setType(const_cast<LPWSTR>(PE_EVENT_T));
		}
		else {
			delete chosenEntry->getDateTo();
			delete chosenEntry->getTimeTo();

			chosenEntry->setDateTo(NULL);
			chosenEntry->setTimeTo(NULL);
			chosenEntry->setType(const_cast<LPWSTR>(PE_NOTIFICATION_T));
		}

		delete chosenEntry->getTitle();
		delete chosenEntry->getDateFrom();
		delete chosenEntry->getTimeFrom();

		chosenEntry->setTitle(title);
		chosenEntry->setDateFrom(dateFrom);
		chosenEntry->setTimeFrom(timeFrom);

		if (chosenTaskIndex == -1) {
			repo.push_front(chosenEntry);
			UpdateView(hLVTasks);
		}

		InvalidateRect(hLVTasks, 0, TRUE);
		changed = TRUE;
	case IDCANCEL:
		chosenTaskIndex = -1;
		EndDialog(hWnd, TRUE);
	}
}
