// вариант 2 номер 2
// Вокзал.Номер поезда, пункт назначения, дни следования, время прибытия, время отправления.Выбор по пункту назначения.

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

void output();
void input();
void find();
void del();

union all_trains		// объединение
{
	char str[50];
};

struct trains
{
	all_trains number;
	all_trains timeOut;
	all_trains timeIn;
	all_trains destination;
	all_trains days;
};

trains train[20];		// массив структур

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
			<< "\n2 - вывод информации о поезде на экран"
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
		cout << "Введите количество поездов (не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		cout << "\nНомер поезда:\n";
		cin >> train[i].number.str;
		file1 << "\t№" << train[i].number.str << "\n";
		file1 << "\n";

		cout << "\nДни следования:\n";
		cin >> train[i].days.str;
		file1 << train[i].days.str;
		file1 << "\n";

		cout << "\nВремя прибытия на платформу(ЧЧ.ММ):\n";
		cin >> train[i].timeIn.str;
		file1 << train[i].timeIn.str;
		file1 << "\n";

		cout << "\nВремя отправления(ЧЧ.ММ)\n";
		cin >> train[i].timeOut.str;
		file1 << train[i].timeOut.str;
		file1 << "\n";

		cout << "\nПункт назначения:\n";
		cin >> train[i].destination.str;
		file1 << train[i].destination.str;
		file1 << "\n";
	}
	file1.close();
}

// функция для вывода в консоль
void output()
{
	int num;
	cout << "Введите номер поезда по счету, которого вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	cout << "\t№" << train[i].number.str << '\n';
	cout << "Дни следования: " << train[i].days.str << '\n';
	cout << "Время прибытия: " << train[i].timeIn.str << '\n';
	cout << "Время отправления: " << train[i].timeOut.str << '\n';
	cout << "Пункт назначения: " << train[i].destination.str << '\n';
	
}

// функция для поиска 

void find()
{
	string destinationSearch;
	cout << "Введите пункт назначения, по которому искать:";
	cin >> destinationSearch;
	for (int i = 0; i < 20; i++)
	{
		if (destinationSearch == train[i].destination.str)			// если введенный пункт совпадает с одним из пунктов массивов структур
		{
			cout << "\t№" << train[i].number.str << '\n';
			cout << "Дни следования: " << train[i].days.str << '\n';
			cout << "Время прибытия: " << train[i].timeIn.str << '\n';
			cout << "Время отправления: " << train[i].timeOut.str << '\n';
			cout << "Пункт назначения: " << train[i].destination.str << '\n';
		}
	}
	cout << "\n\n";
}