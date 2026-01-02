// 14 вариант 2 задание
#include <stdio.h>
#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");
	FILE* F1;
	FILE* F2;
	char str[255];
	errno_t err;
	err = fopen_s(&F1, "f1_14.txt", "w");
	for (int i = 0; i < 6; i++)
	{
		printf("Строка  %d: \n", i + 1);
		gets_s(str);
		fputs(str, F1);
		fputs("\n", F1);
	}
	fclose(F1);
	err = fopen_s(&F1, "f1_14.txt", "r");
	err = fopen_s(&F2, "f2_14.txt", "w");

	while (fgets(str, 255, F1) != 0)
	{
		if (str[0] >= '0' && str[0] <= '9')
		{
			fputs(str, F2);
		}
	}
	fclose(F1);
	fclose(F2);
}