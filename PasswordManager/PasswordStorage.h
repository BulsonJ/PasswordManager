#pragma once
#include <string>
#include <map>
using namespace std;

class PasswordStorage
{
public:
	PasswordStorage(string file_name) throw (invalid_argument);
	~PasswordStorage();
	bool check_duplicate_username(const string name) const;
	void save_to_file(const string username, const string password) throw (invalid_argument);
	string get_password(const string username);
protected:
	string file_name;
	map<string, string> accounts;
};

