#include "PasswordSecurity.h"
#include <iostream>
#include <vector>

int PasswordSecurity::collatz(int input) {
	return collatz(input, 0);
}

int PasswordSecurity::collatz(int input, int count) {
	if (input == 1) return count;
	input % 2 == 0 ? collatz(input / 2, count + 1) : collatz((input * 3) + 1, count + 1);
}

string PasswordSecurity::encrypt_string(const string input) {
	string encrypted = "";
	int previousNumber = 0;

	for (int i = 0; i < input.size(); ++i) {
		int number_of_turns = 0;
		number_of_turns = collatz(int(input[i]) + previousNumber);
		encrypted += to_string(number_of_turns);
		previousNumber = number_of_turns;
	}

	return encrypted;
}

string PasswordSecurity::decrypt_password(const string s) {
	string current_numbers = "";

	// if possible values = 0, go to next number and start again
	vector<vector<int>> possible_full_word_ascii_values;
	int offset = 0;
	for (int i = 0; i < s.length(); ++i) {
		current_numbers += s[i];
		vector<int> possible_values;

		vector<pair<int, int>> collatz_values = get_ascii_collatz_values(offset);
		// For each value in the collatz, if matches current numbers then add to possible values
		for (auto it = collatz_values.begin(); it != collatz_values.end(); it++) {
			if (std::stoi(current_numbers) == it->second) {
				possible_values.emplace_back(it->first);
			}
		}
		
		// If there are possible values, emplace the list back
		if (possible_values.size() > 0) {
			offset = std::stoi(current_numbers);
			possible_full_word_ascii_values.emplace_back(possible_values);
			current_numbers = "";
		}
	}

	string decrypted_password;
	for (auto it = possible_full_word_ascii_values.begin(); it != possible_full_word_ascii_values.end(); it++) {
		decrypted_password += char((*it)[0]);
	}

	return decrypted_password;
}

vector<int>* PasswordSecurity::decrypt_password_r(string password) {

	vector<int>* ascii_values = new vector<int>;
	decrypt_password_recursive(password, 0, ascii_values);
	return ascii_values;
}

void PasswordSecurity::decrypt_password_recursive(string password,int offset, vector<int>* ascii_values) {
	/*
		20953985

		if 2 is ascii, decrypt 0953985 with offset of 2 - true
		if 0 is ascii, decrypt 953985 with offset of 0 - false

		if 20 is ascii, decrypt 953985 with offset of 20 - true
		if 9 is ascii, 53985 with offset of 0 - false
	*/

	if (password.size() == 0) {
		return;
	}

	bool collatzFound = false;
	string current_numbers;

	for (int i = 0; i < password.size(); i++) {
		current_numbers += password[i];

		int current_number = std::stoi(current_numbers);
		vector<int> possible_values = get_ascii_from_collatz(std::stoi(current_numbers), offset);
		if (possible_values.size() > 0) {
			int ascii_value = possible_values[0];
			(*ascii_values).push_back(ascii_value);
			string rest_of_password = password.substr(i + 1, password.size() - 1);
			collatzFound = true;

			decrypt_password_recursive(rest_of_password, current_number, ascii_values);
		}
	}

	// if combination is false, delete it
	if (!collatzFound) {
		(*ascii_values).clear();
	}

	
}

void PasswordSecurity::print_ascii_collatz_values(int offset) {
	for (int i = 1; i < 256; i++) {
		cout << "char value: " << i <<  " + " << offset << " :" << collatz(i + offset) << endl;
	}
}

vector<pair<int, int>> PasswordSecurity::get_ascii_collatz_values(int offset) {
	vector<pair<int, int>> values;
	for (int i = 1; i < 256; i++) {
		values.emplace_back(make_pair(i, collatz(i + offset)));
	}
	return values;
}

vector<int> PasswordSecurity::get_ascii_from_collatz(int collatz, int offset) {
	vector<pair<int, int>> collatz_values = get_ascii_collatz_values(offset);
	vector<int> possible_values;
	// For each value in the collatz, if matches current numbers then return ascii value
	for (auto it = collatz_values.begin(); it != collatz_values.end(); it++) {
		if (collatz == it->second) {
			possible_values.push_back(it->first);
		}
	}
	return possible_values;
}