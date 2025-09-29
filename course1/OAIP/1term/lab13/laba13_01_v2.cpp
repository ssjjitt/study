// Написать программу, реализующую выделение подстроки S1 длиной k с позиции номер n из неко-торой строки. 
#include <iostream>
#include <stdio.h>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	char string[256];
	int position, kolvo;
	cout << "введите строку: ";
	gets_s(string);

	cout << "введите позицию, с которой начнется выделение подстроки: ";
	cin >> position;

	cout << "введите длину подстроки: ";
	cin >> kolvo;

	cout << "подстрока: ";

	for (int i = position; i < position + kolvo; i++)
	{
		cout << string[i];
	}
}