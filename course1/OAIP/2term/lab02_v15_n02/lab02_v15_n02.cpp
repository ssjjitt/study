#include <stdio.h>
#include <iostream>
#define LEN 100
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int row1, row2;
	FILE* f1;
	FILE* f2;
	errno_t err1, err2;
	err1 = fopen_s(&f1, "t1.txt", "r");
	if (err1 != NULL)
	{
		printf("ошибка открытия файла\n"); return -1;
	}
	err2 = fopen_s(&f2, "t2.txt", "w");
	if (err2 != NULL)
	{
		printf("Ошибка\n"); return -1;
	}
	fclose(f1);
	fclose(f2);
	cout << "k строки:\n";
	cin >> row1;
	row2 = row1 + 3;
	fopen_s(&f1, "t1.txt", "r");
	fopen_s(&f2, "t2.txt", "w");
	int sum = 0;
	char str[LEN];

	while (fgets(str, LEN, f1))
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
				fputs(str, f2);
			}
			row1++;
		}
	}
}