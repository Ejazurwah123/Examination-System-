#pragma once
#include "22i-0474_Users.h"
#include "22i-0474_Course.h"


class Admin : User {
    
	Registration reg;
	Authentication auth;
	Teacher** teachers;
	Student** students;
	int* stdCount;
	int* techCount;
	int* maxStd;
	int* maxTech;
	Course** courses;
	int* courseCount;
	int* courseMax;
    
public:
    
	Admin() {
		teachers = NULL;
		students = NULL;
	}
	Admin(string name, string address, string email, string dob, string username, Teacher**& teachers, Student**& students, int* stdCount, int* techCount, int* maxStd, int* maxTech) : User(name, address, email, dob, username) {
		this->teachers = teachers;
		this->students = students;
		this->stdCount = stdCount;
		this->techCount = techCount;
		this->maxStd = maxStd;
		this->maxTech = maxTech;
		this->courses = NULL;
		this->courseCount = NULL;
		this->courseMax = NULL;
	}

	void updateData(Teacher**& teachers, Student**& students, int* stdCount, int* techCount, int* maxStd, int* maxTech, Course** courses, int* courseCount, int* courseMax) {
		this->teachers = teachers;
		this->students = students;
		this->stdCount = stdCount;
		this->techCount = techCount;
		this->maxStd = maxStd;
		this->maxTech = maxTech;
		this->courses = courses;
		this->courseCount = courseCount;
		this->courseMax = courseMax;
	}
	void registerStudent() {
		system("cls");
		if (stdCount < maxStd) {
			string username, pass, c_pass, Name, Address, Email, DOB;
			cout << "------------- REGISTER STUDENT ---------------\n";
			
            do {
				cout << "Enter UserName: ";
				cin >> username;
			} while (auth.checkUserExists(username));
			
            do {
				cout << "Enter Password: ";
				cin >> pass;
				cout << "Re_Enter Password: ";
				cin >> c_pass;
			} while (pass != c_pass);
			
            do {
				cout << "Enter Name: ";
				getline(cin, Name);
			} while (Name == "");
			
            do {
				cout << "Enter Address: ";
				getline(cin, Address);
			} while (Address == "");
			
            do {
				cout << "Enter Email: ";
				cin >> Email;
			} while (Email == "");
			do {
				cout << "Enter DOB (YYYY-MM-DD): ";
				cin >> DOB;
			} while (DOB == "");
			if (reg.registerUser(username, pass, "Student", Name, Address, Email, DOB)) {
				students[*stdCount] = new Student(Name, Address, Email, DOB, username, courses, courseCount, courseMax, students, stdCount, maxStd);
				stdCount++;
				cout << "Student Registered Successfully\n";
			}
			else {
				cout << "Unable to Register User";
			}
		}
		else {
			cout << "Unable to create Students. MAX LIMIT REACHED\n";
		}
		system("pause");
	}

	void viewCourses() {
		system("cls");
		cout << "------------------ COURSES -------------------\n";
		if (*courseCount >= 1) {
			for (int i = 0; i < *courseCount; i++) {
				cout << i+1 << ". " << courses[i]->getCourseName() << endl;
			}
		}
		else {
			cout << "No Courses Found\n";
		}
		system("pause");
	}

	void assignTeacherCourses() {
		system("cls");
		cout << "------------------ COURSES -------------------\n";
		if (*courseCount >= 1) {
			int cNum, tNum;
			for (int i = 0; i < *courseCount; i++) {
				cout << i + 1 << ". " << courses[i]->getCourseName() << '\t' << (courses[i]->getTeacher() ? courses[i]->getTeacher()->getName() : "No Teacher Allocated") << endl;
			}
			do {
				cout << "\nEnter Course Number: ";
				cin >> cNum;
			} while (cNum < 1 || cNum > *courseCount);
			
			cout << "\nSelect Teacher to Assign: ";
			for (int i = 0; i < *techCount; i++) {
				cout << i+1 << ". " << teachers[i]->getName() << endl;
			}
			do {
				cout << "Enter Teacher Number: ";
				cin >> tNum;
			} while (tNum < 1 || tNum > *techCount);
			courses[cNum - 1]->assignInstructor(teachers[tNum - 1]);
			updateCourses();
			cout << "Instructor Assigned Successfully\n";
		}
		else {
			cout << "No Courses Found\n";
		}
		system("pause");
	}

	void updateCourseRegistrations() {
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
		for (int k = 0; k < *stdCount; k++) {
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
					if (i != *courseCount - 1) { file << ','; }
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

	void createCourse() {
		system("cls");
		cout << "------------------ COURSE CREATION -------------------\n";
		if (*courseCount < *courseMax) {
			string cName, cCode;
			int cLimit;
			cin.ignore();
			do {
				cout << "Enter Course Name: ";
				getline(cin, cName);
			} while (cName == "");
			do {
				cout << "Enter Course Code: ";
				getline(cin, cCode);
			} while (cCode == "");
			do {
				cout << "Enter Course Students Limit: ";
				cin >> cLimit;
			} while (cLimit < 1 && cLimit > 100);
			courses[*courseCount] = new Course(cName, cCode, 10, cLimit);
			(*courseCount)++;
			ofstream file;
			file.open("courses.txt", ios::out|ios::app);
			if (!file.is_open()) {
				cout << "COURSE UNABLE TO UPDATE IN FILE\n";
			}
			else {
				file << '\n' << cName << ',' << cCode << ',' << 10 << ',' << cLimit << ',';
				file.close();
			}
			updateCourseRegistrations();
		}
		else {
			cout << "MAX LIMIT REACHED. No Course can be added\n";
		}
		system("pause");
	}

	void updateCourses() {
		ofstream file1;
		file1.open("./courses.txt");
		if (!file1.is_open()) {
			cout << "Unable to Upadate Courses Data\n";
		}
		else {
			for (int i = 0; i < *courseCount; i++) {
				file1 << courses[i]->getCourseName() << ',' << courses[i]->getCourseCode() << ',' << courses[i]->getMaxTopics() << ',' << courses[i]->getMaxStudent() << ',' << (courses[i]->getTeacher() ? courses[i]->getTeacher()->getUsername() : "") << endl;
			}
			file1.close();
		}
	}

	void registerTeacher() {
		system("cls");
		if (techCount < maxTech) {
			string username, pass, c_pass, Name, Address, Email, DOB;
			cout << "------------- REGISTER TEACHER ---------------\n";
			do {
				cout << "Enter UserName: ";
				cin >> username;
			} while (auth.checkUserExists(username));
			do {
				cout << "Enter Password: ";
				cin >> pass;
				cout << "Re_Enter Password: ";
				cin >> c_pass;
			} while (pass != c_pass);
			do {
				cout << "Enter Name: ";
				getline(cin, Name);
			} while (Name == "");
			do {
				cout << "Enter Address: ";
				getline(cin, Address);
			} while (Address == "");
			do {
				cout << "Enter Email: ";
				cin >> Email;
			} while (Email == "");
			do {
				cout << "Enter DOB (YYYY-MM-DD): ";
				cin >> DOB;
			} while (DOB == "");
			if (reg.registerUser(username, pass, "Teacher", Name, Address, Email, DOB)) {
				teachers[*techCount] = new Teacher(Name, Address, Email, DOB, username, courses, courseCount, courseMax);
				techCount++;
				cout << "Teacher Registered Successfully\n";
			}
			else {
				cout << "Unable to Register Teacher";
			}
		}
		else {
			cout << "Unable to create Teacher. MAX LIMIT REACHED\n";
		}
		system("pause");
	}

	void viewStudents() {
		system("cls");
		cout << "----------- STUDENTS ------------\n";
		cout << "Total Students: " << stdCount << endl << "Max Student: " << maxStd << endl;
		for (int i = 0; i < *stdCount; i++) {
			cout << i+1<<students[i]->getName() << "\t" << students[i]->getEmail() << "\t" << students[i]->getDOB() << endl;
		}
		system("pause");
	}

	void viewTeachers() {
		system("cls");
		cout << "----------- TEACHERS ------------\n";
		for (int i = 0; i < *techCount; i++) {
			cout << teachers[i]->getName() << "\t" << teachers[i]->getEmail() << "\t" << teachers[i]->getDOB() << endl;
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
				cout << "1. Register User\n2. Register Teacher\n3. View Users\n4. View Teachers\n5. Create Courses\n6. View Courses\n7. Assign Courses\n8. EXIT\n";
				cin >> option;
			} while (option < 1 || option>8);
			switch (option) {
			case 1:
				registerStudent();
				break;
			case 2:
				registerTeacher();
				break;
			case 3:
				viewStudents();
				break;
			case 4:
				viewTeachers();
				break;
			case 5:
				createCourse();
				break;
			case 6:
				viewCourses();
				break;
			case 7:
				assignTeacherCourses();
				break;
			case 8:
				flag = false;
				break;
			}
		}
		return;
	}
};
