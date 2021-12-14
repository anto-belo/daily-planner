#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "PlannerEntry.h"

#define DATA_FILE_PATH "D:\\OSaSP labs\\daily-planner\\x64\\Debug\\data.txt"

using namespace std;

class PlannerRepository {
	vector<PlannerEntry*> entries;
public:
	PlannerRepository();

	int size();
	void push_front(PlannerEntry* entry);
	PlannerEntry* get(int index);
	void remove(int i);
	BOOL removeDone();

	void savePlanner();
	BOOL saveToday(LPWSTR filePath, LPWSTR date);
};
