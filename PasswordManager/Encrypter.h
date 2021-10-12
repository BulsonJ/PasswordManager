#include <string>
using namespace std;

class Encrypter
{
public:
	static string encrypt_string(const string s);
protected:
	static int collatz(const int input);
	static int collatz(const int input, const int count);
};

