// Записная книжка.Ф.И.О, дата рождения, адрес, телефон, место работы или учебы, должность.
// Поиск по фамилии.Дату рождения реализовать с помощью битового поля.
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;
void output();
void input();
void find();
void del();
// битовые поля
struct date {
	unsigned int day : 5;	// 5 бит - 32 числа
	unsigned int month : 4;		// 4 бит - 16
	unsigned int year : 11;		// 11 бит - 2048
};
// перечисление
enum notebook {
	test = 1,		// индексацию установим в единицу
	frontend,
	backend,
	fullstack
};
// структура
struct notebooks {
	string fio;
	string number;
	notebook spec;		// из перечисоения
	string place;
	date datee;			// из битовых полей
};

notebooks note[20];

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
			<< "\n3 - удаление информации о горожанине"
			<< "\n4 - поиск"
			<< "\n0 - выход из программы\n";
		cin >> choice;


		switch (choice)
		{
		case 1: input();  break;
		case 2: output(); break;
		case 3: del(); break;
		case 4: find(); break;
		case 0: exit(0);  break;
		}
	} while (choice != 0);
}

// функция для ввода и записи в файл

void input()
{
	int day = NULL, month = NULL, year = NULL, spec = NULL;
	int num;
	do {
		cout << "Введите количество(не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		file1 << "\n";
		cout << "\tЗапись №" << i + 1 << endl;

		cout << "\nФИО:\n";
		cin >> note[i].fio;
		file1 << "\t№" << i + 1 << "\n";
		file1 << note[i].fio;
		file1 << "\n";

		cout << "\nТел номер:\n";
		cin >> note[i].number;
		file1 << note[i].number;
		file1 << "\n";

		cout << "\nМесто работы/учебы:\n";
		cin >> note[i].place;
		file1 << note[i].place;
		file1 << "\n";

		cout << "\nДата рождения: \n";
		cout << "день: ";
		cin >> day;
		cout << "месяц: ";
		cin >> month;
		cout << "год: ";
		cin >> year;
		note[i].datee.day = day;		// присваем введенные числа переменным из битовых полей
		note[i].datee.month = month;
		note[i].datee.year = year;
		file1 << day << "." << month << "." << year << "\n";
		cout << "\n";

		cout << endl << "Должность: 1 - тестировщик, 2 - фронтенд, 3 - бэкенд, 4 - фуллстак\n";
		cin >> spec;
		note[i].spec = (notebook)spec;		// присваиваем из перечисления
		switch (note[i].spec)
		{
		case notebook::test:
			file1 << "тестировщик";
			break;
		case notebook::frontend:
			file1 << "фронтенд";
			break;
		case notebook::backend:
			file1 << "бэкенд";
			break;
		case notebook::fullstack:
			file1 << "фуллстак";
			break;
		}
	}
	file1.close();
}

// функция для вывода в консоль
void output()
{
	int num;
	cout << "Введите номер записи, которую вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	if (note[i].datee.day == NULL) {
		cout << "информации о работнике № " << i + 1 << " нет";
	}
	else {
		cout << "\tРаботник №" << num << '\n';
		cout << "ФИО: " << note[i].fio << '\n';
		cout << "Тел номер: " << note[i].number << '\n';
		cout << "Место работы/учебы" << note[i].place << "\n";
		cout << "Дата рождения: " << note[i].datee.day << '.' << note[i].datee.month << "." << note[i].datee.year << "\n";
		cout << "Должность: ";
		switch (note[i].spec)
		{
		case 1: cout << "тестировщик \n";
			break;
		case 2: cout << "фронтенд \n";
			break;
		case 3: cout << "бэкенд \n";
			break;
		case 4: cout << "фуллстак \n";
			break;
		}
	}
}

// функция для удаления данных

void del()
{
	int num;
	cout << "Введите порядковый номер записи, информацию о которой Вы хотите удалить:\n";
	cin >> num;
	cout << '\n';
	int i = num - 1;
	note[i].fio = ' ';
	note[i].number = ' ';
	note[i].place = ' ';
	note[i].datee.day = NULL;
	note[i].datee.month = NULL;
	note[i].datee.year = NULL;
	note[i].spec;
	cout << '\n';
}

// функция для поиска

void find()
{
	string search;
	cout << "Введите фамилию:";
	cin >> search;
	for (int i = 0; i < 20; i++)
	{
		if (search == note[i].fio)
		{
			cout << "\tРаботник №" << i + 1 << '\n';
			cout << "ФИО: " << note[i].fio << '\n';
			cout << "Тел номер: " << note[i].number << '\n';
			cout << "Место работы/учебы: " << note[i].place << '\n';
			cout << "Дата рождения: " << note[i].datee.day << '.' << note[i].datee.month << "." << note[i].datee.year << "\n";
			cout << "Должность: " << note[i].spec << '\n';
		}
	}
	cout << "\n\n";
}


