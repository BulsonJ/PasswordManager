#pragma once
#include "FileStorage.h"
#include <vector>
#include <string>
using namespace std;

class PasswordStorage :
	public FileStorage
{
public:
	PasswordStorage(const string file_name);
	~PasswordStorage();
	virtual void save_to_file(const string password) throw (invalid_argument);
	string** read_from_file();
protected:
	fstream data_file;
};

