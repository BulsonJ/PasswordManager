#include "PasswordTesting.h"
#include "Encrypter.h"
#include <fstream>

void PasswordTesting::GeneratePasswords(const string file_name) {
	ofstream data_file;

	data_file.open(file_name.c_str(), ios::trunc);

	if (data_file.fail())
		throw invalid_argument("no file exists " + file_name);

	const int random_letter_amount = 10;
	char random_letters[random_letter_amount];
	for (int i = 0; i < random_letter_amount; ++i) {
		random_letters[i] = char(rand() % 25 + 97);
	}

	string* passwords = new string[20000];
	int length = 0;
	for (int i = 0; i < 10000; i++) {
		if (i % 100 == 0) length++;
		string password = "";

		for (int x = 0; x < length; x++) {
			password += random_letters[rand() % 10];
		}

		passwords[i] = Encrypter::encrypt_string(password);
		data_file << passwords[i] << endl;
	}
	
	length = 100;
	for (int i = 10000; i < 20000; i++) {
		if (i % 100 == 0) length++;
		string password = "";

		for (int x = 0; x < length; x++) {
			password += char(rand() % 93 + 33);
		}
		passwords[i] = Encrypter::encrypt_string(password);
		data_file << passwords[i - 1] << endl;
	}

	data_file.close();

	delete[] passwords;
	passwords = nullptr;

}