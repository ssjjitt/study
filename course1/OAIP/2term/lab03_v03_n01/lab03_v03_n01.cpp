// 3 вариант 1 задание
// Скопировать из файла FILE1 в файл FILE2 строки, начиная с к до к + 3. Подсчитать количество гласных букв в FILE2.
#include <fstream>
#include <stdio.h>
#include <iostream>
#define LEN 256
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int row1, row2;
	ifstream ifile("FILE1.txt");
	fstream ofile("FILE2.txt");
	cout << "k строки:\n";
	cin >> row1;
	row2 = row1 + 3;
	int sum = 0, count = 0;
	char str[LEN];

	while (ifile >> str)
	{
		row1--;
		row2--;
		if (sum < row1)
		{
		}
		else
		{
			if (row1 <= row2)
			{
				ofile << str << "\n";
				for (int i = 0; i < strlen(str); i++)
					if ((str[i] == 'a' || str[i] == 'e') || ((str[i] == 'y' || str[i] == 'u') || (str[i] == 'i' || str[i] == 'o')))
						count++;
			}
			row1++;
		}
	}

	cout << "количество гласных: " << count;

	ifile.close();
	ofile.close();
}