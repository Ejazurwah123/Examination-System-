#pragma once
#include "22i-0474_Topic.h"
#include <fstream>
#include "22i-0474_AssessmentItems.h"
#include "22i-0474_Result.h"

class Student;
class Teacher;

class Course

{
	string courseName;
	string courseCode;
	Topic** topic;
	int topicsCreated;
	int maxTopics;
	Teacher* instructor;
	Student** students;
	AssessmentItems** assessments;
	int studentsCount;
	int maxStudent;
	int maxAssessment;
	int assessmentCount;
	Result* results;
	int maxResults;
	int ResultsCount;
public:
	Course() {
		students = new Student * [50];
		instructor = NULL;
		assessments = new AssessmentItems * [20];
		maxAssessment = 20;
		assessmentCount = 0;
		courseName = "";
		topic = NULL;
		topicsCreated = 0;
		maxTopics = 0;
		studentsCount = 0;
		maxStudent = 50;
		courseCode = "";
		results = new Result[100];
		maxResults = 100;
		ResultsCount = 0;
	}
	Course(string courseName, string courseCode, int size, int seatingCapacity) {
		students = new Student * [seatingCapacity];
		instructor = NULL;
		this->courseName = courseName;
		topic = new Topic*[size];
		topicsCreated = 0;
		maxTopics = size;
		studentsCount = 0;
		maxStudent = seatingCapacity;
		this->courseCode = courseCode;
		assessments = new AssessmentItems * [20];
		maxAssessment = 20;
		assessmentCount = 0;
		results = new Result[seatingCapacity*2];
		maxResults = seatingCapacity*2;
		ResultsCount = 0;
	}

	Course(string courseName, string courseCode, int size, int seatingCapacity, Teacher* teacher) {
		students = new Student * [seatingCapacity];
		instructor = teacher;
		this->courseName = courseName;
		topic = new Topic * [size];
		topicsCreated = 0;
		maxTopics = size;
		studentsCount = 0;
		maxStudent = seatingCapacity;
		this->courseCode = courseCode;
		assessments = new AssessmentItems * [20];
		maxAssessment = 20;
		assessmentCount = 0;
		results = new Result[seatingCapacity * 2];
		maxResults = seatingCapacity * 2;
		ResultsCount = 0;
	}

	void registerStudent(Student* std) {
		students[studentsCount] = std;
		studentsCount++;
	}

	void assignInstructor(Teacher*& teacher) {
		instructor = teacher;
	}

	int createTopic(string topicName) {
		if (topicsCreated < maxTopics) {
			topic[topicsCreated] = new Topic(topicName, 30);
			return topicsCreated++;
		}
		else {
			cout << "Max Limit Reached. More Topics Can Not be Created\n";
		}
		return -1;
	}

	bool writeQuestionToFile() {
		ofstream file;
		file.open("./" + courseName + ".txt");
		if (!file.is_open()) {
			return false;
		}
		for (int i = 0; i < topicsCreated; i++) {
			topic[i]->writeToFile(file);
		}
		return true;
	}

	bool loadQuestions() {
		ifstream file;
		string temp;
		string question;
		int topicNo = 0;
		file.open("./" + courseName + ".txt");
		if (!file.is_open()) {
			cout << "FILE NOT EXISTS. CREATING FILES\n";
			writeQuestionToFile();
			return false;
		}
		while (!file.eof()) {
			getline(file, temp);
			if (temp == "a5380ee") {
				getline(file, temp);
				topicNo = createTopic(temp);
				getline(file, temp);
			}
			if (temp == "2efcde9") {
				string option1, option2, option3, option4;
				int correctOpt;
				getline(file, question);
				getline(file, option1, ':');
				if (option1[option1.length() - 1] == '4') {
					correctOpt = 1;
				}
				getline(file, option1);
				getline(file, option2, ':');
				if (option2[option2.length() - 1] == '4') {
					correctOpt = 2;
				}
				getline(file, option2);
				getline(file, option3, ':');
				if (option3[option3.length() - 1] == '4') {
					correctOpt = 3;
				}
				getline(file, option3);
				getline(file, option4, ':');
				if (option4[option4.length() - 1] == '4') {
					correctOpt = 4;
				}
				getline(file, option4);
				getline(file, temp);
				topic[topicNo]->createQuestion(question, option1, option2, option3, option4, correctOpt);

			}
			if (temp == "b94d27b") {
				bool isTrue = false;
				getline(file, question);
				getline(file, temp, ':');
				if (temp[temp.length() - 1] == '4') {
					isTrue = true;
				}
				getline(file, temp);
				getline(file, temp);
				topic[topicNo]->createQuestion(question, isTrue);
			}
			if (temp == "88f7ace") {
				string question;
				int count = 0;
				while (getline(file, temp) && temp != "") {
					if (count!=0){ temp += "\n"; }
					question += temp;
					count++;
				}
				topic[topicNo]->createQuestion(question, question);
			}
		}
		return true;
	}

	void createAssessment() {
		if (topicsCreated > 0) {
			if (assessmentCount < maxAssessment) {
				int option;
				system("cls");
				cout << "----------- CREATE ASSESSMENT -----------\n";
				cout << "Select Assessment Type...\n";
				cout << "1. Quiz\n2. Assignment\n";
				do {
					cin >> option;
				} while (option < 1 || option>2);

				cout << "\nSelect Assessment Topic: \n";
				int num;
				for (int i = 0; i < topicsCreated; i++) {
					cout << i + 1 << ". " << topic[i]->getName() << endl;
				}
				do {
					cout << "Enter Topic Number: ";
					cin >> num;
				} while (num<1 || num>topicsCreated);
				if (option == 1) {
					if (topic[num - 1]->getQuestionBank()->getQuestionsExixt() > 0) {
						assessments[assessmentCount] = new Quiz();
						assessments[assessmentCount]->createAssement(topic[num - 1]);
						assessmentCount++;
					}
					else {
						cout << "No Questions Exists for this topic to Create Quiz\n";
					}
				}
				else {
					if (topic[num - 1]->getQuestionBank()->getDescriptiveCount() > 0) {
						assessments[assessmentCount] = new Assignment();
						assessments[assessmentCount]->createAssement(topic[num - 1]);
						assessmentCount++;
					}
					else {
						cout << "No Questions Exists for this topic to Create Assignment\n";
					}
				}
			}
			else {
				cout << "Assessments Limit Reached\n";
			}
		}
		else {
			cout << "Topic Not Created\n";
		}
		
	}

	void loadAssessments() {
		ifstream file;
		file.open("assessments.txt");
		if (!file.is_open()) {
			cout << "UNABLE TO LOAD ASSESSMENTS\n";
			return;
		}
		int id, mcq, des, tf, mcqMrk, tfMrk;
		long long pub_date, due_date;
		string temp, type, topicName;
		while (!file.eof()) {
			getline(file, temp, ',');
			if (temp == "") { break; }
			id = stoi(temp);
			getline(file, type, ',');
			getline(file, topicName, ',');

			bool is_continue = false;
			for (int i = 0; i < topicsCreated; i++) {
				if (topic[i]->getName() == topicName) {
					is_continue = true;
				}
			}
			if (is_continue) {
				getline(file, temp, ',');
				pub_date = stoll(temp);
				cout << pub_date << endl;
				getline(file, temp, ',');
				due_date = stoll(temp);
				cout << due_date << endl;
				int i = 0;
				for (i = 0; i < topicsCreated; i++) {
					if (topic[i]->getName() == topicName) {
						break;
					}
				}
				if (type == "Quiz") {
					getline(file, temp, ',');
					mcq = stoi(temp);
					getline(file, temp, ',');
					des = stoi(temp);
					getline(file, temp, ',');
					tf = stoi(temp);
					getline(file, temp, ',');
					mcqMrk = stoi(temp);
					getline(file, temp);
					tfMrk = stoi(temp);
					assessments[assessmentCount] = new Quiz(topic[i], pub_date, due_date, mcq, des, tf, mcqMrk, tfMrk);
					assessmentCount++;
				}
				else {
					getline(file, temp);
					des = stoi(temp);
					assessments[assessmentCount] = new Assignment(topic[i], pub_date, due_date, des);
					assessmentCount++;
				}
			}
			else {
				getline(file, temp);
			}
			
		}
	}

	void attemptAssessment(string s) {
		if (assessmentCount > 0) {
			int num;
			cout << "----------- ASSESSMENTS --------------\n";
			for (int i = 0; i < assessmentCount; i++) {
				cout << i + 1 << ". " << assessments[i]->getTopic()->getName() << " " << assessments[i]->getType() << '\t' << (assessments[i]->getDate().isInDueTime() ? "Assigned" : "Deadline Passed") << endl;
			}
			do {
				cout << "\nEnter Assessment Number to Continue: \n";
				cin >> num;
			} while (num<1 || num>assessmentCount);
			double marks = assessments[num - 1]->attemptAssessment(s);
			if (marks != -1) {
				cout << "Hooray! You got " << marks << " Marks\n";
				results[ResultsCount].addResult(s, marks, assessments[num - 1]);
				ResultsCount++;
			}
		}
		else {
			cout << "No Assessments Available\n";
		}
	}

	void viewResults() {
		system("cls");
		cout << "--------- RESULTS -----------\n";
		if (ResultsCount > 0) {
			int num;
			cout << "Select an Assessment to Show the Results\n";
			for (int i = 0; i < assessmentCount; i++) {
				cout << i + 1 << ". " << assessments[i]->getTopic()->getName() << " " << assessments[i]->getType() << endl;
			}
			do {
				cout << "\nEnter Assessment Number to Continue: ";
				cin >> num;
			} while (num <1 || num>assessmentCount);
			for (int i = 0; i < ResultsCount; i++) {
				if (results[i].getAssessment()->getTopic() == assessments[num - 1]->getTopic() && results[i].getAssessment()->getType() == assessments[num - 1]->getType())
				{
					cout << results[i].getStudent() << "\t" << results[i].getMarks() << endl;
				}
			}
		}
		else {
			cout << "No Results to Show\n";
		}
	}

	void viewResults(string student) {
		if (ResultsCount > 0) {
			for (int i = 0; i < ResultsCount; i++) {
				if (results[i].getStudent() == student)
				{
					cout << i+1 << ". " << results[i].getAssessment()->getTopic()->getName() << ' ' << results[i].getAssessment()->getType() << "\t" << results[i].getMarks() << endl;
				}
			}
		}
		else {
			cout << "No Results to Show\n";
		}
	}


	void printAnalytics() {
		if (ResultsCount > 0 && assessmentCount > 0) {
			for (int i = 0; i < assessmentCount; i++) {
				cout << "Assessment: " << assessments[i]->getTopic()->getName() << endl;
				for (int j = 0; j < assessments[i]->getTopic()->getQuestionBank()->getQuestionsExixt(); j++) {
					cout << "\n-------------------------------------------------------------------------------------" << endl;
					cout << assessments[i]->getTopic()->getQuestionBank()->getQuestion(j)->getQuestion() << endl;
					int wrong = assessments[i]->getTopic()->getQuestionBank()->getQuestion(j)->getWrong();
					int right = assessments[i]->getTopic()->getQuestionBank()->getQuestion(j)->getRight();
					double correct;
					if (wrong == right) { correct = 1; }
					else {
						int total = wrong + right;
						correct = double(right) / double(total);
					}
					correct *= 40;
					cout << "Correct (#)\t Wrong(-)\n";
					cout << "Bar Graph (" << correct << ") : ";
					for (int i = 0; i < 40; i++) {
						if (correct < 40) {
							cout << '#';
						}
						else {
							cout << '-';
						}
					}
					cout << endl << endl;
				}
			}
		}
		else {
			cout << "No Examination have been conducted Yet\n";
		}
	}

	Teacher* getTeacher() { return instructor; }
	string getCourseName() { return courseName; }
	Student** getStudents() const { return students; }
	int getStudentsCount() const { return studentsCount; }
	int getMaxStudent() const { return maxStudent; }
	string getCourseCode() const { return courseCode; }
	int getAssessmentCount() const { return assessmentCount; }
	AssessmentItems* getAssessment(int id) const { return assessments[id]; }
	int getMaxTopics() const { return maxTopics; }


	void viewTopics() {
		if (topicsCreated > 0) {
			for (int i = 0; i < topicsCreated; i++) {
				cout << '\t' << i + 1 << ". " << topic[i]->getName() << endl;
			}
		}
		else {
			cout << "No Topics Exixts";
		}
	}

	void viewQuestions() {
		if (topicsCreated > 0) {
			for (int i = 0; i < topicsCreated; i++) {
				cout << "TOPIC " << i + 1 << ": " << topic[i]->getName() << endl;
				for (int j = 0; j < topic[i]->getQuestionBank()->getQuestionsExixt(); j++) {
					topic[i]->getQuestionBank()->getQuestion(j)->print();
					cout << endl;
				}
			}
		}
		else {
			cout << "No Topics Exixts";
		}
	}

	void createQuestion() {
		if (topicsCreated > 0) {
			int num;
			cout << "Select Topic to Proceed...\n";
			for (int i = 0; i < topicsCreated; i++) {
				cout << i + 1 << ". " << topic[i]->getName() << endl;
			}
			do {
				cout << "Enter Topic Number: ";
				cin >> num;
			} while (num<1 || num>topicsCreated);
			topic[num - 1]->createQuestion();
			writeQuestionToFile();
		}
		else {
			cout << "No Topics Exixts";
		}
	}

	bool viewAssessments() {
		if (assessmentCount > 0) {
			for (int i = 0; i < assessmentCount; i++) {
				cout << i + 1 << ". " << assessments[i]->getTopic()->getName() << " " << assessments[i]->getType() << (assessments[i]->getDate().isInDueTime() ? "\tAssigned" : "\tDeadline Passed") << endl;
			}
			return true;
		}
		else {
			cout << "No Assessments Exixts\n";
			return false;
		}
	}
};
