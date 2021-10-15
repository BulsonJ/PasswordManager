#include "PasswordStorage.h"

void PasswordStorage::save_to_file(const string password) throw (invalid_argument) {
	ofstream data_file;

	data_file.open(file_name.c_str(), ios::app);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	data_file << password << endl;

	data_file.close();
}