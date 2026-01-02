// Студенты.Ф.И.О., дата поступления, специальность, группа, факультет, средний балл.Выбор по среднему баллу.

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

void output();
void input();
void find();
void del();

union Note		// объединение
{
	char str[50];
};

struct Notee
{
	Note fio;
	Note spec;
	Note date;
	Note number;
	Note faculty;
	Note ball;
};

Notee note[20];		// массив структур

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
		cin >> note[i].fio.str;
		file1 << "\t№" << note[i].fio.str << "\n";
		file1 << "\n";


		cout << "\nДата поступления:\n";
		cin >> note[i].date.str;
		file1 << note[i].date.str;
		file1 << "\n";

		cout << "\nСпециальность\n";
		cin >> note[i].spec.str;
		file1 << note[i].spec.str;
		file1 << "\n";

		cout << "\nГруппа\n";
		cin >> note[i].number.str;
		file1 << note[i].number.str;
		file1 << "\n";

		cout << "\nФакультет\n";
		cin >> note[i].faculty.str;
		file1 << note[i].faculty.str;
		file1 << "\n";

		cout << "\nСредний балл\n";
		cin >> note[i].ball.str;
		file1 << note[i].ball.str;
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
	cout << "Фамилия: " << note[i].fio.str << '\n';
	cout << "Дата поступления: " << note[i].date.str << '\n';
	cout << "Специальность: " << note[i].spec.str << '\n';
	cout << "Группа: " << note[i].number.str << '\n';
	cout << "Факультет: " << note[i].faculty.str << '\n';
	cout << "Средний балл: " << note[i].ball.str << '\n';

}

// функция для поиска 

void find()
{
	string search;
	cout << "Введите балл, по которому искать:";
	cin >> search;
	for (int i = 0; i < 20; i++)
	{
		if (search == note[i].ball.str)
		{
			cout << "\t№" << i + 1 << '\n';
			cout << "Фамилия: " << note[i].fio.str << '\n';
			cout << "Дата поступления: " << note[i].date.str << '\n';
			cout << "Специальность: " << note[i].spec.str << '\n';
			cout << "Группа: " << note[i].number.str << '\n';
			cout << "Факультет: " << note[i].faculty.str << '\n';
			cout << "Средний балл: " << note[i].ball.str << '\n';
		}
	}
	cout << "\n\n";
}
