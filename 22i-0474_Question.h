#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Question {
	string topic;
	string type;
	int wrong;
	int right;
public:
	Question() {
		topic = "";
		type = "";
		wrong = 0;
		right = 0;
	}
	Question(string type) {
		topic = "";
		this->type = type;
		wrong = 0;
		right = 0;
	}
	Question(string topic, string type) {
		this->topic = topic;
		this->type = type;
		wrong = 0;
		right = 0;
	}
	void virtual createQuestion(string topic) = 0;
	int virtual print() = 0;
	void virtual writeToFile(ofstream& file) = 0;
	void setTopic(string topic) {
		this->topic = topic;
	}
	void setType(string type) {
		this->type = type;
	}
	string getType() { return type; }
	string getTopic() { return topic; }
	int getWrong() { return wrong; }
	int getRight() { return right; }
	void addWrong() { wrong += 1; }
	void addRight() { right += 1; }
	string virtual getQuestion() = 0;
};

class MCQ : public Question {
	string question;
	string options[4];
	int correctOption;
public:
	MCQ():Question("MCQ") {
		question = "";
		for (string i : options) {
			i = "";
		}
		correctOption = 0;
	}
	MCQ(string topic, string question, string option1, string option2, string option3, string option4, int correctOption):Question(topic, "MCQ") {
		this->question = question;
		options[0] = option1;
		options[1] = option2;
		options[2] = option3;
		options[3] = option4;
		this->correctOption = correctOption;
		setTopic(topic);
	}
	void createQuestion(string topic) {
		do {
			cout << "Enter Question: ";
			getline(cin, question);
		} while (question == "");
		do {
			cout << "Enter Option 1: ";
			getline(cin, options[0]);
		} while (options[0] == "");
		do {
			cout << "Enter Option 2: ";
			getline(cin, options[1]);
		} while (options[1] == "");
		do {
			cout << "Enter Option 3: ";
			getline(cin, options[2]);
		} while (options[2] == "");
		do {
			cout << "Enter Option 4: ";
			getline(cin, options[3]);
		} while (options[3] == "");
		do {
			cout << "Enter Correct Option Number (1 - 4) : ";
			cin >> correctOption;
		} while (correctOption < 1 || correctOption > 4);
		setType("MCQ");
		setTopic(topic);
	}
	void writeToFile(ofstream& file) {
		file << "2efcde9\n";
		file << question << endl;
		for (int i = 0; i < 4; i++) {
			if (i + 1 == correctOption) {
				file << "option dabfac4:";
			}
			else {
				file << "option:";
			}
			file << options[i] << endl;
		}
		file << endl;
	}
	MCQ* shuffle() {
		string Array[5];
		int arr[4] = { 0,0,0,0 };
		int random;
		bool flag = true;
		for (int i = 1; i <= 4; i++) {
			flag = true;
			while (flag) {
				random = rand() % 4 + 1;
				if (arr[random] == 0) {
					arr[random] = i;
					flag = false;
				}
			}
		}
		int crctopt = 0;
		for (int i = 0; i < 4; i++) {
			if (options[arr[i] - 1] == options[correctOption]) {
				crctopt = i + 1;
			}
		}
	}
	int print() {
		cout << "Q: " << question << endl;
		int arr[4] = { 0,0,0,0 };
		int random;
		bool flag = true;
		for (int i = 1; i <= 4; i++) {
			flag = true;
			while (flag) {
				random = rand() % 4 + 1;
				if (arr[random-1] == 0) {
					arr[random-1] = i;
					flag = false;
				}
			}
		}
		int crctopt = 0;
		for (int i = 0; i < 4; i++) {
			cout << i+1 << ". " << options[arr[i] - 1] << endl;
			if (options[arr[i] - 1] == options[correctOption]) {
				crctopt = i + 1;
			}
		}
		return crctopt;
	}
	string getQuestion() {
		return question;
	}
};

class DescriptiveQuestion : public Question {
    
	string question;
	string correctAnswer;
    
public:
	DescriptiveQuestion() :Question("Descriptive") {
		question = "";
		correctAnswer = "";
	}
	DescriptiveQuestion(string topic, string question, string correctAnswer) :Question(topic, "Descriptive") {
		this->question = question;
		this->correctAnswer = correctAnswer;
	}
	void createQuestion(string topic) {
		do {
			cout << "Enter Question: ";
			getline(cin, question);
		} while (question == "");
		do {
			cout << "Enter correct answer: ";
			getline(cin, correctAnswer);
		} while (correctAnswer == "");
		setType("Descriptive");
		setTopic(topic);
	}
	void writeToFile(ofstream& file) {
		file << "88f7ace\n";
		file << question << endl << endl;
	}
	int print() {
		cout << "Q: " << question << endl;
		return 0;
	}
	string getQuestion() { return question; }
};

class TrueFalseQuestions : public Question {
	string question;
	bool isTrue;
public:
	TrueFalseQuestions() :Question("TrueFalse") {
		question = "";
		isTrue = false;
	}
	TrueFalseQuestions(string topic, string question, bool isTrue) :Question(topic, "TrueFalse") {
		this->question = question;
		this->isTrue = isTrue;
		setTopic(topic);
	}
	void createQuestion(string topic) {
		char opt;
		do {
			cout << "Enter Question: ";
			getline(cin, question);
		} while (question == "");
		do {
			cout << "Is this question True (Y or N): ";
			cin >> opt;
		} while (opt != 'Y' || opt != 'N' || opt != 'y' || opt != 'n');
		opt == 'Y' || opt == 'y' ? isTrue = true : isTrue = false;
		setType("TrueFalse");
		setTopic(topic);
	}
	void writeToFile(ofstream& file) {
		file << "b94d27b\n";
		file << question << endl;
		if (isTrue) {
			file << "option dabfac4: True\noption: False\n\n";
		}
		else {
			file << "option: True\noption dabfac4: False\n\n";
		}
	}
	int print() {
		cout << "Q: " << question << " (T or F): " << endl;
		return isTrue ? 1 : 0;
	}
	string getQuestion() {	return question; }
};
