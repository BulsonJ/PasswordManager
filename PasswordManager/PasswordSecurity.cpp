#include "PasswordSecurity.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

string PasswordSecurity::encrypt_vector_int(const vector<int> input) {
	string encrypted = "";
	int previousNumber = 0;

	for (auto it = input.begin(); it < input.end(); ++it) {
		int number_of_turns = 0;
		number_of_turns = collatz(*it + previousNumber);
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


vector<int> PasswordSecurity::decrypt_password_first_result(string password) {
	vector<int> words;
	vector<int> ascii_values;
	decrypt_password_recursive_single(password, 0, words, ascii_values);
	return words;
}

template <typename T>
void combinations(vector<vector<T>>& vector_of_vectors, vector<T>& current_combo, vector<vector<T>>& all_combinations) {
	if (vector_of_vectors.size() == 0) {
		all_combinations.emplace_back(current_combo);
		return;
	}

	vector<vector<T>> rest_of_vectors(vector_of_vectors.begin() + 1, vector_of_vectors.end());
	vector<T> current_char = vector_of_vectors[0];
	for (auto it = current_char.begin(); it < current_char.end(); it++) {
		current_combo.emplace_back(*it);
		combinations<T>(rest_of_vectors, current_combo, all_combinations);
		current_combo.pop_back();
	}

}

vector<string> PasswordSecurity::decrypt_string(string password) {
	vector<vector<vector<int>>> possible_strings;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive_string(password, 0, possible_strings, ascii_values);

	// load in dictionary

	ifstream english_dictionary;
	english_dictionary.open("words.txt");

	string myText;
	vector<string> english_words;
	while(getline(english_dictionary, myText)) {
		english_words.emplace_back(myText);
	}
	vector<vector<vector<string>>> strings;
	for (auto it = possible_strings.begin(); it < possible_strings.end(); it++) {

		int last_word_pos = 0;
		vector<vector<string>> final_sentence;

		for (auto string_it = (*it).begin(); string_it < (*it).end(); string_it++) {
			if (((*string_it)[0] == 32 && (*string_it).size() > 0) || string_it + 1 == (*it).end()) {

				auto word_begin = (*it).begin() + last_word_pos;
				auto word_end = (*it).begin() + (string_it - (*it).begin());
				if (string_it + 1 == (*it).end()) {
					word_end = (*it).end();
				}

				vector<vector<int>> word(word_begin, word_end);
				last_word_pos = string_it - (*it).begin() + 1;

				vector<int> current_word;
				vector<vector<int>> final_words;
				combinations<int>(word, current_word, final_words);

				vector<string> possible_words;
				for (auto word_it = final_words.begin(); word_it < final_words.end(); word_it++) {
					string word;
					for (auto char_it = (*word_it).begin(); char_it < (*word_it).end(); char_it++) {
						word += (*char_it);
					}
					string lowercase_string = word;
					std::transform(lowercase_string.begin(), lowercase_string.end(), lowercase_string.begin(), ::tolower);

					if (std::find(english_words.begin(), english_words.end(), lowercase_string) != english_words.end()) {
						possible_words.emplace_back(word);
					}
				}
				final_sentence.emplace_back(possible_words);
			}
		}

		vector<string> current_word;
		vector<vector<string>> final_words;
		combinations<string>(final_sentence, current_word, final_words);

		strings.emplace_back(final_words);
	}

	vector<string> passwords;
	for (auto it = strings.begin(); it < strings.end(); it++) {
		for (auto pass_it = (*it).begin(); pass_it < (*it).end(); pass_it++) {
			string password;
			for (auto word_it = (*pass_it).begin(); word_it < (*pass_it).end(); word_it++) {
				password += *word_it;
				password += " ";
			}
			passwords.emplace_back(password);
		}
	}

	return passwords;
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

void PasswordSecurity::decrypt_password_recursive_single(string password, int offset, vector<int>& possible_password, vector<int>& current_password_possibility) {
	
	if (possible_password.size() > 0) {
		return;
	}

	if (password.size() == 0) {
		possible_password = current_password_possibility;
		return;
	}

	string current_numbers;
	int count = 0;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0) return;

		int ascii_value = get_ascii_from_collatz(std::stoi(current_numbers), offset);
		if (ascii_value != -1){
			current_password_possibility.emplace_back(ascii_value);
			decrypt_password_recursive_single(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_password, current_password_possibility);
			current_password_possibility.pop_back();
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
		if (i > 32 && i < 63){
			continue;
		}
		if (collatzNum == collatz(i + offset)) {
			ascii_values.emplace_back(i);
		}
	}
	return ascii_values;
}