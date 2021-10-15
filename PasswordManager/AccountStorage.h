#pragma once
#include <string>
#include <map>
#include <exception>
#include "FileStorage.h"
using namespace std;

class AccountStorage : public FileStorage
{
public:
	AccountStorage(string file_name) throw (invalid_argument);
	void save_to_file(const string s) throw (invalid_argument);
	virtual void save_to_file(const string username, const string password) throw (invalid_argument);

	bool check_duplicate_username(const string name) const;
	string get_password(const string username) const;
protected:
	map<string, string> accounts;
};

