// 12-я лаба, 5в.  Отредактировать заданное предложение, удаляя из него все слова с нечетными номерами и переворачивая слова с четными номерами. 

#include <iostream>		
#include<Windows.h>
#pragma warning(default:4716)
int test() {
	return 0;
}
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int* h(char* arr, int size);
	char arr[255];
	puts("Введите предложение: ");
	gets_s(arr);
	int size = strlen(arr);
	*h(arr, size);
}
int* h(char* arr, int size)
{
	int i, pos = 0, a = -100, k;
	for (i = 0; i <= size; i++)
	{
		if (arr[i] == ' ')
		{
			pos++;
			if (pos % 2 == 0)
			{
				for (k = i - 1; k > a; k--)
					cout << arr[k];
				cout << " ";
			}
			else a = i;
		}
	}
}
