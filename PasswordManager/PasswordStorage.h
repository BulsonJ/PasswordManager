#ifndef PASSWORDSTORAGE_H
#define PASSWORDSTORAGE_H

#pragma once
#include "FileStorage.h"
#include <vector>
using namespace std;

class PasswordStorage :
	public FileStorage
{
public:
	PasswordStorage(const string file_name);
	~PasswordStorage();
	virtual void save_to_file(const string password) throw (invalid_argument);
	void save_passwords_to_file(const string* password) throw (invalid_argument);
	string** read_from_file();
protected:
	fstream data_file;
};

#endif
