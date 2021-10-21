#ifndef PASSWORDSECURITY_H
#define PASSWORDSECURITY_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class PasswordSecurity
{
public:
	PasswordSecurity();
	~PasswordSecurity();

	static string encrypt_string(const string s);
	static string encrypt_vector_int(const vector<int> input);

	vector<vector<vector<int>>> decrypt_password(const string password);
	vector<int> decrypt_password_first_result(const string password);
	vector<string> decrypt_string(const string password, const string filename);

	void generate_collatz_ascii_values();
	void generate_collatz_multiple_ascii_values();
	void generate_collatz_multiple_sentence_ascii_values();
protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);

	map<pair<int, int>, int> collatz_first_ascii_result;
	map<pair<int, int>, vector<int>> collatz_multiple_ascii_result;
	map<pair<int, int>, vector<int>> collatz_multiple_sentence_ascii_result;

	void decrypt_password_recursive(string rest_of_password, int offset, vector<vector<vector<int>>>& password_possibilities, vector<vector<int>>& current_password_possibility);
	void decrypt_password_recursive_single(string rest_of_password, int offset, vector<int>& password_possibility, vector<int>& current_password_possibility);
	void decrypt_password_recursive_string(string rest_of_password, int offset, vector<vector<vector<int>>>& password_possibilities, vector<vector<int>>& current_password_possibility);

	vector<vector<vector<int>>> split_sentence_into_words(vector<vector<int>> sentence);
	vector<string> password_combination_to_strings(vector<vector<vector<string>>> possible_passwords_strings);
	string convert_vector_to_word(vector<int> word);

	static int get_ascii_from_collatz(int collatz, int offset);
	static vector<int> get_ascii_list_from_collatz(int collatz, int offset);
	static vector<int> get_ascii_string_list_from_collatz(int collatz, int offset);
};

#endif

