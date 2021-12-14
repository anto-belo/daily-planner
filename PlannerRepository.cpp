#include "PlannerRepository.h"

PlannerRepository::PlannerRepository() {
	string fileLine;
	ifstream in(DATA_FILE_PATH);
	if (in.is_open()) {
		while (getline(in, fileLine)) {
			entries.push_back(new PlannerEntry(fileLine));
		}
		in.close();
	}
}

int PlannerRepository::size() {
	return entries.size();
}

void PlannerRepository::push_front(PlannerEntry* entry) {
	entries.insert(entries.begin(), entry);
}

PlannerEntry* PlannerRepository::get(int index) {
	if (index < 0 || index >= entries.size()) {
		return nullptr;
	}
	return entries.at(index);
}

void PlannerRepository::remove(int i) {
	PlannerEntry* pe = entries.at(i);
	entries.erase(entries.begin() + i);
	delete pe;
}

BOOL PlannerRepository::removeDone() {
	PlannerEntry* pe;
	BOOL anyDone = FALSE;
	for (int i = 0; i < entries.size(); i++) {
		pe = entries.at(i);
		if (pe->isDone()) {
			anyDone = TRUE;
			remove(i);
		}
	}
	return anyDone;
}

void PlannerRepository::savePlanner() {
	wofstream out;
	out.open(DATA_FILE_PATH);
	if (out.is_open()) {
		for (PlannerEntry* pe : entries) {
			out << pe->toString() << endl;
		}
		out.close();
	}
}

BOOL PlannerRepository::saveToday(LPWSTR filePath, LPWSTR date) {
	wofstream out;
	BOOL isAnyTasks = FALSE;
	for (PlannerEntry* pe : entries) {
		if ((wcscmp(pe->getType(), PE_EVENT_T) == 0
			&& wcscmp(pe->getDateFrom(), date) <= 0
			&& wcscmp(pe->getDateTo(), date) >= 0)
			|| (wcscmp(pe->getType(), PE_NOTIFICATION_T) == 0
				&& wcscmp(pe->getDateFrom(), date) == 0)) {
			if (!out.is_open()) {
				out.open(filePath);
			}
			isAnyTasks = TRUE;
			out << pe->toString() << endl;
		}
	}
	if (out.is_open()) {
		out.close();
	}

	return isAnyTasks;
}
