#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#define TIME_DELIM L':'
#define DATE_DELIM L'-'

using namespace std;

LPWSTR s2ws(const string& s);

vector<string> split(string src, CHAR delimiter);

vector<wstring> wsplit(wstring src, WCHAR delimiter);

LPSYSTEMTIME timestampToSysTime(LPWSTR date, LPWSTR time);

void SysTimeToDate(LPSYSTEMTIME lpst, LPWSTR date);

void SysTimeToTime(LPSYSTEMTIME lpst, LPWSTR time);

LPWSTR getSaveFilePath(HWND hWnd, LPWSTR defaultName);

LPWSTR GetCurrentDate();
