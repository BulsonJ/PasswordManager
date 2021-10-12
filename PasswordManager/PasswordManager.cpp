#include <iostream>
#include "PasswordStorage.h"
#include "Encrypter.h"
using namespace std;

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

	PasswordStorage storage("password.txt");
	Account newAccount;
	newAccount.username = username;
	newAccount.password = Encrypter::encrypt_string(password);
	try {
		storage.save_to_file(newAccount);
	}
	catch (const std::invalid_argument& e) {
		cout << "Username already exists" << endl;
	}
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
		case(2):
			break;
		case(3):
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