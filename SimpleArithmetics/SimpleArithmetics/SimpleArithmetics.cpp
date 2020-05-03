
#include <iostream>
#include <string>
#include <algorithm>

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
};

string Operation::addition(string a, string b)
{
	alignStrings(a, b);
	if (a.length() != b.length())
	{
		return "Error";
	}
	string str;
	int i,
		add = 0;

	for (i = a.length() - 1; i >= 0; i--)
	{
		add += a[i] + b[i] - 2 * '0';
		str += add % 10 + '0';
		if (add / 10 > 0)
			add = 1;
		else
			add = 0;
	}

	if (add > 0)
		str += add + '0';

	reverse(str.begin(), str.end());

	return str;
}

string Operation::subtraction(string a, string b)
{
	alignStrings(a, b);
	if (a.length() != b.length())
	{
		return "Error";
	}
	string str;
	int i,
		sub = 0;

	for (i = a.length() - 1; i >= 0; i--)
	{
		sub = a[i] - b[i] - sub;
		if (sub < 0)
		{
			str += sub + 10 + '0';
			sub = 1;
		}
		else
		{
			str += sub + '0';
			sub = 0;
		}
	}

	reverse(str.begin(), str.end());

	return str;
}

string* Operation::multiplication(string a, string b)
{
	string *str = new string[b.length()];
	int i,
		j,
		z,
		mul = 0;
	for (j = b.length() - 1, z = 0; j >= 0; j--, z++)
	{
		for (i = a.length() - 1; i >= 0; i--)
		{
			mul = (a[i] - '0')*(b[j] - '0') + mul;
			str[z] += mul % 10 + '0';
			mul /= 10;
		}
		if (mul > 0)
			str[z] += mul + '0';
		mul = 0;
		reverse(str[z].begin(), str[z].end());
	}
	return str;
}

Operation::Operation()
{
	x = "";
	y = "";
	operation = '0';
}

Operation::Operation(string line)
{
	size_t len = line.length(),
		pos;
	char opp[] = { '+', '-', '*' };

	if (len > 0)
	{
		for (int i = 0; i < 3; i++)
		{
			pos = line.find(opp[i]);
			if (pos != string::npos)
			{
				x = line.substr(0, pos);
				y = line.substr(pos + 1, len);
				operation = opp[i];
				break;
			}
		}
	}
}

void Operation::remove0fromFront(string &digits)
{
	int len = digits.length(),
		i;
	bool stop = false;
	for (i = 0; i < len; i++)
	{
		if (stop == true && digits[i] == ' ')
		{
			digits[i - 1] = '0';
			return;
		}
		else if (digits[i] == ' ')
			continue;
		else if (digits[i] == '0')
		{
			digits[i] = ' ';
			stop = true;
			continue;
		}
		else
			return;
	}
	digits[i - 1] = '0';
}

string Operation::doSeparator(size_t len)
{
	if (len > 0)
	{
		string str;
		str.append(len, '-');
		return str;
	}
	return "Error";
}

void Operation::insertSpaceAtFront(string &str, size_t len)
{
	if (len - str.length() > 0)
	{
		str.insert(0, len - str.length(), ' ');
	}
}

void Operation::perform()
{
	size_t len = 0;

	if (operation == '+')
	{
		string solution,
			separator;

		solution = addition(x, y);
		y.insert(0, 1, '+');
		len = max(x.length(), y.length());
		len = max(len, solution.length());
		insertSpaceAtFront(x, len);
		insertSpaceAtFront(y, len);
		insertSpaceAtFront(solution, len);
		separator = doSeparator(len);
		out = x + "\n" + y + "\n" + separator + "\n" + solution + "\n";
		return;
	}

	if (operation == '-')
	{
		string solution,
			separator;

		solution = subtraction(x, y);
		remove0fromFront(solution);
		y.insert(0, 1, '-');
		len = max(x.length(), y.length());
		len = max(len, solution.length());
		insertSpaceAtFront(x, len);
		insertSpaceAtFront(y, len);
		insertSpaceAtFront(solution, len);
		separator = doSeparator(len);
		out = x + "\n" + y + "\n" + separator + "\n" + solution + "\n";
		return;
	}

	if (operation == '*')
	{
		string *solution,
			separator,
			t,
			t1;
		int row,
			i;

		solution = multiplication(x, y);
		row = y.length();
		t = solution[0];
		for (i = 1; i < row; i++)
		{
			t1 = solution[i];
			t = addition(t, t1.append(i, '0'));
		}
		y.insert(0, 1, '*');
		len = max(x.length(), y.length());
		separator = doSeparator(len);
		len = max(len, t.length());
		insertSpaceAtFront(x, len);
		insertSpaceAtFront(y, len);
		insertSpaceAtFront(separator, len);
		out = x + "\n" + y + "\n" + separator + "\n";
		for (i = 0; i < row; i++)
		{
			solution[i].append(i, ' ');
			remove0fromFront(solution[i]);
			insertSpaceAtFront(solution[i], len);
			out += solution[i] + "\n";
		}
		if (row > 1)
		{
			separator = doSeparator(t.length());
			insertSpaceAtFront(separator, len);
			insertSpaceAtFront(t, len);
			out += separator + "\n" + t + "\n";
		}
		return;
	}

}

void Operation::print()
{
	cout << out << endl;
}

void Operation::alignStrings(string &a, string &b)
{
	if (a.length() > b.length())
	{
		b.insert(0, a.length() - b.length(), '0');
	}
	else if (b.length() > a.length())
	{
		a.insert(0, b.length() - a.length(), '0');
	}
}

int main()
{
	int lines;
	Operation *operation;
	string line;

	cin >> lines;
	operation = new Operation[lines];
	for (int i = 0; i < lines; i++)
	{
		cin >> line;
		operation[i] = Operation(line);
		operation[i].perform();
	}
	for (int i = 0; i < lines; i++)
	{
		operation[i].print();
	}

	getchar();
	return 0;
}
