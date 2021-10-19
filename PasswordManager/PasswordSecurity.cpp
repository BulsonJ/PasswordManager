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
	vector<vector<int>> words;
	vector<int> ascii_values;
	decrypt_password_recursive_single(password, 0, words, ascii_values);
	return words;
}

vector<vector<vector<int>>> PasswordSecurity::decrypt_string(string password) {
	vector<vector<vector<int>>> possible_strings;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive_string(password, 0, possible_strings, ascii_values);

	// go through possible words here

	// for each possible string
	vector<string> strings;
	for (auto it = possible_strings.begin(); it < possible_strings.end(); it++) {
		if (it - possible_strings.begin() == 0) continue;
		string current_string;
		vector<int> last_word_pos;

		// for each possible character space
		for (auto string_it = (*it).begin(); string_it < (*it).end(); string_it++) {
			if ((*string_it).size() == 1) {
				current_string += (*string_it)[0];
				if ((*string_it)[0] == 32) {
					last_word_pos.emplace_back(string_it - (*it).begin());
				}
			}
			else {
				current_string += "?";
			}
			// for each possible character in that space
			for (auto char_it = (*string_it).begin(); char_it < (*string_it).end(); char_it++) {

			}

		}
		strings.emplace_back(current_string);
	}


	// -------------------------------
	for (auto it = strings.begin(); it < strings.end(); it++) {
		cout << *it << endl;
	}
	return possible_strings;
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

void PasswordSecurity::decrypt_password_recursive_single(string password, int offset, vector<vector<int>>& possible_words, vector<int>& current_word_possibility) {
	
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

		int ascii_value = get_ascii_from_collatz(std::stoi(current_numbers), offset);
		if (ascii_value != -1){
			current_word_possibility.emplace_back(ascii_value);
			decrypt_password_recursive_single(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_words, current_word_possibility);
			current_word_possibility.pop_back();
		}
		count++;
	}	
}

void PasswordSecurity::decrypt_password_recursive_string(string password, int offset, vector<vector<vector<int>>>& possible_words, vector<vector<int>>& current_word_possibility) {

	if (password.size() == 0) {
		possible_words.emplace_back(current_word_possibility);
		return;
	}

	string current_numbers;
	int count = 0;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0) return;

		vector<int> ascii_values_matching = get_ascii_string_list_from_collatz(std::stoi(current_numbers), offset);
		if (!(ascii_values_matching.size() == 0)) {
			current_word_possibility.emplace_back(ascii_values_matching);
			decrypt_password_recursive_string(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_words, current_word_possibility);
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

vector<int> PasswordSecurity::get_ascii_string_list_from_collatz(int collatzNum, int offset) {
	vector<int> ascii_values;
	for (int i = 32; i < 123; i++) {
		if (i > 32 && i < 43){
			continue;
		}
		if (collatzNum == collatz(i + offset)) {
			ascii_values.emplace_back(i);
		}
	}
	return ascii_values;
}