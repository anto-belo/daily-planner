#include "util.h"

LPWSTR s2ws(const string& s) {
	int sLength = (int)s.length() + 1;
	int bufLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, 0, 0);
	LPWSTR buf = new WCHAR[bufLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), sLength, buf, bufLength);
	return buf;
}

vector<string> split(string src, CHAR delimiter) {
	stringstream stream(src);
	string segment;
	vector<string> seglist;

	while (getline(stream, segment, delimiter)) {
		seglist.push_back(segment);
	}

	return seglist;
}

vector<wstring> wsplit(wstring src, WCHAR delimiter) {
	wstringstream stream(src);
	wstring segment;
	vector<wstring> seglist;

	while (getline(stream, segment, delimiter)) {
		seglist.push_back(segment);
	}

	return seglist;
}

LPSYSTEMTIME timestampToSysTime(LPWSTR date, LPWSTR time) {
	vector<wstring> dateComponents = wsplit(date, DATE_DELIM);
	vector<wstring> timeComponents = wsplit(time, TIME_DELIM);
	LPSYSTEMTIME st = new SYSTEMTIME();
	st->wYear = stoi(dateComponents.at(0));
	st->wMonth = stoi(dateComponents.at(1));
	st->wDay = stoi(dateComponents.at(2));
	st->wHour = stoi(timeComponents.at(0));
	st->wMinute = stoi(timeComponents.at(1));
	return st;
}

void SysTimeToDate(LPSYSTEMTIME lpst, LPWSTR date) {
	WCHAR year[5] = { 0 }, month[3] = { 0 }, day[3] = { 0 };
	_itow_s(lpst->wYear, year, 5, 10);
	_itow_s(lpst->wMonth, month, 3, 10);
	_itow_s(lpst->wDay, day, 3, 10);

	if (lpst->wMonth < 10) {
		month[1] = month[0];
		month[0] = '0';
		month[2] = '\0';
	}

	if (lpst->wDay < 10) {
		day[1] = day[0];
		day[0] = '0';
		day[2] = '\0';
	}

	swprintf_s(date, 11, L"%s-%s-%s", year, month, day);
}

void SysTimeToTime(LPSYSTEMTIME lpst, LPWSTR time) {
	WCHAR hour[3] = { 0 }, minute[3] = { 0 };
	_itow_s(lpst->wHour, hour, 3, 10);
	_itow_s(lpst->wMinute, minute, 3, 10);

	if (lpst->wHour < 10) {
		hour[1] = hour[0];
		hour[0] = '0';
		hour[2] = '\0';
	}

	if (lpst->wMinute < 10) {
		minute[1] = minute[0];
		minute[0] = '0';
		minute[2] = '\0';
	}

	swprintf_s(time, 6, L"%s:%s", hour, minute);
}

LPWSTR getSaveFilePath(HWND hWnd, LPWSTR defaultName) {
	/*OPENFILENAME ofn;
	WCHAR szPath[100];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szPath;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = L"Text files\0*.txt\0";
	ofn.nFilterIndex = 1;
	
	BOOL fOk = GetSaveFileName(&ofn);
	if (fOk) {
		return szPath;
	}
	return nullptr;*/
	WCHAR szPath[MAX_PATH] = {};

	OPENFILENAME ofn = { sizeof(ofn) };
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = L"Text Files\0*.txt\0";
	ofn.lpstrFile = szPath;
	ofn.nMaxFile = ARRAYSIZE(szPath);

	BOOL fOk = GetSaveFileName(&ofn);
	if (fOk)
	{
		// Open the file that was selected in
		// the Open File dialog
		return szPath;
	}
	return nullptr;
}

LPWSTR GetCurrentDate() {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d");
	return s2ws(oss.str());
}
