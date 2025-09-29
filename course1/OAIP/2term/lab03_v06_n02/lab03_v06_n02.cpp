#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string fileOut(string* pStrOut)
{
	ofstream file1("file1.txt");
	file1 << *pStrOut;
	file1.close();
	return *pStrOut;
}

string fileIn(string* pStrIn)
{
	string StrIn;
	ifstream file2("file1.txt");
	while (file2)
	{
		file2 >> StrIn;
		if (StrIn.length() % 2 == 0)
			cout << StrIn << '\n';
	}
	file2.close();
	return StrIn;
}

int main()
{
	setlocale(LC_ALL, "ru");
	string strOut, strIn;
	string* pStrOut = &strOut, * pStrIn = &strIn;
	cout << "Введите группы цифр, разделенные пробелом:\n";
	getline(cin, strOut);
	fileOut(pStrOut);
	fileIn(pStrIn);
}