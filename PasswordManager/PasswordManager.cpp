#include <iostream>
#include "PasswordStorage.h"
#include "Encrypter.h"
#include "PasswordTesting.h"
#include "Timer.h"
using namespace std;

PasswordStorage storage("password.txt");

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
		storage.save_to_file(username, Encrypter::encrypt_string(password));
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

		if (Encrypter::encrypt_string(password) == storage.get_password(username)) {
			cout << "Success!" << endl;
			foundPassword = true;
		}
		else {
			cout << "Failure!" << endl;
		}
	}

}


int main(){
	bool exit = false;

	Timer test;
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
			try {
				test.start();
				PasswordTesting::GeneratePasswords("passwordtest.txt");
				test.stop();
			}
			catch (const std::invalid_argument& e) {
				cout << e.what() << endl;
			}
			cout << "Passwords saved to passwordtest.txt(" << test.elapsedTime() / 1000.0 << " s taken)" << endl;
			break;
		case(4):
			break;
		case(5):
			exit = true;
		}
		cout << endl;
	}

	return 0;
}