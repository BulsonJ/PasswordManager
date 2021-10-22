#include "PasswordSecurity.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include "Timer.h"

PasswordSecurity::PasswordSecurity() {

}

PasswordSecurity::~PasswordSecurity() {

}

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

vector<vector<vector<int>>> PasswordSecurity::decrypt_password(const string password) {
	vector<vector<vector<int>>> words;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive(password, 0, words, ascii_values);
	return words;
}

vector<int> PasswordSecurity::decrypt_password_first_result(const string password) {
	vector<int> words;
	vector<int> ascii_values;
	decrypt_password_recursive_single(password, 0, words, ascii_values);
	return words;
}

template <typename T>
void ordered_combinations(vector<vector<T>>& vector_of_vectors, vector<T>& current_combo, vector<vector<T>>& all_combinations) {
	if (vector_of_vectors.size() == 0) {
		all_combinations.emplace_back(current_combo);
		return;
	}

	vector<vector<T>> rest_of_vectors(vector_of_vectors.begin() + 1, vector_of_vectors.end());
	vector<T> current_char = vector_of_vectors[0];
	for (auto it = current_char.begin(); it < current_char.end(); it++) {
		current_combo.emplace_back(*it);
		ordered_combinations<T>(rest_of_vectors, current_combo, all_combinations);
		current_combo.pop_back();
	}
}

vector<string> PasswordSecurity::password_combination_to_strings(vector<vector<vector<string>>> possible_passwords_strings){
	vector<string> passwords;
	for (auto it = possible_passwords_strings.begin(); it < possible_passwords_strings.end(); it++) {
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

vector<vector<vector<int>>> PasswordSecurity::split_sentence_into_words(const vector<vector<int>> sentence) {
	int last_word_pos = 0;
	vector<vector<vector<int>>> words;
	for (auto char_it = sentence.begin(); char_it < sentence.end(); char_it++) {
		if (((*char_it)[0] == 32 && (*char_it).size() > 0) || char_it + 1 == sentence.end()) {

			auto word_begin = sentence.begin() + last_word_pos;
			auto word_end = sentence.begin() + (char_it - sentence.begin());
			if (char_it + 1 == sentence.end()) {
				word_end = sentence.end();
			}

			vector<vector<int>> word(word_begin, word_end);
			last_word_pos = char_it - sentence.begin() + 1;
			words.emplace_back(word);
		}
	}
	return words;
}

string PasswordSecurity::convert_vector_to_word(vector<int> word_vector) {
	string word = "";
	for (auto char_it = word_vector.begin(); char_it < word_vector.end(); char_it++) {
		word += (*char_it);
	}
	return word;
}


vector<string> PasswordSecurity::decrypt_string(const string password, const string file_name) throw (invalid_argument) {
	vector<vector<vector<int>>> possible_passwords;
	vector<vector<int>> ascii_values;
	decrypt_password_recursive_string(password, 0, possible_passwords, ascii_values);

	ifstream english_dictionary;
	english_dictionary.open(file_name.c_str());

	if (english_dictionary.fail()) 
		throw invalid_argument("no dictionary file available" + file_name);

	string myText;
	vector<string> english_words;
	while(getline(english_dictionary, myText)) {
		english_words.emplace_back(myText);
	}

	vector<vector<vector<string>>> possible_passwords_strings;
	for (auto password_it = possible_passwords.begin(); password_it < possible_passwords.end(); password_it++) {

		vector<vector<vector<int>>> words = split_sentence_into_words(*password_it);

		vector<vector<string>> possible_sentences;
		for (auto word_index_it = words.begin(); word_index_it < words.end(); word_index_it++) {
			vector<int> current_word_combination;
			vector<vector<int>> all_combinations_of_words;
			ordered_combinations<int>(*word_index_it, current_word_combination, all_combinations_of_words);

			vector<string> possible_passwords;
			for (auto word_it = all_combinations_of_words.begin(); word_it < all_combinations_of_words.end(); word_it++) {

				string word = convert_vector_to_word(*word_it);
				string lowercase_string = word;
				std::transform(lowercase_string.begin(), lowercase_string.end(), lowercase_string.begin(), ::tolower);

				if (std::find(english_words.begin(), english_words.end(), lowercase_string) != english_words.end()) {
					possible_passwords.emplace_back(word);
				}
			}
			possible_sentences.emplace_back(possible_passwords);
		}

		vector<string> current_sentence;
		vector<vector<string>> sentence_combinations;
		ordered_combinations<string>(possible_sentences, current_sentence, sentence_combinations);

		possible_passwords_strings.emplace_back(sentence_combinations);
	}

	return password_combination_to_strings(possible_passwords_strings);
}

void PasswordSecurity::decrypt_password_recursive(string password, int offset, vector<vector<vector<int>>>& possible_passwords, vector<vector<int>>& current_password_possibility) {
	
	if (password.size() == 0) {
		possible_passwords.emplace_back(current_password_possibility);
		return;
	}

	string current_numbers;
	int count = 0;
	vector<int> ascii_values;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0 && current_password_possibility.size() > 0) return;
		auto ascii_value_search = collatz_multiple_ascii_result.find(make_pair(std::stoi(current_numbers), offset));
		ascii_value_search != collatz_multiple_ascii_result.end() ? ascii_values = ascii_value_search->second : ascii_values = vector<int>();

		if (!(ascii_values.size() == 0)) {
			current_password_possibility.emplace_back(ascii_values);
			decrypt_password_recursive(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_passwords, current_password_possibility);
			current_password_possibility.pop_back();
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
	int ascii_value = 0;
	while (current_numbers.size() < 3 && possible_password.size() < 1 && !(current_numbers == password)) {
		current_numbers += password[count];

		if (std::stoi(current_numbers) == 0 && current_password_possibility.size() > 0) return;

		auto ascii_value_search = collatz_first_ascii_result.find(make_pair(std::stoi(current_numbers), offset));
		ascii_value_search != collatz_first_ascii_result.end() ? ascii_value = ascii_value_search->second : ascii_value = -1;

		if (ascii_value != -1) {
			current_password_possibility.emplace_back(ascii_value);
			decrypt_password_recursive_single(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_password, current_password_possibility);
			current_password_possibility.pop_back();
		}

		if (current_numbers == password) return;
		count++;
	}
}

void PasswordSecurity::decrypt_password_recursive_string(string password, int offset, vector<vector<vector<int>>>& possible_passwords, vector<vector<int>>& current_password_possibility) {
	
	if (password.size() == 0) {
		possible_passwords.emplace_back(current_password_possibility);
		return;
	}

	string current_numbers;
	int count = 0;
	vector<int> ascii_values;
	while (current_numbers.size() < 3 && !(current_numbers == password)) {
		current_numbers += password[count];
		if (std::stoi(current_numbers) == 0 && current_password_possibility.size() > 0) return;
		auto ascii_value_search = collatz_multiple_sentence_ascii_result.find(make_pair(std::stoi(current_numbers), offset));
		ascii_value_search != collatz_multiple_sentence_ascii_result.end() ? ascii_values = ascii_value_search->second : ascii_values = vector<int>();

		if (!(ascii_values.size() == 0)) {
			current_password_possibility.emplace_back(ascii_values);
			decrypt_password_recursive_string(password.substr(count + 1, password.size() - count), std::stoi(current_numbers), possible_passwords, current_password_possibility);
			current_password_possibility.pop_back();
		}
		count++;
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

void PasswordSecurity::generate_collatz_ascii_values() {
	set<int> possible_values;
	int max_collatz = 0;
	int max_iter = 256;
	for (int i = 1; i < 256; i++) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	max_iter = max_collatz + 256;
	for (int i = 256; i < max_iter; ++i) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	for (int i = max_iter; i < 256 + max_collatz; ++i) {
		possible_values.insert(collatz(i));
	}

	for (auto it = possible_values.begin(); it != possible_values.end(); ++it) {
		for (int i = 1; i < 256; i++) {
			collatz_first_ascii_result.insert(make_pair(make_pair(collatz(i + *it), *it), i));
		}
	}
}

void PasswordSecurity::generate_collatz_multiple_ascii_values() {
	set<int> possible_values;
	int max_collatz = 0;
	int max_iter = 256;
	for (int i = 1; i < 256; i++) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	max_iter = max_collatz + 256;
	for (int i = 256; i < max_iter; ++i) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	for (int i = max_iter; i < 256 + max_collatz; ++i) {
		possible_values.insert(collatz(i));
	}

	for (auto it = possible_values.begin(); it != possible_values.end(); ++it) {
		for (int i = 1; i < 256; i++) {
			pair<int, int> collatz_and_offset = make_pair(collatz(i + *it), *it);
			auto ascii_value_search = collatz_multiple_ascii_result.find(collatz_and_offset);
			if (ascii_value_search != collatz_multiple_ascii_result.end()) {
				ascii_value_search->second.emplace_back(i);
			}
			else {
				vector<int> ascii_values = { i };
				collatz_multiple_ascii_result.insert(make_pair(collatz_and_offset, ascii_values));
			}
		}
	}

	return;
}

void PasswordSecurity::generate_collatz_multiple_sentence_ascii_values() {
	set<int> possible_values;
	int max_collatz = 0;
	int max_iter = 256;
	for (int i = 1; i < 256; i++) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	max_iter = max_collatz + 256;
	for (int i = 256; i < max_iter; ++i) {
		int collatz_value = collatz(i);
		possible_values.insert(collatz_value);
		if (collatz_value > max_collatz) max_collatz = collatz_value;
	}

	for (int i = max_iter; i < 256 + max_collatz; ++i) {
		possible_values.insert(collatz(i));
	}

	for (auto it = possible_values.begin(); it != possible_values.end(); ++it) {
		for (int i = 32; i < 123; i++) {
			if (i > 32 && i < 63) {
				continue;
			}
			pair<int, int> collatz_and_offset = make_pair(collatz(i + *it), *it);
			auto ascii_value_search = collatz_multiple_sentence_ascii_result.find(collatz_and_offset);
			if (ascii_value_search != collatz_multiple_sentence_ascii_result.end()) {
				ascii_value_search->second.emplace_back(i);
			}
			else {
				vector<int> ascii_values = { i };
				collatz_multiple_sentence_ascii_result.insert(make_pair(collatz_and_offset, ascii_values));
			}
		}
	}

	return;
}