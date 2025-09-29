// Личная библиотека.Автор книги, название, издательство, раздел библиотеки(специальная литература, хобби, домашнее хозяйство, беллетристика и т.д.), 
// происхождение(покупка, кража, подарок) и наличие книги в данный момент.Выбор книг по автору.

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
	Note name;
	Note izdat;
	Note razdel;
	Note proisxozd;
	Note nalichie;
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


		cout << "\nИздательство:\n";
		cin >> note[i].izdat.str;
		file1 << note[i].izdat.str;
		file1 << "\n";

		cout << "\nНазвание книги\n";
		cin >> note[i].name.str;
		file1 << note[i].name.str;
		file1 << "\n";

		cout << "\nТелефон\n";
		cin >> note[i].razdel.str;
		file1 << note[i].razdel.str;
		file1 << "\n";

		cout << "\nПроисхождение\n";
		cin >> note[i].proisxozd.str;
		file1 << note[i].proisxozd.str;
		file1 << "\n";

		cout << "\nНаличие\n";
		cin >> note[i].nalichie.str;
		file1 << note[i].nalichie.str;
		file1 << "\n";
	}
	file1.close();
}

// функция для вывода в консоль
void output()
{
	int num;
	cout << "Введите номер, которого вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	cout << "\t№" << num << '\n';
	cout << "Фамилия: " << note[i].fio.str << '\n';
	cout << "Издательство: " << note[i].izdat.str << '\n';
	cout << "Название книги: " << note[i].name.str << '\n';
	cout << "Раздел библиотеки: " << note[i].razdel.str << '\n';
	cout << "Происхождение: " << note[i].proisxozd.str << '\n';
	cout << "Наличие: " << note[i].nalichie.str << '\n';

}

// функция для поиска 

void find()
{
	string fioSearch;
	cout << "Введите фамилию, по которой искать:";
	cin >> fioSearch;
	for (int i = 0; i < 20; i++)
	{
		if (fioSearch == note[i].fio.str)
		{
			cout << "\t№" << i + 1 << '\n';
			cout << "Фамилия: " << note[i].fio.str << '\n';
			cout << "Издательство: " << note[i].izdat.str << '\n';
			cout << "Название книги: " << note[i].name.str << '\n';
			cout << "Происхождение: " << note[i].proisxozd.str << '\n';
			cout << "Наличие: " << note[i].nalichie.str << '\n';
		}
	}
	cout << "\n\n";
}
