#include "PlannerEntry.h"

PlannerEntry::PlannerEntry() {
	this->done = FALSE;
	this->type = nullptr;
	this->dateFrom = nullptr;
	this->timeFrom = nullptr;
	this->dateTo = nullptr;
	this->timeTo = nullptr;
	this->title = nullptr;
}

PlannerEntry::PlannerEntry(BOOL done, LPCWSTR type, LPWSTR dateFrom, LPWSTR timeFrom, LPWSTR dateTo, LPWSTR timeTo, LPWSTR title) {
	this->done = done;
	this->type = const_cast<LPWSTR>(type);
	this->dateFrom = dateFrom;
	this->timeFrom = timeFrom;
	this->dateTo = dateTo;
	this->timeTo = timeTo;
	this->title = title;
}

PlannerEntry::PlannerEntry(string dataEntryString) {
	vector<string> seglist = split(dataEntryString, PE_DELIMITER);

	if (seglist.size() != PE_EVENT_S && seglist.size() != PE_NOTIFICATION_S) {
		done = FALSE;
		type = const_cast<LPWSTR>(PE_UNDEFINED_T);
		dateFrom = NULL;
		timeFrom = NULL;
		dateTo = NULL;
		timeTo = NULL;
		title = NULL;
	}
	else {
		done = stoi(seglist.at(0));
		type = s2ws(seglist.at(1));
		dateFrom = s2ws(seglist.at(2));
		timeFrom = s2ws(seglist.at(3));
		BOOL isEvent = !wcscmp(type, PE_EVENT_T);
		dateTo = isEvent ? s2ws(seglist.at(4)) : NULL;
		timeTo = isEvent ? s2ws(seglist.at(5)) : NULL;
		title = isEvent ? s2ws(seglist.at(6)) : s2ws(seglist.at(4));
	}
}

PlannerEntry::~PlannerEntry() {
	delete type;
	delete dateFrom;
	delete timeFrom;
	delete dateTo;
	delete timeTo;
	delete title;
}

wstring PlannerEntry::toString() {
	LPWSTR doneBuf = new WCHAR[2];
	_itow_s(done, doneBuf, 2, 10);

	LPWSTR result = new WCHAR[200];
	if (wcscmp(this->type, PE_EVENT_T) == 0) {
		swprintf_s(result, 200, L"%s|%s|%s|%s|%s|%s|%s", doneBuf, type, dateFrom, timeFrom, dateTo, timeTo, title);
	}
	else {
		swprintf_s(result, 200, L"%s|%s|%s|%s|%s", doneBuf, type, dateFrom, timeFrom, title);
	}
	
	delete[] doneBuf;
	return wstring(result);
}

BOOL PlannerEntry::isDone() {
	return done;
}

LPWSTR PlannerEntry::getType() {
	return type;
}

LPWSTR PlannerEntry::getDateFrom() {
	return dateFrom;
}

LPWSTR PlannerEntry::getTimeFrom() {
	return timeFrom;
}

LPWSTR PlannerEntry::getDateTo() {
	return dateTo;
}

LPWSTR PlannerEntry::getTimeTo() {
	return timeTo;
}

LPWSTR PlannerEntry::getTitle() {
	return title;
}

void PlannerEntry::setDone(BOOL done) {
	this->done = done;
}

void PlannerEntry::setType(LPWSTR type) {
	this->type = type;
}

void PlannerEntry::setDateFrom(LPWSTR dateFrom) {
	this->dateFrom = dateFrom;
}

void PlannerEntry::setTimeFrom(LPWSTR timeFrom) {
	this->timeFrom = timeFrom;
}

void PlannerEntry::setDateTo(LPWSTR dateTo) {
	this->dateTo = dateTo;
}

void PlannerEntry::setTimeTo(LPWSTR timeTo) {
	this->timeTo = timeTo;
}

void PlannerEntry::setTitle(LPWSTR title) {
	this->title = title;
}
