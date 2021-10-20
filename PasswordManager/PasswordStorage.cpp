#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(const string file_name) : FileStorage(file_name) {
	data_file.open(file_name.c_str(), ios::in | ios::out | ios::app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);
}

PasswordStorage::~PasswordStorage() {
	data_file.close();
}

void PasswordStorage::save_to_file(const string password) throw (invalid_argument) {
	data_file << password << endl;
}

string** PasswordStorage::read_from_file() {
	string password;

	string** passwords = new string * [20000];
	int count = 0;
	while (std::getline(data_file, password)) {
		passwords[count] = new string(password);
		count++;
	}

	return passwords;
}