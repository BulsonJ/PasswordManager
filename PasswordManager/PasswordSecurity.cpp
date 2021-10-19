#include "PasswordSecurity.h"
#include <iostream>
#include <vector>
#include "Timer.h"

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

vector<vector<vector<int>>> PasswordSecurity::decrypt_password(string password) {
	vector<vector<vector<int>>> words;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive(password, 0, words, ascii_values);
	return words;
}


vector<vector<int>> PasswordSecurity::decrypt_password_first_result(string password) {
	vector<vector<vector<int>>> words;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive_single(password, 0, words, ascii_values);
	return words[0];
}

void PasswordSecurity::decrypt_password_recursive(string password, int offset, vector<vector<vector<int>>>& possible_words, vector<vector<int>>& current_word_possibility) {
	
	if (password.size() == 0) {
		possible_words.emplace_back(current_word_possibility);
		return;
	}

	string current_numbers;
	int count = 0;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0) return;

		vector<int> ascii_values_matching = get_ascii_list_from_collatz(std::stoi(current_numbers), offset);
		if (!(ascii_values_matching.size() == 0)) {
			current_word_possibility.emplace_back(ascii_values_matching);
			decrypt_password_recursive(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_words, current_word_possibility);
			current_word_possibility.pop_back();
		}
		count++;
	}	
}

void PasswordSecurity::decrypt_password_recursive_single(string password, int offset, vector<vector<vector<int>>>& possible_words, vector<vector<int>>& current_word_possibility) {

	if (possible_words.size() > 0) {
		return;
	}

	if (password.size() == 0) {
		possible_words.emplace_back(current_word_possibility);
		return;
	}

	string current_numbers;
	int count = 0;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0) return;

		vector<int> ascii_values_matching = get_ascii_list_from_collatz(std::stoi(current_numbers), offset);
		if (!(ascii_values_matching.size() == 0)) {
			current_word_possibility.emplace_back(ascii_values_matching);
			decrypt_password_recursive(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_words, current_word_possibility);
			current_word_possibility.pop_back();
		}
		count++;
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

int PasswordSecurity::get_ascii_from_collatz(int collatzNum, int offset) {
	for (int i = 1; i < 256; i++) {
		if (collatzNum == PasswordSecurity::collatz(i + offset)) {
			return i;
		}
	}
	return -1;
}

vector<int> PasswordSecurity::get_ascii_list_from_collatz(int collatzNum, int offset) {
	vector<int> ascii_values;
	for (int i = 1; i < 256; i++) {
		if (collatzNum == collatz(i + offset)) {
			ascii_values.emplace_back(i);
		}
	}
	return ascii_values;
}