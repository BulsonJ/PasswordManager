#include <iostream>
#include <fstream>
#include <exception>
#include <locale>
#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(string file_name) {
	this->file_name = file_name;

	ifstream passwordFile;
	passwordFile.open(file_name.c_str());

	string myText;
	while (getline(passwordFile, myText)) {
		string username = myText.substr(0, myText.find(" "));
		string password = myText.substr(myText.find(" ") + 1, myText.find("\n"));
		
		accounts.emplace(username, password);
	}

	passwordFile.close();
}

PasswordStorage::~PasswordStorage() {

}

bool PasswordStorage::check_duplicate_username(const string name) const {
	if (accounts.count(name)) {
		return true;
	}
	return false;
}

string PasswordStorage::get_password(const string username) {
	auto it = accounts.find(username);
	return it->second;
}

void PasswordStorage::save_to_file(const string username, const string password) throw (invalid_argument){
	if (check_duplicate_username(username)) {
		throw invalid_argument("username already exists: " + username);
	}

	ofstream data_file;

	data_file.open(file_name.c_str(), ios::app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << username << " " << password << endl;
	accounts.emplace(username, password);


	data_file.close();
}