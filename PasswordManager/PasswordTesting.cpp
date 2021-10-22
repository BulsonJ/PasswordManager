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

	string** passwords = nullptr;
	try {
		passwords = store.read_from_file();
	}
	catch (const std::invalid_argument& e) {
		cout << e.what() << endl;
		return;
	}

	Timer test;
	PasswordSecurity cracker;
	test.start();
	cracker.generate_collatz_ascii_values();
	test.stop();
	cout << "Generated possible collatz values, took " << test.elapsedTime() << "ms." << endl;

	/*cracker.generate_collatz_multiple_ascii_values();
	vector<vector<vector<int>>> passwordstest = cracker.decrypt_password("20953985");
	vector<int> testtt;
	for (auto it = passwordstest[0].begin(); it < passwordstest[0].end(); it++) {
		testtt.emplace_back((*it)[0]);
	}
	string crackedPassword = PasswordSecurity::encrypt_vector_int(testtt);*/

	int success_amounts[200] = {0};
	double average_amounts[200] = {0.0};
	int set_counter = 0;

	bool success = false;
	cout << "-----------------------------------------------------------" << endl;
	for (int i = 0; i < 20000; ++i) {
		test.start();
		vector<int> password = cracker.decrypt_password_first_result(*passwords[i]);
		test.stop();

		string crackedPassword = PasswordSecurity::encrypt_vector_int(password);
		if (*passwords[i] == crackedPassword) {
			average_amounts[set_counter] += test.elapsedTime();
			success_amounts[set_counter] += 1;
		}
		else {
			continue;
		}
		
		if ((i + 1) % 100 == 0) {
			cout << i + 1 - 100 << "to" << i + 1 << " percent cracked(" << success_amounts[set_counter] << "%), avg time: " << average_amounts[set_counter] / 100 << "ms" << endl;
			set_counter++;
		}
		
		if (i + 1 == 10000 || i + 1 == 20000) {
			int success = 0;
			double average = 0;
			if (i + 1 == 10000) {
				for (int j = 0; j < 100; j++) {
					average += average_amounts[j];
					success += success_amounts[j];
				}
			}
			else {
				for (int j = 100; j < 200; j++) {
					average += average_amounts[j];
					success += success_amounts[j];
				}
			}
			average = average / 10000;
			success = success / 100;

			cout << "-----------------------------------------------------------" << endl;
			cout << i + 1 - 10000 << "to" << i + 1 << " percent cracked(" << success << "%), avg time: " << average << "ms" << endl;
			cout << "-----------------------------------------------------------" << endl;
			cout << endl;
		}

	}

}