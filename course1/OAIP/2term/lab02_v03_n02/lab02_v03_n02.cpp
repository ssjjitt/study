// 3 вариант 2 задание
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "");
	const int len = 4;
	char line1[len], line2[len], line3[len];
	FILE* f1;
	fopen_s(&f1, "NameA.txt", "r"); // открываем файл для чтения
	FILE* f2;
	fopen_s(&f2, "NameB.txt", "r");
	FILE* f3;
	fopen_s(&f3, "NameC.txt", "r");
	FILE* f4;
	fopen_s(&f4, "NameD.txt", "w");	// открываем файл для записи

	for (int i = 0; i <= 6; i++)
	{
		fgets(line1, len, f1);	// читаем строку из указанного потока, пока не встретится символ перевода на новую строку
		fputs(line1, f4);		// записываем строку в указанный поток(f4 - NameD.txt)
		fgets(line2, len, f2);
		fputs(line2, f4);		// записываем строку
		fgets(line3, len, f3);
		fputs(line3, f4);		// записываем строку 
	}
	cout << "Данные записаны в файл NameD.txt" << endl;
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
}