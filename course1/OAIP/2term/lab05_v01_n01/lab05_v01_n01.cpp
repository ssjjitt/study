// вариант 1 номер 1
//Отдел кадров. Ф.И.О. работника, образование, специальность, подразделение, должность, оклад, дата поступления на предприятие. 
//Выбор по стражу работы. Даты реализовать с помощью битового поля, должность  с помощью перечисления.
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
enum speciality {
	test = 1,		// индексацию установим в единицу
	frontend,
	backend,
	fullstack
};
// структура
struct workers {
	string fio;
	string education;
	speciality spec;		// из перечисоения
	string subdivision;
	string salary;
	date datee;			// из битовых полей
};

workers work[20];

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
		cout << "\tРаботник №" << i + 1 << endl;

		cout << "\nФИО:\n";
		cin >> work[i].fio;
		file1 << "\t№" << i + 1 << "\n";
		file1 << work[i].fio;
		file1 << "\n";

		cout << "\nОбразование:\n";
		cin >> work[i].education;
		file1 << work[i].education;
		file1 << "\n";

		cout << "\nПодразделение:\n";
		cin >> work[i].subdivision;
		file1 << work[i].subdivision;
		file1 << "\n";

		cout << "\nОклад:\n";
		cin >> work[i].salary;
		file1 << work[i].salary;
		file1 << "\n";

		cout << "\nДата поступления на предприятие: \n";
		cout << "день: ";
		cin >> day;
		cout << "месяц: ";
		cin >> month;
		cout << "год: ";
		cin >> year;
		work[i].datee.day = day;		// присваем введенные числа переменным из битовых полей
		work[i].datee.month = month;
		work[i].datee.year = year;
		file1 << day << "." << month << "." << year << "\n";
		cout << "\n";

		cout << endl << "Должность: 1 - тестировщик, 2 - фронтенд, 3 - бэкенд, 4 - фуллстак\n";
		cin >> spec;
		work[i].spec = (speciality)spec;		// присваиваем из перечисления
		switch (work[i].spec)
		{
		case speciality::test:				
			file1 << "тестировщик";
			break;
		case speciality::frontend:		
			file1 << "фронтенд";
			break;
		case speciality::backend:				
			file1 << "бэкенд";
			break;
		case speciality::fullstack:				
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
	cout << "Введите номер работника, которого вы хотите вывести:\n";
	cin >> num;
	int i = num - 1;
	if (work[i].datee.day == NULL) {									
		cout << "информации о работнике № " << i + 1 << " нет";
	}
	else {
		cout << "\tРаботник №" << num << '\n';
		cout << "ФИО: " << work[i].fio << '\n';
		cout << "Образование: " << work[i].education << '\n';
		cout << "Подразделение" << work[i].subdivision << "\n";
		cout << "Оклад" << work[i].salary << "\n";
		cout << "Дата поступления: " << work[i].datee.day << '.' << work[i].datee.month << "." << work[i].datee.year << "\n";
		cout << "Должность: ";
		switch (work[i].spec)
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
	cout << "Введите порядковый номер работника, информацию о котором Вы хотите удалить:\n";
	cin >> num;
	cout << '\n';
	int i = num - 1;
	work[i].fio = ' ';
	work[i].education = ' ';
	work[i].subdivision = ' ';
	work[i].salary = ' ';
	work[i].datee.day = NULL;
	work[i].datee.month = NULL;
	work[i].datee.year = NULL;
	work[i].spec;
	cout << '\n';
}

// функция для поиска

void find()
{
	int yearSearch;
	cout << "Введите год поступления искомого работника:";
	cin >> yearSearch;
	for (int i = 0; i < 20; i++)
	{
		if (yearSearch == work[i].datee.year)			
		{
			cout << "\tРаботник №" << i + 1 << '\n';
			cout << "ФИО: " << work[i].fio << '\n';
			cout << "Образование: " << work[i].education << '\n';
			cout << "Подразделение: " << work[i].subdivision << '\n';
			cout << "Оклад: " << work[i].salary << '\n';
			cout << "Дата поступления: " << work[i].datee.day << '.' << work[i].datee.month << "." << work[i].datee.year << "\n";
			cout << "Должность: " << work[i].spec << '\n';
		}
	}
	cout << "\n\n";
}

