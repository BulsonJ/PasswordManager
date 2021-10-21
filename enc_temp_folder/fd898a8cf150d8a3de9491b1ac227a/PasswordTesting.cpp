#include "PasswordTesting.h"
#include "PasswordSecurity.h"
#include "PasswordStorage.h"
#include "Timer.h"
#include <fstream>
#include <iostream>

void PasswordTesting::GeneratePasswords(const string file_name) throw (invalid_argument){
	PasswordStorage store(file_name);

	string* passwords = new string[20000];

	const int random_letter_amount = 10;
	int random_letters[random_letter_amount];
	for (int i = 0; i < random_letter_amount; ++i) {
		random_letters[i] = (rand() % 25) + 97;
	}

	int length = 0;
	for (int i = 0; i < 10000; i++) {
		if (i % 100 == 0) length++;
		vector<int> password;

		for (int x = 0; x < length; x++) {
			password.emplace_back(random_letters[rand() % 10]);
		}

		passwords[i] = PasswordSecurity::encrypt_vector_int(password);
	}
	
	length = 0;
	for (int i = 10000; i < 20000; i++) {
		if (i % 100 == 0) length++;
		vector<int> password;

		for (int x = 0; x < length; x++) {
			int next_character = (rand() % 255) + 1;
			while (std::find(password.begin(), password.end(), next_character) != password.end()) {
				next_character = (rand() % 255) + 1;
			}
			password.emplace_back(next_character);
		}
		passwords[i] = PasswordSecurity::encrypt_vector_int(password);
	}

	store.save_passwords_to_file(passwords);
}

void PasswordTesting::TestPasswords(const string file_name) {
	PasswordStorage store(file_name);

	string** passwords = store.read_from_file();

	PasswordSecurity cracker;
	cracker.generate_collatz_ascii_values();
	cracker.generate_collatz_multiple_ascii_values();

	Timer test;
	float average = 0.0;
	int successAmount = 0;
	bool success = false;
	for (int i = 0; i < 20000; ++i) {
		test.start();
		vector<int> password = cracker.decrypt_password_first_result(*passwords[i]);
		test.stop();

		string crackedPassword = PasswordSecurity::encrypt_vector_int(password);
		if (*passwords[i] == crackedPassword) {
			average += test.elapsedTime();
			successAmount += 1;
		}
		else {
			continue;
		}
		
		if ((i + 1) % 100 == 0) {
			cout << i + 1 - 100 << "to" << i + 1 << " cracked" << endl;
		}
		
		if ((i + 1) % 10000 == 0) {
			cout << "-----------------------------------------------------------" << endl;
			cout << i + 1 - 10000 << "to" << i + 1 << " percent cracked(" << successAmount/10000 << "%), avg time: " << average / 10000 << "ms" << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
			successAmount = 0;
			average = 0;
		}

	}

}