#pragma once
#include <string>
#include <fstream>
using namespace std;

class Registration {
	string usersFileName;
public:
	Registration() {
		usersFileName = "./users.txt";
	}
	bool registerUser(string username, string password, string role, string name, string address, string email, string dob) {
		ofstream file;
		file.open(usersFileName, ios::out|ios::app);
		if (!file.is_open()) {
			return false;
		}
		file << '\n' << username << ',' << password << ',' << role << ',' << name << ',' << address << ',' << email << ',' << dob;
		file.close();
		return true;
	}
};