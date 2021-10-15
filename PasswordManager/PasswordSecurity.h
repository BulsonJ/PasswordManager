#include <string>
#include <vector>
using namespace std;

class PasswordSecurity
{
public:
	static string encrypt_string(const string s);
	static string decrypt_password(const string s);
	static vector<int>* decrypt_password_r(string password);
	static void decrypt_password_recursive(string rest_of_password,int offset, vector<int>* ascii_values);
	static void print_ascii_collatz_values(int offset);
	static vector<pair<int, int>> get_ascii_collatz_values(int offset);
	static vector<int> get_ascii_from_collatz(int collatz, int offset);
protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);
};

