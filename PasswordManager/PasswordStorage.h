#pragma once
#include "FileStorage.h"
class PasswordStorage :
	public FileStorage
{
public:
protected:
	virtual void save_to_file(const string password) throw (invalid_argument);
};

