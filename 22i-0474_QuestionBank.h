#pragma once
#include "22i-0474_Question.h"
#include "22i-0474_Topic.h"

class QuestionBank {
	Question** questions;
	int questionsExist;
	int maxQuestions;
	int MCQCount;
	int DescriptiveCount;
	int TrueFalseCount;

public:
	QuestionBank() {
		questions = NULL;
		questionsExist = 0;
		maxQuestions = 0;
		MCQCount = 0;
		DescriptiveCount = 0;
		TrueFalseCount = 0;
	}
	QuestionBank(int size) {
		questions = new Question*[size];
		questionsExist = 0;
		maxQuestions = size;
		MCQCount = 0;
		DescriptiveCount = 0;
		TrueFalseCount = 0;
	}
	void createQuestion(string topic) {
		if (questionsExist < maxQuestions) {
			int questionType;
			string question;
			do {
				cout << "Enter Question Type: \n";
				cout << "1. MCQ\n2. Descriptive\n3. True False\nEnter Option: ";
				cin >> questionType;
			} while (questionType < 1 || questionType > 3);
			switch (questionType) {
			case 1:
				questions[questionsExist] = new MCQ;
				questions[questionsExist]->createQuestion(topic);
				questionsExist++;
				MCQCount++;
				break;
			case 2:
				questions[questionsExist] = new DescriptiveQuestion;
				questions[questionsExist]->createQuestion(topic);
				questionsExist++;
				DescriptiveCount++;
				break;
			case 3:
				questions[questionsExist] = new TrueFalseQuestions;
				questions[questionsExist]->createQuestion(topic);
				questionsExist++;
				TrueFalseCount++;
				break;
			}
		}
		else {
			cout << "Question Bank Limit Reached. More Question Can not be Added.\n";
		}
	}
	void createQuestion(string topic, string question, string option1, string option2, string option3, string option4, int correctOption) {
		if (questionsExist < maxQuestions) {
			questions[questionsExist] = new MCQ(topic, question, option1, option2, option3, option4, correctOption);
			questionsExist++;
			MCQCount++;
		}
		else {
			cout << "Question Bank Limit Reached. More Question Can not be Added.\n";
		}
	}
	void createQuestion(string topic, string question, string correctAnswer) {
		if (questionsExist < maxQuestions) {
			questions[questionsExist] = new DescriptiveQuestion(topic, question, correctAnswer);
			questionsExist++;
			DescriptiveCount++;
		}
		else {
			cout << "Question Bank Limit Reached. More Question Can not be Added.\n";
		}
	}
	void createQuestion(string topic, string question, bool isTrue) {
		if (questionsExist < maxQuestions) {
			questions[questionsExist] = new TrueFalseQuestions(topic, question, isTrue);
			questionsExist++;
			TrueFalseCount++;
		}
		else {
			cout << "Question Bank Limit Reached. More Question Can not be Added.\n";
		}
	}

	void writeToFile(ofstream& file) {
		for (int i = 0; i < questionsExist; i++) {
			questions[i]->writeToFile(file);
		}
	}

	int getTrueFalseCount() { return TrueFalseCount; }
	int getDescriptiveCount() { return DescriptiveCount; }
	int getMCQCount() { return MCQCount; }
	int getMaxQuestion() { return maxQuestions; }
	int getQuestionsExixt() { return questionsExist; }
	Question** getQuestion() { return questions; }
	Question* getQuestion(int i) { return questions[i]; }

	Question** getQuestions(int mcq, int tf, int des) {
		Question** questionsArr = new Question*[mcq+tf+des];
		int count = 0;
		for (int i = 0; i < questionsExist && count < mcq; i++) {
			if (questions[i]->getType() == "MCQ") {
				questionsArr[count] = questions[i];
				count++;
			}
		}
		for (int i = 0; i < questionsExist && count < des + mcq; i++) {
			if (questions[i]->getType() == "Descriptive") {
				questionsArr[count] = questions[i];
				count++;
			}
		}
		for (int i = 0; i < questionsExist && count < tf + mcq + des; i++) {
			if (questions[i]->getType() == "TrueFalse") {
				questionsArr[count] = questions[i];
				count++;
			}
		}
		return questionsArr;
	}
};
