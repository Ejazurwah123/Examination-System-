#pragma once
#include "22i-0474_AssessmentItems.h"
using namespace std;

class Result {
	AssessmentItems* assessment;
	double marks;
	string student;
public:
	Result() {
		assessment = NULL;
		marks = 0;
		student = "";
	}

	void addResult(string Student, double marks, AssessmentItems* assessment) {
		this->student = Student;
		this->marks = marks;
		this->assessment = assessment;
		ofstream file;
		file.open("./results.txt", ios::out|ios::app);
		if (file.is_open()) {
			file << Student << ',' << assessment->getTopic()->getName() << ',' << marks << endl;
			file.close();
		}
	}

	AssessmentItems* getAssessment() { return assessment; }
	double getMarks() { return marks; }
	string getStudent() { return student; }
};
