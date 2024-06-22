#pragma once
#include <fstream>
#include <string>
using namespace std;

class Authentication {
	string usersFileName;
public:
	Authentication() {
		usersFileName = "./users.txt";
	}
	string authenticateUser(string username, string password) {
		ifstream file;
		file.open(usersFileName);
		if (!file.is_open()) {
			return "Error while File Opening";
		}
		string temp;
		while (!file.eof()) {
			if (getline(file, temp, ',') && temp == username) {
				if (getline(file, temp, ',') && temp == password) {
					getline(file, temp, ',');
					file.close();
					return temp;
				}
				file.close();
				return "UserName/Password Error";
			}
			else {
				getline(file, temp);
			}
		}
		file.close();
		return "No User";
	}

	bool checkUserExists(string username) {
		ifstream file;
		file.open(usersFileName);
		if (!file.is_open()) {
			return false;
		}
		string temp;
		while (!file.eof()) {
			if (getline(file, temp, ',') && temp == username) {
				file.close();
				return true;
			}
			else {
				getline(file, temp);
			}
		}
		file.close();
		return false;
	}

	string getfileName() { return usersFileName; }
};