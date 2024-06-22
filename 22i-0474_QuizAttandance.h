#pragma once
#include "22i-0474_AssessmentItems.h"

class AssessmentItems;

class AssessmentAttandance {
	int assessmentId;
	string** attandance;
	int attandanceCount;
	int maxCount;
public:
	AssessmentAttandance() {
		assessmentId = 0;
		attandance = new string*[30];
		for (int i = 0; i < 30; i++) {
			attandance[i] = new string[2];
		}
		attandanceCount = 0;
		maxCount = 30;
	}

	AssessmentAttandance(int size, int id) {
		assessmentId = id;
		attandance = new string * [size];
		for (int i = 0; i < size; i++) {
			attandance[i] = new string[2];
		}
		attandanceCount = 0;
		maxCount = size;
	}

	void addAttandance(string StudentName, string topic, string type) {
		attandance[attandanceCount][0] = StudentName;
		attandance[attandanceCount][1] = "P";
		attandanceCount++;
		ofstream file;
		file.open("attandance.txt", ios::out|ios::app);
		file << StudentName << ',' << topic << ',' << type << ',' << 'P' << endl;
		file.close();
	}

	bool hasAttanded(string StudentName) {
		for (int i = 0; i < attandanceCount; i++) {
			if (attandance[i][0] == StudentName) {
				return true;
			}
		}
		return false;
	}

	void print() {
		for (int i = 0; i < attandanceCount; i++) {
			cout << "Course Attandance\n";
			cout << attandance[i][0] << "\t" << attandance[i][1] << endl;
		}
	}
};
