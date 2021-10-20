#include <iostream>
#include "PasswordStorage.h"
#include "AccountStorage.h"
#include "PasswordSecurity.h"
#include "PasswordTesting.h"
#include "Timer.h"
using namespace std;

AccountStorage storage("password.txt");

int menu_input() {
	cout << "Select an option:" << endl;
	cout << "1. Create username/password" << endl;
	cout << "2. Check username and password" << endl;
	cout << "3. Generate password strength analysis file" << endl;
	cout << "4. Analyse password strength analysis file" << endl;
	cout << "5. Exit" << endl;

	int selected_option;
	cin >> selected_option;
	return selected_option;
}

void option_create_password() {
	string username;
	string password;
	cout << "Please enter a username" << endl;
	cin >> username;
	cout << "Please enter a password" << endl;
	cin >> password;

	try {
		storage.save_to_file(username, PasswordSecurity::encrypt_string(password));
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
	cout << "Please enter a username:" << endl;
	cin >> username;

	while (triesRemaining > 0 && !foundPassword) {
		cout << "Please enter a password(" << triesRemaining << " tries remaining):" << endl;
		cin >> password;
		triesRemaining--;

		if (PasswordSecurity::encrypt_string(password) == storage.get_password(username)) {
			cout << "Success!" << endl;
			foundPassword = true;
		}
		else {
			cout << "Failure!" << endl;
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
	/*vector<vector<vector<int>>> passwords;
	passwords = PasswordSecurity::decrypt_password("20953985");*/

	vector<string> ten_marks;
	ten_marks = PasswordSecurity::decrypt_string("27322810313331033910211452912207344136146925461033281533271031012815108114101");

	for (auto it = ten_marks.begin(); it < ten_marks.end(); it++) {
		cout << *it << endl;
	}

	/*vector<vector<int>> password_single;
	Timer test;
	test.start();
	password_single = PasswordSecurity::decrypt_password_first_result("20202033901320152846239539362810826116101261032110813332346234615334141116348544234611611411411410111911412713113211512121114132828116348588106884410113214123951369111342828116348544982610821901067049111101261083936231520153315");
	test.stop();
	cout << test.elapsedTime() << "ms";*/

	//PasswordTesting::TestPasswords("passwordtest.txt");
	/*vector<int> passwords;
	passwords = PasswordSecurity::decrypt_password_first_result("11834231515108701828234115");
	string crackedPassword = PasswordSecurity::encrypt_vector_int(passwords);*/

	return;
}

int main(){
	bool exit = false;

	while (!exit) {
		int input = menu_input();
		switch (input)
		{
		default:
			break;
		case(1):
			option_create_password();
			break;
		case(2):
			option_check_password();
			break;
		case(3):
			option_generate_password();
			break;
		case(4):
			option_decrypt_password();
			break;
		case(5):
			exit = true;
		}
		cout << endl;
	}

	return 0;
}