#pragma once
#include <string>
#include <iostream>

using namespace std;

class Palin
{
public:
	string findPalin(string number);

private:
	string increase(string &number, int mid=0);
};

