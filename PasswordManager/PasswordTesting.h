#pragma once
#include <string>
#include <vector>
using namespace std;

class PasswordTesting
{
public:
	static void GeneratePasswords(const string file_name);
	static void TestPasswords(const string file_name);
protected:
	static void Generate_Repeating_Set(const string file_name);
	static void Generate_Nonrepeating_Set(const string file_name);

};

