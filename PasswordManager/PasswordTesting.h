#ifndef PASSWORDTESTING_H
#define PASSWORDTESTING_H

#pragma once
#include <string>
#include <vector>
using namespace std;

class PasswordTesting
{
public:
	static void GeneratePasswords(const string file_name);
	static void TestPasswords(const string file_name);
};

#endif

