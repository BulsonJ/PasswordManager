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
	vector<vector<int>> password;
	password = PasswordSecurity::decrypt_password_r("1279513461033941361595393615108262841159588119212810339239010613281595261032110821281032641152010826284111634287202815121132028239011921281085223411163415201081333413623282315108212873315108131081328281082190441112128");

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