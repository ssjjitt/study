// вариант 2 номер 1
// Горожанин. Ф.И.О., дата рождения, адрес, пол (м, ж). Выборка по году рождения. Дату рождения организовать с помощью битового поля, пол  с помощью перечисления.

#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;
void output();
void input();
void find();
void del();
// битовые поля
struct birthday{			
	unsigned int day : 5;	// 5 бит - 32 числа
	unsigned int month : 4;		// 4 бит - 16
	unsigned int year : 11;		// 11 бит - 2048
};
// перечисление
enum gender {
	male = 1,		// индексацию установим в единицу
	female
};
// структура
struct citizen {
	string fio;
	string adress;
	gender gend;		// из перечисоения
	birthday birth;			// из битовых полей
};

citizen citizens[20];

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
			<< "\n2 - вывод информации о горожанине на экран"
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
	int day = NULL, month = NULL, year = NULL, gend = NULL;
	int num;
	do {
		cout << "Введите количество горожан (не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		file1 << "\n";
		cout << "\tГорожанин №" << i + 1 << endl;

		cout << "\nФИО:\n";
		cin >> citizens[i].fio;
		file1 << "\t№" << i + 1 << "\n";
		file1 << citizens[i].fio;
		file1 << "\n";

		cout << "\nВведите адрес:\n";
		cin >> citizens[i].adress;
		file1 << citizens[i].adress;
		file1 << "\n";

		cout << "\nВведите дату рождения: \n";
		cout << "день: ";
		cin >> day;
		cout << "месяц: ";
		cin >> month;
		cout << "год: ";
		cin >> year;
		citizens[i].birth.day = day;		// присваем введенные числа переменным из битовых полей
		citizens[i].birth.month = month;
		citizens[i].birth.year = year;
		file1 << day << "." << month << "." << year << "\n";
		cout << "\n";

		cout << endl << "Гендер: мужской - 1, женский - 2\n"; 
		cin >> gend;
		citizens[i].gend = (gender)gend;		// присваиваем из перечисления
		switch (citizens[i].gend)
		{
		case gender::male:				// case gender::male то же самое, что и case 1
			file1 << "мужской";
			break;
		case gender::female:		// то же самое, что и case 2
			file1 << "женский";		
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
	if (citizens[i].birth.day == NULL) {									// если день рождения равен нулю
		cout << "информации о горожанине № " << i + 1 << " нет";
	}
	else {
		cout << "\tГорожанин №" << num << '\n';
		cout << "ФИО: " << citizens[i].fio << '\n';
		cout << "Адрес: " << citizens[i].adress << '\n';
		cout << "Дата рождения: " << citizens[i].birth.day << '.' << citizens[i].birth.month << "." << citizens[i].birth.year << "\n";
		switch (citizens[i].gend)
		{
		case 1: cout << "Пол: мужской \n";
			break;
		case 2: cout << "Пол: женский \n";
			break;
		}
	}
}

// функция для удаления данных о Горожанине

void del()
{
	int num;
	cout << "Введите порядковый номер Горожанина, информацию о котором Вы хотите удалить:\n";
	cin >> num;
	cout << '\n';
	int i = num - 1;
	citizens[i].fio = ' ';
	citizens[i].adress = ' ';
	citizens[i].birth.day = NULL;
	citizens[i].birth.month = NULL;
	citizens[i].birth.year = NULL;
	citizens[i].gend;
	cout << '\n';
}

// функция для поиска Горожанина

void find()
{
	int yearSearch;
	cout << "Введите год искомого Горожанина:";
	cin >> yearSearch;
	for (int i = 0; i < 20; i++)
	{
		if (yearSearch == citizens[i].birth.year)			// если введенный год совпадает с годом горожанина
		{
			cout << "\tГорожанин №" << i + 1 << '\n';
			cout << "ФИО: " << citizens[i].fio << '\n';
			cout << "Адрес: " << citizens[i].adress << '\n';
			cout << "Дата рождения: " << citizens[i].birth.day << '.' << citizens[i].birth.month << "." << citizens[i].birth.year << "\n";
			cout << "Пол: " << citizens[i].gend << '\n';
		}
	}
	cout << "\n\n";
}	

