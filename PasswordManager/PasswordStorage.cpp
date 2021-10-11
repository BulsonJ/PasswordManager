#include <iostream>
#include <fstream>
#include <locale>
#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(string file_name) {
	this->file_name = file_name;
}

PasswordStorage::~PasswordStorage() {

}

bool PasswordStorage::check_duplicate_username(string name) const {
	string myText;

	ifstream passwordFile("filename.txt");
	
	while (getline(passwordFile, myText)) {
		string username = myText.substr(0, myText.find(" "));

		if (username == name) {
			passwordFile.close();
			return true;
		}
	}

	passwordFile.close();
	return false;
}

void PasswordStorage::save_to_file(const Account& s) const throw (invalid_argument) {
	check_duplicate_username(s.username) ? NULL : throw invalid_argument("username already exists" + s.username);

	ofstream data_file;

	data_file.open(file_name.c_str(), ios::app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << s.username << " " << s.password << endl;

	data_file.close();
}