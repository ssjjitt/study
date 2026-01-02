// 2 вариант 2 задание
#include <stdio.h>
#include <iostream>


using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	const int len = 3;
	char line1[len], line2[len];
	FILE* f1;
	fopen_s(&f1, "f.txt", "r");
	FILE* f2;
	fopen_s(&f2, "g.txt", "w");
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
			fputs(line1, f2);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
			fputs(line1, f2);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
			fputs(line1, f2);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
		}
	}
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			fgets(line1, len, f1);
			fputs(line1, f2);
		}
	}
	cout << "Данные записаны в файл g.txt" << endl;
}