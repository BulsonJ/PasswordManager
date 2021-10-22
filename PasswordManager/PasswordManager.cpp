#include <iostream>
#include "PasswordStorage.h"
#include "AccountStorage.h"
#include "PasswordSecurity.h"
#include "PasswordTesting.h"
#include "Timer.h"
using namespace std;

AccountStorage* storage = nullptr;

int menu_input() {
	cout << "Select an option:" << endl;
	cout << "1. Create username/password" << endl;
	cout << "2. Check username and password" << endl;
	cout << "3. Generate password strength analysis file" << endl;
	cout << "4. Analyse password strength analysis file" << endl;
	cout << "5. Decrypt sentence" << endl;
	cout << "6. Exit" << endl;

	string selected_option;
	getline(cin, selected_option);

	if (selected_option.find(' ') != std::string::npos)
		return 0;

	return stoi(selected_option);
}

bool check_username(const string username) {
	if (username.size() == 0)
		return false;
	if (username.find(' ') != std::string::npos)
		return false;

	return true;
}

string get_username() {
	string username;
	cout << "Please enter a username" << endl;
	getline(cin, username);
	bool valid_username = check_username(username);

	while (!valid_username) {
		cout << "Please enter a valid username" << endl;
		getline(cin, username);
		valid_username = check_username(username);
	}
	return username;
}

string get_password() {
	string password;
	cout << "Please enter a password" << endl;
	getline(cin, password);

	while (password.size() == 0) {
		cout << "Please enter a valid password" << endl;
		getline(cin, password);
	}
	return password;
}

void option_create_password() {
	string username = get_username();
	string password = get_password();

	try {
		storage->save_to_file(username, PasswordSecurity::encrypt_string(password));
		cout << "Account created successfully!" << endl;
	}
	catch (const std::invalid_argument& e) {
		cout << e.what() << endl;
	}
}

void option_check_password() {
	int triesRemaining = 3;
	bool foundPassword = false;
	string username;
	string password;
	
	username = get_username();

	while (triesRemaining > 0 && !foundPassword) {
		password = get_password();
		triesRemaining--;

		if (PasswordSecurity::encrypt_string(password) == storage->get_password(username)) {
			cout << "Success!" << endl;
			foundPassword = true;
		}
		else {
			cout << "Failure! ("<< triesRemaining << " tries remaining)" << endl;
		}
	}
}

void option_generate_password() {
	Timer test;
	try {
		test.start();
		PasswordTesting::GeneratePasswords("passwordtest.txt");
		test.stop();
	}
	catch (const std::invalid_argument& e) {
		cout << e.what() << endl;
	}
	cout << "Passwords saved to passwordtest.txt(" << test.elapsedTime() / 1000.0 << " s taken)" << endl;
}

void option_decrypt_password() {
	PasswordTesting::TestPasswords("passwordtest.txt");
}

void option_decrypt_sentence() {
	vector<string> sentence;
	PasswordSecurity test;
	test.generate_collatz_multiple_sentence_ascii_values();
	try {
		sentence = test.decrypt_string("27322810313331033910211452912207344136146925461033281533271031012815108114101", "words.txt");
	}
	catch (const std::invalid_argument& e) {
		cout << e.what() << endl;
	}

	auto func = [](string print) { cout << print << endl; };
	for (auto it = sentence.begin(); it < sentence.end(); it++) {
		func(*it);
	}
}

int main(){
	bool exit = false;

	storage = new AccountStorage("password.txt");


	while (!exit) {

		void (*menu_option)();
		menu_option = nullptr;

		int input = menu_input();
		switch (input)
		{
		default:
			input = menu_input();
			break;
		case(1):
			menu_option = &option_create_password;
			break;
		case(2):
			menu_option = &option_check_password;
			break;
		case(3):
			menu_option = &option_generate_password;
			break;
		case(4):
			menu_option = &option_decrypt_password;
			break;
		case(5):
			menu_option = &option_decrypt_sentence;
			break;
		case(6):
			exit = true;
			break;
		}

		if (input == 0)
			continue;

		if (exit)
			break;

		menu_option();

		cout << endl;
	}

	delete storage;
	storage = nullptr;

	return 0;
}