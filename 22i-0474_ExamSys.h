#pragma once
#include <Windows.h>
#include <iostream>
#include "22i-0474_Course.h"
#include "22i-0474_Users.h"
#include "i220474_Admin.h"
#include <conio.h>


class  ExaminationSys

{
	Authentication auth;
	Registration reg;
	Admin* admin;
	Teacher** teachers;
	Student** students;
	Course** courses;
	int stdCount;
	int techCount;
	int courseCount;
	int maxStd;
	int maxTech;
	int maxCourse;

public:
	ExaminationSys() {
		admin = NULL;
		courses = new Course* [10];
		teachers = new Teacher* [20];
		students = new Student* [300];
		stdCount = 0;
		techCount = 0;
		courseCount = 0;
		maxStd = 300;
		maxTech = 20;
		maxCourse = 10;
	}

	ExaminationSys(int techCount, int stdCount, int courseCount) {
		admin = NULL;
		courses = new Course * [courseCount];
		teachers = new Teacher * [techCount];
		students = new Student * [stdCount];
		this->stdCount = 0;
		this->techCount = 0;
		this->courseCount = 0;
		maxStd = techCount;
		maxTech = stdCount;
		maxCourse = courseCount;
	}

	void loadData() {
		cout << "Process: Loading Users Data...\n";
		ifstream file;
		string temp;
		file.open("./users.txt");
		if (!file.is_open()) {
			cout << "Unable to Load Users Data\n";
		}
		else {
			string name, address, email, dob, username;
			while (!file.eof()) {
				getline(file, username, ',');
				getline(file, temp, ',');
				getline(file, temp, ',');
				if (temp == "Admin") {
					getline(file, name, ',');
					getline(file, address, ',');
					getline(file, email, ',');
					getline(file, dob, '\n');
					admin = new Admin(name, address, email, dob, username, teachers, students, &stdCount, &techCount, &maxStd, &maxTech);
				}
				else if (temp == "Teacher") {
					getline(file, name, ',');
					getline(file, address, ',');
					getline(file, email, ',');
					getline(file, dob, '\n');
					teachers[techCount++] = new Teacher(name, address, email, dob, username, courses, &courseCount, &maxCourse);
				}
				else if (temp == "Student") {
					getline(file, name, ',');
					getline(file, address, ',');
					getline(file, email, ',');
					getline(file, dob, '\n');
					students[stdCount++] = new Student(name, address, email, dob, username, courses, &courseCount, &maxCourse, students, &stdCount, &maxStd);
				}
				else {
					getline(file, temp);
				}
			}
			admin->updateData(teachers, students, &stdCount, &techCount, &maxStd, &maxTech, courses, &courseCount, &maxCourse);
			cout << "Success: Users Data Loaded\n";
		}
		cout << "Process: Loading Courses Data...\n";
		ifstream file1;
		file1.open("./courses.txt");
		if (!file1.is_open()) {
			cout << "Unable to Load Courses Data\n";
		}
		else {
			string cName, cCode, cTopicNum, cCapacity, cTeacherName;
			while (!file1.eof()) {
				getline(file1, cName, ',');
				getline(file1, cCode, ',');
				getline(file1, cTopicNum, ',');
				getline(file1, cCapacity, ',');
				getline(file1, cTeacherName, '\n');
				if (cTeacherName == "") {
					courses[courseCount] = new Course(cName, cCode, stoi(cTopicNum), stoi(cCapacity));
					courses[courseCount]->loadQuestions();
					courses[courseCount]->loadAssessments();
					courseCount++;
				}
				else {
					int i = 0;
					for (i; i < techCount; i++) {
						if (teachers[i]->getUsername() == cTeacherName) {
							break;
						}
					}
					courses[courseCount] = new Course(cName, cCode, stoi(cTopicNum), stoi(cCapacity), teachers[i]);
					courses[courseCount]->loadQuestions();
					courses[courseCount]->loadAssessments();
					courseCount++;
				}
			}
			cout << "Success: Courses Data Loaded\n";
		}
		cout << "Process: Loading Course Registations Data...\n";
		ifstream file2;
		file2.open("./courseRegistration.csv");
		if (!file2.is_open()) {
			cout << "Unable to Load Courses Registrations Data\n";
		}
		else {
			string temp;
			getline(file2, temp);
			getline(file2, temp);
			for (int i = 0; i< stdCount && (!file2.eof()); i++) {
				getline(file2, temp, ',');
				getline(file2, temp, ',');
				getline(file2, temp, ',');

				for (int j = 0; j < courseCount;j++){
					if (j == courseCount-1) {
						getline(file2, temp, '\n');
					}
					else {
						getline(file2, temp, ',');
					}
					if (temp == "1") {
						courses[j]->registerStudent(students[i]);
					}
					
				}
				cout << i << endl;
			}
		}
		cout << "Success: Course Registations Loaded...\n";
		system("pause");
	}
    
    
	void login() {
		string username, password = "", response;
		char temp = ' ';
		do {
			system("cls");
			cout << "------------- LOGIN ---------------\n";
			cout << "Enter UserName: ";
			cin >> username;
			cout << "Enter Password: ";
			password = "";
			while ((temp = _getch()) && (temp != 13)) {
				if (temp == '\b') {
					password.pop_back();
					cout << "\b \b";
				}
				else {
					password += temp;
					cout << '*';
				}
			}
			response = auth.authenticateUser(username, password);
			cout << response << endl;

			if (response == "Student") {
				for (int i = 0; i < stdCount; i++) {
					if (username == students[i]->getUsername()) {
						students[i]->dashboard();
						break;
					}
				}
			}
			else if (response == "Teacher") {
				for (int i = 0; i < techCount; i++) {
					if (username == teachers[i]->getUsername()) {
						teachers[i]->dashboard();
						break;
					}
				}
			}
			else if (response == "Admin") {
				if (!admin) {
					cout << "No Admin Exists\n";
					return;
				}
				admin->dashboard();
			}
			else if (response == "Error while File Opening") {
				cout << "The System is Unable to Read the Users Data\n";
			}
			else if (response == "UserName/Password Error") {
				cout << "Wrong Username / Password Entered. Please Try Again...\n";
			}
			else {
				cout << "No User having username: " << username << " found.\n";
			}
			do {
				cout << "Do you want to Try Logging In Again (Y or N) ?";
				cin >> response;
			} while (!(response == "Y" || response == "N" || response == "n" || response == "y"));
		} while (response == "Y" || response == "y");
	}

	
	void home() {
		system("cls");
		cout << "---------- EXAMINATION SYSTEM -----------\n";
		cout << "----------------- HOME ------------------\n";
		cout << "\n\nThis Program Offers Many Features: \n";
		cout << "1. Courses Management\n2. Students Management\n3. Teachers Management\n4. Results Management\n";
		system("pause");
	}
	void coursePage() {
		system("cls");
		cout << "---------- EXAMINATION SYSTEM -----------\n";
		cout << "--------------- COURSES ----------------_\n";
		for (int i = 0; i < courseCount; i++) {
			cout << "Course " << i+1 << ". " << courses[i]->getCourseName() << endl;
			courses[i]->viewTopics();
			cout << "\n\n";
		}
		system("pause");
	}

	void start() {
		loadData();
		int option = 0;
		bool flag = true;
		while (flag) {
			do {
				system("cls");
				cout << "-------------- WELCOME TO EXAMINATION SYSTEM -------------\n";
				cout << "1. Home\n2. Courses\n3. Login\n4. EXIT\nEnter Option: ";
				cin >> option;
			} while (option < 1 || option>4);
			switch (option) {
			case 1:
				home();
				break;
			case 2:
				coursePage();
				break;
			case 3:
				login();
				break;
			case 4:
				flag = false;
				break;
			}
		}
	}

	Teacher**& getTeachers() { return teachers; }
	Student**& getStudents() { return students; }
	Course**& getCourse() { return courses; }
	int& getStdCount() { return stdCount; }
	int& getTechCount() { return techCount; }
	int& getMaxStd() { return maxStd; }
	int& getMaxTech() { return maxTech; }
};

