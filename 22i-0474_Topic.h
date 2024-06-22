#pragma once
#include "22i-0474_QuestionBank.h"

class Topic {
	QuestionBank* questionBank;
	string topicName;
public:
	Topic() {
		questionBank = new QuestionBank(30);
		topicName = "";
	}
	Topic(string topicName, int size) {
		questionBank = new QuestionBank(size);
		this->topicName = topicName;
	}
	void createQuestion() {
		questionBank->createQuestion(topicName);
	}
	void createQuestion(string question, string option1, string option2, string option3, string option4, int correctOption) {
		questionBank->createQuestion(topicName, question, option1,option2, option3, option4, correctOption);
	}
	void createQuestion(string question, string correctAnswer) {
		questionBank->createQuestion(topicName, question, correctAnswer);
	}
	void createQuestion(string question, bool isTrue) {
		questionBank->createQuestion(topicName, question, isTrue);
	}
	void writeToFile(ofstream& file) {
		file << "a5380ee\n";
		file << topicName << '\n' << '\n';
		questionBank->writeToFile(file);
	}
	int getNoOfMCQ() { return questionBank->getMCQCount(); }
	int getNoOfDescriptive() { return questionBank->getDescriptiveCount(); }
	int getNoOfTrueFalse() { return questionBank->getTrueFalseCount(); }
	string getName() { return topicName; }
	QuestionBank* getQuestionBank() { return questionBank; }

	Question** getQuestions(int mcq, int des, int tf) {
		return questionBank->getQuestions(mcq, tf, des);
	}
};
