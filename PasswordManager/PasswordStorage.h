#pragma once
#include "FileStorage.h"
class PasswordStorage :
	public FileStorage
{
public:
	PasswordStorage(const string file_name);
	~PasswordStorage();
	virtual void save_to_file(const string password) throw (invalid_argument);
protected:
	ofstream data_file;
};

