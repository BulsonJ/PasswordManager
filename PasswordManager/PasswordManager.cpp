#include <iostream>
#include "PasswordStorage.h"
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


int collatz(int input, int count) {
	if (input == 1) {
		return count;
	}
	else {
		count++;
		input % 2 == 0 ? collatz(input / 2, count) : collatz((input * 3) + 1, count);
	}
}

string encrypt_string(string input) {
	string encrypted = "";
	int previousNumber = 0;

	for (int i = 0; i < input.size(); ++i) {
		int number_of_turns = 0;
		number_of_turns = collatz(int(input[i]) + previousNumber, 0);
		encrypted += to_string(number_of_turns);
		previousNumber = number_of_turns;
	}

	return encrypted;
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
	newAccount.password = password;
	storage.save_to_file(newAccount);
}

int main(){
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
		return 0;
	}

	return 0;
}