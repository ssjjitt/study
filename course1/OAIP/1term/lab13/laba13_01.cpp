// Написать программу, реализующую выделение подстроки S1 длиной k с позиции номер n из неко-торой строки. 
#include <iostream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	string s;
	int n, k, i;
	cout << "введите строку: ";
	cin >> s;
	cout << "количество символов: ";
	cin >> k;
	cout << "позиция: ";
	cin >> n;
	cout << "подстрока: " << s.substr(n, k) << endl;
}
