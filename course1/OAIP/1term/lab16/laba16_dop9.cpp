//1. Дан двумерный массив, состоящий из N строк и М столбцов, а также число number. Проверить, находится ли это число  на главной диагонали.
//2. Написать программу, которая вводит ряд строк текста и выводит те из них, которые начинаются с буквы «b».
#include <iostream>
using namespace std;
void findnumb(int** matrix, int n);
void matrix();
void stroka();
int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	int choice;
	do
	{
		cout << "Выберите вариант работы" << endl;
		cout << "1 - с двумерным массивом" << endl;
		cout << "2 - со строками" << endl;
		cout << "3 - выход" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			matrix();
			break;
		case 2:
			stroka();
			break;
		case 3:
			break;
		}
	} while (choice != 3);
}
void matrix()
{
	int n, z;
	cout << "Введите размер матрицы ";
	cin >> n;

	int** array = new int* [n];

	for (int i = 0; i < n; i++)
	{
		array[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "Введите эл матрицы:" << endl;
			cin >> array[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl;


	findnumb(array, n);

	for (int i = 0; i < n; i++)
	{
		delete[] array[i];

	}

	delete[] array;

}

void findnumb(int** matrix, int l)
{
	int number = 0;

	cout << "Введите число(number)" << endl;
	cin >> number;

	for (int i = 0; i < l; i++)
	{
		if (matrix[i][i] == number)
		{
			cout << "Заданное число находится на главной диагонали на позиции " << i << i << endl;
		}
		else
		{
			cout << "Заданное число не находится на главной диагонали на позиции " << i << i << endl;
		}
	}

}
void stroka()
{
	int amount;
	cout << "Введите количество строк: " << endl;
	cin >> amount;
	char str[256];
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int k = 0; k < amount; k++)
	{

		cout << "Введите строку" << endl;

		cin.getline(str, 256, '\n');


		if (str[0] == 'b')
		{
			cout << str << endl;
		}

		else
		{
			cout << "Строка не начинается с символа 'b' " << endl;
		}


	}
}

