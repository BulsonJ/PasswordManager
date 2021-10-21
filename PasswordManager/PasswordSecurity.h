#include <string>
#include <vector>
#include <map>
using namespace std;

class PasswordSecurity
{
public:
	static string encrypt_string(const string s);
	static string encrypt_vector_int(const vector<int> input);

	static vector<vector<vector<int>>> decrypt_password(string password);
	static vector<int> decrypt_password_first_result(string password);
	static vector<string> decrypt_string(string password);

protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);

	static void decrypt_password_recursive(string rest_of_password, int offset);
	static void decrypt_password_recursive(string rest_of_password, int offset, vector<vector<vector<int>>>& password_possibilities, vector<vector<int>>& current_password_possibility);
	static void decrypt_password_recursive_single(string rest_of_password, int offset, vector<int>& password_possibility, vector<int>& current_password_possibility);
	static void decrypt_password_recursive_string(string rest_of_password, int offset, vector<vector<vector<int>>>& password_possibilities, vector<vector<int>>& current_password_possibility);

	static int get_ascii_from_collatz(int collatz, int offset);
	static vector<int> get_ascii_list_from_collatz(int collatz, int offset);

	static vector<int> get_ascii_string_list_from_collatz(int collatz, int offset);
};

