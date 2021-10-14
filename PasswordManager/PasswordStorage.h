#pragma once
#include <string>
#include <map>
using namespace std;

class PasswordStorage
{
public:
	PasswordStorage(string file_name);
	~PasswordStorage();
	bool check_duplicate_username(const string name) const;
	void save_to_file(const string username, const string password);
	string get_password(const string username);
protected:
	string file_name;
	map<string, string> accounts;
};

