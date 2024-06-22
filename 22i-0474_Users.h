#pragma once
#include <iostream>
#include <string>
#include "22i-0474_Authentication.h"
#include "22i-0474_Registration.h"
#include "22i-0474_Course.h"

using namespace std;

class ExaminationSys;
class Course;
class Teacher;

class User {
	string name;
	string address;
	string email;
	string dob;
	string username;
public:
	User() {
		name = "";
		address = "";
		email = "";
		dob = "";
		username = "";
	}
	User(string name, string address, string email, string dob, string username) {
		this->name = name;
		this->address = address;
		this->email = email;
		this->dob = dob;
		this->username = username;
	}

	const string& getName() const { return name; }
	const string& getAddress() const { return address; }
	const string& getEmail() const { return email; }
	const string& getDOB() const { return dob; }
	const string& getUsername() const { return username; }
};

class Student : public User {
	Course** courses;
	int* courseCount;
	int* courseMax;
	Student** students;
	int* studentCount;
	int* studentMax;
public:
	Student(string name, string address, string email, string dob, string username, Course** courses, int* courseCount, int* courseMax, Student** students, int* studentCount, int* studentMax) : User(name, address, email, dob, username) {
		this->courses = courses;
		this->courseCount = courseCount;
		this->courseMax = courseMax;
		this->students = students;
		this->studentCount = studentCount;
		this->studentMax = studentMax;
	}

	void viewCourseRegistered() {
		system("cls");
		cout << "------------------ COURSES -------------------\n";
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				if (courses[i]->getStudentsCount() > 0) {
					for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
						if (courses[i]->getStudents()[j]->getUsername() == this->getUsername()) {
							cout << count + 1 << ". " << courses[i]->getCourseName() << endl;
							count++;
						}
					}
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void courseRegistration() {
		system("cls");
		cout << "------------------ COURSES REGISTRATION -------------------\n";
		string temp = "";
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
					if (courses[i]->getStudents()[j]->getUsername() == this->getUsername()) {
					
					}
					else if ((courses[i]->getStudentsCount() < courses[i]->getMaxStudent())) {
						if (temp != courses[i]->getCourseName()) {
							temp = courses[i]->getCourseName();
							cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
						}
					}
				}
			}
			int id;
			do {
				cout << "Enter Course Id: ";
				cin >> id;
			} while (id < 0 || id > *courseCount);

			courses[id - 1]->registerStudent(this);
			updateRegistations();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void updateRegistations() {
		ofstream file;
		file.open("courseRegistration.csv");
		if (!file.is_open()) {
			cout << "UNABLE TO UPADATE REGISTRATIONS\n";
			return;
		}
		for (int i = 0; i < *courseCount; i++) {
			if (i != 0) { file << ','; }
			file << courses[i]->getCourseName();
		}
		file << endl << "S#,Roll No.,Student Name,";
		for (int i = 0; i < *courseCount; i++) {
			if (i != 0) { file << ','; }
			file << courses[i]->getCourseCode();
		}
		file << endl;
		bool flag = true;
		for (int k = 0; k < *studentCount; k++) {
			file << k + 1 << ',' << students[k]->getUsername() << ',' << students[k]->getName() << ',';
			for (int i = 0; i < *courseCount; i++) {
				flag = true;
				for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
					if (courses[i]->getStudents()[j]->getUsername() == students[k]->getUsername()) {
						file << '1';
						if (i != *courseCount - 1) { file << ','; }
						flag = false;
					}
				}
				if (flag) {
					flag = false;
					file << '0';
					if(i != *courseCount-1){ file << ','; }
				}
			}
			file << endl;
		}
		file << "Total no of Students";
		for (int i = 0; i < *courseCount; i++) {
			file << ',';
			file << courses[i]->getStudentsCount();
		}
	}
	
	void viewTopics() {
		system("cls");
		cout << "------------- TOPICS -------------\n";
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				if (courses[i]->getStudentsCount() > 0) {
					for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
						if (courses[i]->getStudents()[j]->getUsername() == this->getUsername()) {
							cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
							courses[i]->viewTopics();
							cout << endl;
						}
					}
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void attemptAssessment() {
		system("cls");
		cout << "------------------ ASSESSMENTS -------------------\n";
		bool p = false;
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				if (courses[i]->getStudentsCount() > 0) {
					for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
						if (courses[i]->getStudents()[j]->getUsername() == this->getUsername()) {
							cout << "Course ID: "<< i+1 << "  " << courses[i]->getCourseName() << endl;
							courses[i]->viewAssessments() || p ? p = true: p;
							cout << endl;
						}
					}
				}
			}
			if (p) {
				int id, assessment_id;
				do {
					cout << "Enter Course Id: ";
					cin >> id;
				} while (id < 1 || id > *courseCount);
				courses[id - 1]->attemptAssessment(this->getUsername());
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewResult() {
		system("cls");
		cout << "------------- RESULTS -------------\n";
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				if (courses[i]->getStudentsCount() > 0) {
					for (int j = 0; j < courses[i]->getStudentsCount(); j++) {
						if (courses[i]->getStudents()[j]->getUsername() == this->getUsername()) {
							cout << "Course " << i + 1 << ": " << courses[i]->getCourseName() << endl;
							courses[i]->viewResults(this->getUsername());
							cout << endl;
						}
					}
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void dashboard() {
		int option;
		bool flag = true;
		while (flag) {
			do {
				system("cls");
				cout << "------------------- DASHBOARD ---------------------\n";
				cout << "1. View Courses Registered\n2. Course Registration\n3. Attempt Assessments\n4. View Result\n5. View Topics\n6. EXIT\n";
				cin >> option;
			} while (option < 1 || option>11);
			switch (option) {
			case 1:
				viewCourseRegistered();
				break;
			case 2:
				courseRegistration();
				break;
			case 3:
				attemptAssessment();
				break;
			case 4:
				viewResult();
				break;
			case 5:
				viewTopics();
				break;
			case 6:
				flag = false;
				break;
			}
		}
		return;
	}
};

class Teacher : public User {
	Course** courses;
	int* courseCount;
	int* courseMax;
public:
	Teacher(string name, string address, string email, string dob, string username, Course** courses, int* courseCount, int* courseMax) : User(name, address, email, dob, username) {
		this->courses = courses;
		this->courseCount = courseCount;
		this->courseMax = courseMax;
	}

	void viewCourses() {
		system("cls");
		cout << "------------------ COURSES -------------------\n";
		if (*courseCount >= 1) {
			for (int i = 0, count = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << count + 1 << ". " << courses[i]->getCourseName() << endl;
					count++;
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewStudents() {
		system("cls");
		cout << "------------------ STUDENTS REGISTERED -------------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));

			system("cls");
			cout << "------------------ STUDENTS REGISTERED -------------------\n";
			if (courses[cId - 1]->getStudentsCount() > 0) {
				for (int i = 0; i < courses[cId - 1]->getStudentsCount(); i++) {
					cout << i + 1 << ". " << courses[cId - 1]->getStudents()[i]->getName() << endl;
				}
			}
			else {
				cout << "No Students Registered Yet\n";
			}
		}

		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void createQuestion() {
		system("cls");
		cout << "------------------ CREATE QUESTION -------------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			courses[cId - 1]->createQuestion();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void createTopic() {
		system("cls");
		cout << "------------------ CREATE TOPIC -------------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			string topicName;
			do {
				cout << "\nEnter Topic Name: ";
				getline(cin, topicName);
			} while (topicName == "");
			courses[cId - 1]->createTopic(topicName);
			courses[cId - 1]->writeQuestionToFile();

		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void createQuiz() {
		system("cls");
		cout << "------------------ CREATE ASSESSMENT -------------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			courses[cId - 1]->createAssessment();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewResult() {
		system("cls");
		cout << "------------------ RESULTS -------------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			courses[cId - 1]->viewResults();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void assessmentAnalytics() {
		system("cls");
		cout << "------------- ASSESSMENT ANALYTICS -------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			system("cls");
			cout << "------------- ASSESSMENT ANALYTICS -------------\n";
			courses[cId - 1]->printAnalytics();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewTopics() {
		system("cls");
		cout << "------------- TOPICS -------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
					courses[i]->viewTopics();
					cout << endl;
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewQuestions() {
		system("cls");
		cout << "------------- QUESTIONS FROM QUESTION BANK -------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << i + 1 << ". " << courses[i]->getCourseName() << endl;
				}
			}
			do {
				cout << "\nEnter Course ID: ";
				cin >> cId;
			} while ((cId < 1 || cId > *courseCount) || (courses[cId - 1]->getTeacher() && courses[cId - 1]->getTeacher()->getUsername() != this->getUsername()));
			system("cls");
			cout << "------------- QUESTIONS FROM QUESTION BANK -------------\n";
			courses[cId - 1]->viewQuestions();
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void viewAssessments() {
		system("cls");
		cout << "------------- ASSESSMENTS -------------\n";
		if (*courseCount >= 1) {
			int cId;
			for (int i = 0; i < *courseCount; i++) {
				if (courses[i]->getTeacher() && courses[i]->getTeacher()->getUsername() == this->getUsername()) {
					cout << "COURSE " << i + 1 << ": " << courses[i]->getCourseName() << endl;
					courses[i]->viewAssessments();
					cout << endl;
				}
			}
		}
		else {
			cout << "No Courses Have Been Assigned\n";
		}
		system("pause");
	}

	void dashboard() {
		int option;
		bool flag = true;
		while (flag) {
			do {
				system("cls");
				cout << "------------------- DASHBOARD ---------------------\n";
				cout << "1. View Courses\n2. View Students Registered\n3. Create Questions\n4. Create Topics\n5. Create Assessment\n6. Course Result\n7. Assessment Analytics\n8. View Topics\n9. View Questions\n10. View Assessments\n11.EXIT\n";
				cin >> option;
			} while (option < 1 || option>11);
			switch (option) {
			case 1:
				viewCourses();
				break;
			case 2:
				viewStudents();
				break;
			case 3:
				createQuestion();
				break;
			case 4:
				createTopic();
				break;
			case 5:
				createQuiz();
				break;
			case 6:
				viewResult();
				break;
			case 7:
				assessmentAnalytics();
				break;
			case 8:
				viewTopics();
				break;
			case 9:
				viewQuestions();
				break;
			case 10:
				viewAssessments();
				break;
			case 11:
				flag = false;
				break;
			}
		}
		return;
	}
};
