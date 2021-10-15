#include "PasswordTesting.h"
#include "PasswordSecurity.h"
#include <fstream>

void PasswordTesting::GeneratePasswords(const string file_name) throw (invalid_argument){
	ofstream data_file;

	data_file.open(file_name.c_str(), ios::trunc);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	const int random_letter_amount = 10;
	char random_letters[random_letter_amount];
	for (int i = 0; i < random_letter_amount; ++i) {
		random_letters[i] = char(rand() % 25 + 97);
	}

	int length = 0;
	for (int i = 0; i < 10000; i++) {
		if (i % 100 == 0) length++;
		string password = "";

		for (int x = 0; x < length; x++) {
			password += random_letters[rand() % 10];
		}

		data_file << PasswordSecurity::encrypt_string(password) << endl;
	}
	
	length = 0;
	for (int i = 10000; i < 20000; i++) {
		if (i % 100 == 0) length++;
		string password = "";

		for (int x = 0; x < length; x++) {
			char next_character = char(rand() % 93 + 33);
			while (password.find(next_character) != string::npos) {
				password += char(rand() % 93 + 33);
			}
		}
		data_file << PasswordSecurity::encrypt_string(password) << endl;
	}

	data_file.close();
}