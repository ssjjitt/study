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
enum type {
	pokupka = 1,		// индексацию установим в единицу
	krazha,
	podarok
};
// структура
struct library {
	string author;
	string book;
	string isdatelstvo;
	string razdel;
	type typee;		// из перечисоения
	date datee;			// из битовых полей
};

library librarys[20];

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
	int day = NULL, month = NULL, year = NULL, typee = NULL;
	int num;
	do {
		cout << "Введите количество книг (не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		file1 << "\n";
		cout << "\tКнига №" << i + 1 << endl;

		cout << "\nАвтор:\n";
		cin >> librarys[i].author;
		file1 << "\t№" << i + 1 << "\n";
		file1 << librarys[i].author;
		file1 << "\n";

		cout << "\nКнига:\n";
		cin >> librarys[i].book;
		file1 << librarys[i].book;
		file1 << "\n";

		cout << "\nИздательство: \n";
		cin >> librarys[i].isdatelstvo;
		file1 << librarys[i].isdatelstvo;
		file1 << "\n";

		cout << "\nРаздел: \n";
		cin >> librarys[i].razdel;
		file1 << librarys[i].razdel;
		file1 << "\n";

		cout << "\nВведите дату выпуска: \n";
		cout << "день: ";
		cin >> day;
		cout << "месяц: ";
		cin >> month;
		cout << "год: ";
		cin >> year;
		librarys[i].datee.day = day;		// присваем введенные числа переменным из битовых полей
		librarys[i].datee.month = month;
		librarys[i].datee.year = year;
		file1 << day << "." << month << "." << year << "\n";
		cout << "\n";

		cout << endl << "Происхождение: покупка - 1, кража - 2, подарок - 3\n";
		cin >> typee;
		librarys[i].typee = (type)typee;		// присваиваем из перечисления
		switch (librarys[i].typee)
		{
		case type::pokupka:				// case type::male то же самое, что и case 1
			file1 << "покупка";
			break;
		case type::krazha:		// то же самое, что и case 2
			file1 << "кража";
		case type::podarok:		// то же самое, что и case 3
			file1 << "подарок";
			break;
		}
	}
	file1.close();
}

// функция для вывода в консоль
void output()
{
	int num;
	cout << "Введите номер Горожанина, которого вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	if (librarys[i].datee.day == NULL) {									// если день рождения равен нулю
		cout << "информации о горожанине № " << i + 1 << " нет";
	}
	else {
		cout << "\tКнига №" << num << '\n';
		cout << "Автор: " << librarys[i].author << '\n';
		cout << "Книга: " << librarys[i].book << '\n';
		cout << "Издательство: " << librarys[i].isdatelstvo << '\n';
		cout << "Раздел: " << librarys[i].razdel << '\n';
		cout << "Дата выпуска: " << librarys[i].datee.day << '.' << librarys[i].datee.month << "." << librarys[i].datee.year << "\n";
		cout << "Происхождение: ";
		switch (librarys[i].typee)
		{
		case 1: cout << " покупка \n";
			break;
		case 2: cout << " кража \n";
			break;
		case 3: cout << " подарок \n";
			break;
		default:
			break;
		}
	}
}

// функция для удаления данных о Горожанине

void del()
{
	int num;
	cout << "Введите порядковый номер книги, информацию о которой вы хотите удалить:\n";
	cin >> num;
	cout << '\n';
	int i = num - 1;
	librarys[i].author = ' ';
	librarys[i].book = ' ';
	librarys[i].isdatelstvo = ' ';
	librarys[i].datee.day = NULL;
	librarys[i].datee.month = NULL;
	librarys[i].datee.year = NULL;
	librarys[i].typee;
	cout << '\n';
}

// функция для поиска 

void find()
{
	int yearSearch;
	cout << "Введите год, по которому искать:";
	cin >> yearSearch;
	for (int i = 0; i < 20; i++)
	{
		if (yearSearch == librarys[i].datee.year)			// если введенный год совпадает с годом 
		{
			cout << "\tКнига №" << i + 1 << '\n';
			cout << "Автор: " << librarys[i].author << '\n';
			cout << "Книга: " << librarys[i].book << '\n';
			cout << "Издательство: " << librarys[i].isdatelstvo << '\n';
			cout << "Раздел: " << librarys[i].razdel << '\n';
			cout << "Дата выпуска: " << librarys[i].datee.day << '.' << librarys[i].datee.month << "." << librarys[i].datee.year << "\n";
			cout << "Происхождение: " << librarys[i].typee << '\n';
		}
	}
	cout << "\n\n";
}


