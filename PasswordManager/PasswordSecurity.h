#include <string>
#include <vector>
using namespace std;

class PasswordSecurity
{
public:
	static string encrypt_string(const string s);

	static vector<vector<vector<int>>> decrypt_password(string password);
	static vector<vector<int>> decrypt_password_first_result(string password);
	static vector<vector<vector<string>>> decrypt_string(string password);
	static void decrypt_password_recursive(string rest_of_password,int offset, vector<vector<vector<int>>>& possible_words, vector<vector<int>>& current_word_possibility);
	static void decrypt_password_recursive_single(string rest_of_password, int offset, vector<vector<int>>& possible_words, vector<int>& current_word_possibility);
	static void decrypt_password_recursive_string(string rest_of_password, int offset, vector<vector<vector<int>>>& possible_words, vector<vector<int>>& current_word_possibility);

	//static void combinations(vector<vector<int>> word, vector<int> current_word, vector<vector<int>>& final_words);

	static void print_ascii_collatz_values(int offset);
	static vector<pair<int, int>> get_ascii_collatz_values(int offset);
	static int get_ascii_from_collatz(int collatz, int offset);
	static vector<int> get_ascii_list_from_collatz(int collatz, int offset);
	static vector<int> get_ascii_string_list_from_collatz(int collatz, int offset);
protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);
};

