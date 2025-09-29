// Преподаватели. Фамилия преподавателя, название экзамена, дата экзамена. Выбор по дате экзамена. Дату экзамена реализовать с помощью битового поля.

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
	math = 1,		// индексацию установим в единицу
	oaip,
	trpo,
	sd
};
// структура
struct notebooks {
	string fio;
	notebook exam;		// из перечисоения
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
			<< "\n3 - удаление информации"
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
	int day = NULL, month = NULL, year = NULL, exam = NULL;
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

		cout << "\nДата: \n";
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

		cout << endl << "Предмет: 1 - матанализ, 2 - оаип, 3 - трпо, 4 - сд\n";
		cin >> exam;
		note[i].exam = (notebook)exam;		// присваиваем из перечисления
		switch (note[i].exam)
		{
		case notebook::math:
			file1 << "матанализ";
			break;
		case notebook::oaip:
			file1 << "оаип";
			break;
		case notebook::trpo:
			file1 << "трпо";
			break;
		case notebook::sd:
			file1 << "сд";
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
		cout << "информации № " << i + 1 << " нет";
	}
	else {
		cout << "\tРаботник №" << num << '\n';
		cout << "ФИО: " << note[i].fio << '\n';
		cout << "Дата: " << note[i].datee.day << '.' << note[i].datee.month << "." << note[i].datee.year << "\n";
		cout << "Предмет: ";
		switch (note[i].exam)
		{
		case 1: cout << "матанализ \n";
			break;
		case 2: cout << "оаип \n";
			break;
		case 3: cout << "трпо \n";
			break;
		case 4: cout << "сд \n";
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
	note[i].datee.day = NULL;
	note[i].datee.month = NULL;
	note[i].datee.year = NULL;
	note[i].exam;
	cout << '\n';
}

// функция для поиска

void find()
{
	int search;
	cout << "Введите год:";
	cin >> search;
	for (int i = 0; i < 20; i++)
	{
		if (search == note[i].datee.year)
		{
			cout << "\t№" << i + 1 << '\n';
			cout << "ФИО: " << note[i].fio << '\n';
			cout << "Дата рождения: " << note[i].datee.day << '.' << note[i].datee.month << "." << note[i].datee.year << "\n";
			cout << "Должность: " << note[i].exam << '\n';
		}
	}
	cout << "\n\n";
}


