// вариант 1 задание 2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string fileOut(string* pStrOut)
{
	ofstream file1("f1_1.txt");
	file1 << *pStrOut;
	file1.close();
	return *pStrOut;
}

string fileIn(string* pStrIn)
{
	string StrIn, min = "0000000";
	short counter = 1, SequenceNum;
	int c;
	ifstream file2("f1_1.txt");
	while (file2)
	{
		file2 >> StrIn;
		int len1 = StrIn.length();
		for (int i = 0; i < len1; i++) {
			if (StrIn[i] >= '0' && StrIn[i] <= '9') {
				if (StrIn[i] % 2 == 1) cout << StrIn[i] << " ";
			}
		}

	}

	file2.close();
	return StrIn;
}

int main()
{
	setlocale(LC_ALL, "ru");
	string strOut, strIn;
	string* pStrOut = &strOut, * pStrIn = &strIn;
	cout << "Введите строку с цифрами:\n";
	getline(cin, strOut);
	fileOut(pStrOut);
	fileIn(pStrIn);
}