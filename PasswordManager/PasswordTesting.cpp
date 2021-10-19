#include "PasswordTesting.h"
#include "PasswordSecurity.h"
#include "PasswordStorage.h"
#include <fstream>

void PasswordTesting::GeneratePasswords(const string file_name) throw (invalid_argument){
	PasswordStorage store(file_name);

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

		store.save_to_file(PasswordSecurity::encrypt_string(password));
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
		store.save_to_file(PasswordSecurity::encrypt_string(password));
	}
}