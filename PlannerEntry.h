#pragma once

#include <windows.h>
#include <string>
#include <vector>

#include "util.h"

#define PE_NOTIFICATION_S 5
#define PE_EVENT_S 7

#define PE_NOTIFICATION_T L"N"
#define PE_EVENT_T L"E"
#define PE_UNDEFINED_T L"U"

#define PE_DELIMITER '|'

using namespace std;

class PlannerEntry {
	BOOL done;
	LPWSTR type;
	LPWSTR dateFrom;
	LPWSTR timeFrom;
	LPWSTR dateTo;
	LPWSTR timeTo;
	LPWSTR title;
public:
	PlannerEntry();
	PlannerEntry(BOOL done, LPCWSTR type, LPWSTR dateFrom, LPWSTR timeFrom, LPWSTR dateTo, LPWSTR timeTo, LPWSTR title);
	PlannerEntry(string dataEntryString);
	~PlannerEntry();

	wstring toString();

	BOOL isDone();
	LPWSTR getType();
	LPWSTR getDateFrom();
	LPWSTR getTimeFrom();
	LPWSTR getDateTo();
	LPWSTR getTimeTo();
	LPWSTR getTitle();

	void setDone(BOOL done);
	void setType(LPWSTR type);
	void setDateFrom(LPWSTR dateFrom);
	void setTimeFrom(LPWSTR timeFrom);
	void setDateTo(LPWSTR dateTo);
	void setTimeTo(LPWSTR timeTo);
	void setTitle(LPWSTR title);
};
