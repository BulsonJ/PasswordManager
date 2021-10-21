#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#pragma once
#include <string>
#include <fstream>
#include <ostream>
#include <exception>
using namespace std;

class FileStorage
{
public:
	FileStorage(const string file_name) { this->file_name = file_name; };
	~FileStorage() {};
protected:
	string file_name;
	virtual void save_to_file(const string s) = 0;
};

#endif

