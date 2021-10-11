#include <string>
using namespace std;

struct Account {
	string username;
	string password;
};

class PasswordStorage
{
public:
	PasswordStorage(string file_name);
	~PasswordStorage();
	bool check_duplicate_username(const string name) const;
	void save_to_file(const Account& s) const;
protected:
	string file_name;
};

