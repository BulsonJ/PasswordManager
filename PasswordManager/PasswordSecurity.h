#include <string>
#include <vector>
using namespace std;

class PasswordSecurity
{
public:
	static string encrypt_string(const string s);
	static string decrypt_password(const string s);
	static void print_ascii_collatz_values(int offset);
	static vector<pair<int, int>> get_ascii_collatz_values(int offset);
protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);
};

