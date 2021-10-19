#include "PasswordStorage.h"

PasswordStorage::PasswordStorage(const string file_name) : FileStorage(file_name) {
	data_file.open(file_name.c_str(), ios::app);
}

PasswordStorage::~PasswordStorage() {
	data_file.close();
}

void PasswordStorage::save_to_file(const string password) throw (invalid_argument) {
	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << password << endl;
}