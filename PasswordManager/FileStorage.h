#pragma once
#include <string>
#include <fstream>
#include <exception>
using namespace std;

class FileStorage
{
public:
	FileStorage(string file_name) { this->file_name = file_name; };
	~FileStorage() {};
protected:
	string file_name;
	virtual void save_to_file(const string s) = 0;
};

