#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(const string file_name) : FileStorage(file_name) {
	
}

PasswordStorage::~PasswordStorage() {
	
}

void PasswordStorage::save_to_file(const string password) throw (invalid_argument) {
	data_file.open(file_name.c_str(), ios::out | ios::trunc);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << password << endl;

	data_file.close();
}

void PasswordStorage::save_passwords_to_file(const string* passwords) throw (invalid_argument) {
	data_file.open(file_name.c_str(), ios::out | ios::trunc);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	for (int i = 0; i < 20000; ++i) {
		data_file << passwords[i] << endl;
	}
	
	data_file.close();
}


string** PasswordStorage::read_from_file() throw (invalid_argument){
	data_file.open(file_name.c_str(), ios::in | ios::app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	string password;

	string** passwords = new string * [20000];
	int count = 0;
	while (std::getline(data_file, password)) {
		passwords[count] = new string(password);
		count++;
	}

	data_file.close();
	return passwords;
}