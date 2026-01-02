// вариант 1 номер 2


#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

void output();
void input();
void find();
void del();

union Teach		// объединение
{
	char str[50];
};

struct Teacher
{
	Teach fio;
	Teach exam;
	Teach date;
};

Teacher teachers[20];		// массив структур

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	int choice;
	do
	{
		cout << "\nвыберите пункт меню: "
			<< "\n1 - ввод с клавиатуры "
			<< "\n2 - вывод информации на экран"
			<< "\n3 - поиск"
			<< "\n0 - выход из программы\n";
		cin >> choice;


		switch (choice)
		{
		case 1: input();  break;
		case 2: output(); break;
		case 3: find(); break;
		case 0: exit(0);  break;
		}
	} while (choice != 0);
}

// функция для ввода и записи в файл

void input()
{
	int num;
	do {
		cout << "Введите количество(не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		cout << "\nФамилия:\n";
		cin >> teachers[i].fio.str;
		file1 << "\t№" << teachers[i].fio.str << "\n";
		file1 << "\n";


		cout << "\nДата экзамена:\n";
		cin >> teachers[i].date.str;
		file1 << teachers[i].date.str;
		file1 << "\n";

		cout << "\nЭкзамен\n";
		cin >> teachers[i].exam.str;
		file1 << teachers[i].exam.str;
		file1 << "\n";
	}
	file1.close();
}

// функция для вывода в консоль
void output()
{
	int num;
	cout << "Введите номер по счету, которого вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	cout << "\t№" << num << '\n';
	cout << "Фамилия: " << teachers[i].fio.str << '\n';
	cout << "Дата экзамена: " << teachers[i].date.str << '\n';
	cout << "Экзамен: " << teachers[i].exam.str << '\n';

}

// функция для поиска 

void find()
{
	string fioSearch;
	cout << "Введите фамилию, по которой искать:";
	cin >> fioSearch;
	for (int i = 0; i < 20; i++)
	{
		if (fioSearch == teachers[i].fio.str)			
		{
			cout << "\t№" << i + 1 << '\n';
			cout << "Фамилия: " << teachers[i].fio.str << '\n';
			cout << "Дата экзамена: " << teachers[i].date.str << '\n';
			cout << "Экзамен: " << teachers[i].exam.str << '\n';
		}
	}
	cout << "\n\n";
}