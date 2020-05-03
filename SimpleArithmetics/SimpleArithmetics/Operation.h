#pragma once
#include <string>
using namespace std;
class Operation
{
	string x,
		y,
		out;
	char operation;

public:
	Operation();
	Operation(string a);
	void remove0fromFront(string &digits);
	string doSeparator(size_t len);
	void alignStrings(string &a, string &b);
	string addition(string a, string b);
	string subtraction(string a, string b);
	string* multiplication(string a, string b);
	void insertSpaceAtFront(string &str, size_t len);
	void perform();
	void print();
	string getOutput();
};

