#pragma once
#include "22i-0474_DateTime.h"
#include "22i-0474_Topic.h";
#include "22i-0474_QuizAttandance.h"

class AssessmentItems {
	static int count;
	int id;
	DateTime date;
	AssessmentAttandance* attandance;
	Topic* topic;
	string type;
public:
	AssessmentItems() {
		topic = NULL;
		type = "";
		id = count;
		count++;
		attandance = new AssessmentAttandance(50, id);
	}
	AssessmentItems(string type) {
		topic = NULL;
		this->type = type;
		id = count;
		count++;
		attandance = new AssessmentAttandance(50, id);
	}
	AssessmentItems(string type, Topic* topic) {
		this->topic = topic;
		this->type = type;
		id = count;
		count++;
		attandance = new AssessmentAttandance(50, id);
	}
	Topic* getTopic() { return topic; }
	DateTime& getDate() { return date; }
	void setTopic(Topic* topic) { this->topic = topic; }
	void virtual createAssement(Topic*& topic) = 0;
	double virtual attemptAssessment(string StudentName) = 0;
	AssessmentAttandance& getAttandance() { return *attandance; }
	string getType() { return type;}
	int getId() { return id; }
};

int AssessmentItems::count = 1;

class Quiz :public AssessmentItems {
	int mcqCount, desCount, trueFalseCount,mcqMrk, tfMrk;
public:
	Quiz() : AssessmentItems("Quiz") {
		mcqCount = 0; 
		desCount = 0; 
		trueFalseCount = 0; 
		mcqMrk = 0; 
		tfMrk = 0;
	}

	Quiz(Topic* topic, long long pub_time, long long dueTime, int mcq, int des, int tf, int mcqMrks, int tfMrks) : AssessmentItems("Quiz", topic) {
		mcqCount = mcq;
		desCount = des;
		trueFalseCount = tf;
		mcqMrk = mcqMrks;
		tfMrk = tfMrks;
		getDate().setDateTime(pub_time, dueTime);
	}

	void createAssement(Topic*& topic) {
		if (topic->getQuestionBank()->getQuestionsExixt() > 0) {
			string dateDue;
			int hour, min;
			cout << "--------- ASSESSMENT ITEM CREATION (QUIZ) ---------\n";
			cout << "Enter Due Date in this format (YYYY-MM-DD): ";
			cin >> dateDue;
			do {
				cout << "Enter Hour Due (0 - 23): ";
				cin >> hour;
			} while (hour < 0 || hour>23);
			do {
				cout << "Enter Min Due: ";
				cin >> min;
			} while (min < 0 || min > 59);
			getDate().setTime(dateDue, hour, min);
			setTopic(topic);
			int maxMCQ = topic->getNoOfMCQ();
			int maxTrueFalse = topic->getNoOfTrueFalse();
			int maxDescriptive = topic->getNoOfDescriptive();
			do {
				cout << "Enter Maximum MCQ for Test (max: " << maxMCQ << "): ";
				cin >> mcqCount;
			} while (mcqCount<0 || mcqCount > maxMCQ);
			do {
				cout << "Enter Maximum Descriptive for Test (max: " << maxDescriptive << "): ";
				cin >> desCount;
			} while (desCount<0 || desCount > maxDescriptive);
			do {
				cout << "Enter Maximum True False for Test (max: " << maxTrueFalse << "): ";
				cin >> trueFalseCount;
			} while (trueFalseCount<0 || trueFalseCount > maxTrueFalse);
			do {
				cout << "Enter Marks for each MCQ: ";
				cin >> mcqMrk;
			} while (mcqMrk < 1 || mcqMrk > 100);
			do {
				cout << "Enter Marks for each True False Question: ";
				cin >> tfMrk;
			} while (tfMrk < 1 || tfMrk > 100);

			ofstream file;
			file.open("assessments.txt", ios::out | ios::app);
			file << getId() << ',' << getType() << ',' << topic->getName() << ',' << getDate().getDateTime() << ',' << mcqCount << ',' << desCount << ',' << trueFalseCount << ',' << mcqMrk << ',' << tfMrk << endl;
			file.close();
		}
		else {
			cout << "No Question exist in this Topic\n";
		}
		
	}

	double attemptAssessment(string StudentName) {
		if (getTopic() == NULL) {
			cout << "Assessment Not Created\n";
			return -1;
		}
		if (!getDate().isInDueTime()) {
			cout << "Assessment Due Time is Over\n";
			return -1;
		}
		if (getAttandance().hasAttanded(StudentName)) {
			cout << "Assessment Already Attempted\n";
			return -1;
		}
		Question** questions = getTopic()->getQuestions(mcqCount, desCount, trueFalseCount);
		double marks = 0.0;
		int cOpt, enteredOpt;
		for (int i = 0; i < mcqCount + desCount + trueFalseCount; i++) {
			if (questions[i]->getType() == "MCQ") {
				cOpt = questions[i]->print();
				cin >> enteredOpt;
				if (cOpt == enteredOpt) {
					marks += 1;
					questions[i]->addRight();
				}
				else {
					questions[i]->addWrong();
				}
			}else if (questions[i]->getType() == "TrueFalse") {
				cOpt = questions[i]->print();
				cin >> enteredOpt;
				if (enteredOpt == 1 && cOpt == 1 || enteredOpt == 2 && cOpt == 0) {
					marks += 1;
					questions[i]->addRight();
				}
				else {
					questions[i]->addWrong();
				}
			}
			else {
				string answer;
				int count = 0;
				questions[i]->print();
				cin.ignore();
				getline(cin, answer);
				for (int j = 0; j < answer.length(); j++) {
					if (answer[j] == ' ') {
						count++;
					}
				}
				count = count * 0.01;
				marks += count;
			}
		}
		getAttandance().addAttandance(StudentName, getTopic()->getName(), "MCQ");
		return marks;
	}
};

class Assignment : public AssessmentItems {
	int desCount;
public:
	Assignment() : AssessmentItems("Assignment") {
		desCount = 0;
	}
	Assignment(Topic* topic, int des, long long pub_time, long long dueTime) : AssessmentItems("Assignment", topic) {
		desCount = des;
		getDate().setDateTime(pub_time, dueTime);
	}
	void createAssement(Topic*& topic) {
		string dateDue;
		int hour, min;
		cout << "--------- ASSESSMENT ITEM CREATION (ASSIGNMENT) ---------\n";
		cout << "Enter Due Date in this format (YYYY-MM-DD): ";
		cin >> dateDue;
		do {
			cout << "Enter Hour Due (0 - 23): ";
			cin >> hour;
		} while (hour < 0 || hour>23);
		do {
			cout << "Enter Min Due: ";
			cin >> min;
		} while (min < 0 || min > 59);
		getDate().setTime(dateDue, hour, min);
		setTopic(topic);
		int maxDescriptive = topic->getNoOfDescriptive();
		do {
			cout << "Enter Maximum Descriptive Questions for Assignment (max: " << maxDescriptive << "): ";
			cin >> desCount;
		} while (desCount<0 || desCount > maxDescriptive);
		ofstream file;
		file.open("assessments.txt", ios::out | ios::app);
		file << getId() << ',' << getType() << ',' << topic->getName() << ',' << getDate().getDateTime() << ','  << desCount << endl;
		file.close();
	}
	double attemptAssessment(string StudentName) {
		if (getTopic() == NULL) {
			cout << "Assessment Not Created\n";
			return -1;
		}
		if (!getDate().isInDueTime()) {
			cout << "Assessment Due Time is Over\n";
			return -1;
		}
		if (getAttandance().hasAttanded(StudentName)) {
			cout << "Assessment Already Attempted\n";
			return -1;
		}
		Question** questions = getTopic()->getQuestions(0 ,desCount, 0);
		double marks = 0.0;
		string answer;
		double count = 0;
		for (int i = 0; i < desCount; i++) {
			questions[i]->print();
			cin.ignore();
			getline(cin, answer);
			for (int j = 0; j < answer.length(); j++) {
				if (answer[j] == ' ') {
					count++;
				}
			}
			count = count * 0.01;
			marks += count;
		}
		getAttandance().addAttandance(StudentName, getTopic()->getName(), "Assignment");
		return marks;
	}
};
