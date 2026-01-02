#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int n, k, num = 0, counter = 0;
	cout << "Введите, с какой строки копировать:\n";
	cin >> n;
	cout << "Введите, до какой строки копировать:\n";
	cin >> k;
	string str;
	ifstream file1("FILE1.txt");
	ofstream file2("FILE2.txt");
	k--;
	n--;
	while (getline(file1, str))
	{
		if (num >= n && num <= k)
		{
			file2 << str << '\n';
			for (int j = 0; j < 8; j++)
			{
				if (str[j] == 'q' || str[j] == 'w' || str[j] == 'r' || str[j] == 't' || str[j] == 'p' || str[j] == 's' || str[j] == 'd' || str[j] == 'f' ||
					str[j] == 'g' || str[j] == 'h' || str[j] == 'j' || str[j] == 'k' || str[j] == 'l' || str[j] == 'z' || str[j] == 'x' || str[j] == 'c' ||
					str[j] == 'v' || str[j] == 'b' || str[j] == 'n' || str[j] == 'm')
					counter++;
			}
		}
		num++;
	}
	cout << counter << " согласных букв.\n";
}