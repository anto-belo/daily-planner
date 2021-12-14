#include "todoview.h"

extern HINSTANCE hInst;
extern PlannerRepository repo;

HWND CreateView(HWND hWndParent) {
	HWND hLV = CreateWindow(
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS | LVS_NOSORTHEADER,
		10, 10,
		680, 420,
		hWndParent,
		NULL,
		hInst,
		NULL
	);
	ListView_SetExtendedListViewStyle(hLV, LVS_EX_FULLROWSELECT
		| LVS_EX_HEADERDRAGDROP
		| LVS_EX_LABELTIP
		| LVS_EX_CHECKBOXES
		| LVS_EX_GRIDLINES);
	return hLV;
}

BOOL InitView(HWND hLV) {
	InitViewColumns(hLV);
	InitViewItems(hLV, repo.size());
	return TRUE;
}

BOOL InitViewColumns(HWND hLV) {
	WCHAR szText[256];
	LVCOLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_MINWIDTH | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT | LVCFMT_FIXED_WIDTH;

	int* cxs = new int[6]{ 40, 70, 70, 70, 70, 360 };
	int* cxsmin = new int[6]{ 40, 70, 70, 70, 70, 70 };
	for (int iCol = 0; iCol < LV_COLUMN_C; iCol++) {
		lvc.pszText = szText;
		lvc.iSubItem = iCol;
		lvc.cx = cxs[iCol];
		lvc.cxMin = cxsmin[iCol];

		LoadString(hInst,
			IDS_LVC_FIRST + iCol,
			szText,
			sizeof(szText) / sizeof(szText[0]));

		ListView_InsertColumn(hLV, iCol, &lvc);
	}

	delete[] cxs;
	delete[] cxsmin;
	return TRUE;
}

BOOL InitViewItems(HWND hLV, int cItems) {
	LVITEM lvi;

	lvi.mask = LVIF_TEXT | LVIF_STATE;
	lvi.iSubItem = 0;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.pszText = LPSTR_TEXTCALLBACK;

	for (int index = 0; index < cItems; index++) {
		lvi.iItem = index;
		ListView_InsertItem(hLV, &lvi);
		ListView_SetCheckState(hLV, index, repo.get(index)->isDone());
	}

	return TRUE;
}

void HandleWM_NOTIFY(HWND hLV, LPARAM lParam) {
	NMLVDISPINFO* plvdi;
	PlannerEntry* dispEntry;

	switch (((LPNMHDR)lParam)->code) {
	case LVN_GETDISPINFO:
		plvdi = (NMLVDISPINFO*)lParam;
		dispEntry = repo.get(plvdi->item.iItem);
		switch (plvdi->item.iSubItem) {
		case 0:
			plvdi->item.pszText = dispEntry->getType();
			break;
		case 1:
			plvdi->item.pszText = dispEntry->getDateFrom();
			break;
		case 2:
			plvdi->item.pszText = dispEntry->getTimeFrom();
			break;
		case 3:
			plvdi->item.pszText = dispEntry->getDateTo();
			break;
		case 4:
			plvdi->item.pszText = dispEntry->getTimeTo();
			break;
		case 5:
			plvdi->item.pszText = dispEntry->getTitle();
			break;
		}
		break;
	}
}

void UpdateView(HWND hLV) {
	ListView_DeleteAllItems(hLV);
	InitViewItems(hLV, repo.size());
}

void UpdateCheckStates(HWND hLV) {
	for (int i = 0; i < repo.size(); i++) {
		PlannerEntry* pe = repo.get(i);
		BOOL currentCheckState = ListView_GetCheckState(hLV, i);
		if (pe->isDone() != currentCheckState) {
			changed = TRUE;
			pe->setDone(currentCheckState);
		}
	}
}
