// Ломбард. База хранимых товаров и недвижимости: анкетные данные клиента, наименование товара, оценочная стоимость; сумма, выданная под залог, дата сдачи, срок хранения. Выбор по наименованию товара. 
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;
// объявляем структуру
struct Clients
{
	string fio;	// фамилия клиента гостиницы
	string nameProduct;	// Наименование товара
	string access; // оценочная стоимость
	string summaZalog; // сумма выданная под залог
	string dateSdachi; // Дата сдачи 
	string store; // срок хранения
};
Clients clients[20];

void output();
void input();
void find();
void del();


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	int choice;

	do
	{
		cout << "\n1.Ввод данных с клавиатуры и запись в файл\n";
		cout << "2.Вывод данных из файла в консольное окно\n";
		cout << "3.Поиск по наименованию товара\n";
		cout << "4.Удаление заданной структурированной переменной\n";
		cout << "0.Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		switch (choice)
		{
		case 1: input();  break;
		case 2: output(); break;
		case 3: find(); break;
		case 4: del(); break;
		case 0: exit(0);  break;
		}
	} while (choice != 0);
}

// функция для ввода и записи в файл

void input()
{
	int num;
	do {
		cout << "Введите количество клиентов (не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);

	ofstream file1("information.txt");

	for (int i = 0; i < num; i++)
	{
		cout << "\tКлиент №" << i + 1 << endl;
		cout << "\nФИО клиента:\n";
		cin >> clients[i].fio;
		file1 << "\tКлиент №" << i + 1 << "\n";
		file1 << clients[i].fio;
		file1 << "\n";
		cout << "\nНаименование товара:\n";
		cin >> clients[i].nameProduct;
		file1 << clients[i].nameProduct;
		file1 << "\n";
		cout << "\nОценочная стоимость:\n";
		cin >> clients[i].access;
		file1 << clients[i].access;
		file1 << "\n";
		cout << "\nСумма выданная под залог:\n";
		cin >> clients[i].summaZalog;
		file1 << clients[i].summaZalog;
		file1 << "\n";
		cout << "\nДата сдачи:\n";
		cin >> clients[i].dateSdachi;
		file1 << clients[i].dateSdachi;
		file1 << "\n";
		cout << "\nСрок хранения:\n";
		cin >> clients[i].store;
		file1 << clients[i].store;
		file1 << "\n";
		cout << "\n\n";
	}
	file1.close();
}

// функция для вывода в консоль

void output()
{
	int ClientNum;
	cout << "Введите номер клиента, которого вы хотите вывести:\n";
	cin >> ClientNum;
	int i = ClientNum - 1;
	cout << "\tКлиент №" << ClientNum << '\n';
	cout << "ФИО: " << clients[i].fio << '\n';
	cout << "Наименование товара: " << clients[i].nameProduct << '\n';
	cout << "оценочная стоимость: " << clients[i].access << '\n';
	cout << "сумма выданная под залог: " << clients[i].summaZalog << '\n';
	cout << "Дата сдачи: " << clients[i].dateSdachi << "\n";
	cout << "Срок хранения: " << clients[i].store << "\n\n\n";
}

// функция для удаления данных о клиенте

void del()
{
	int ClientNum;
	cout << "Введите порядковый номер клиента, информацию о котором Вы хотите удалить:\n";
	cin >> ClientNum;
	cout << '\n';
	int i = ClientNum - 1;
	clients[i].fio = ' ';
	clients[i].nameProduct = ' ';
	clients[i].access = ' ';
	clients[i].summaZalog = ' ';
	clients[i].dateSdachi = ' ';
	clients[i].store = ' ';
	cout << '\n';
}

// функция для поиска клиента

void find()
{
	string Search;
	cout << "Введите наименование товара, по которому искать:";
	cin >> Search;
	for (int i = 0; i < 20; i++)
	{
		if (Search == clients[i].nameProduct)
		{
			cout << "\tКлиент №" << i + 1 << '\n';
			cout << "ФИО: " << clients[i].fio << '\n';
			cout << "Наименование товара: " << clients[i].nameProduct << '\n';
			cout << "оценочная стоимость: " << clients[i].access << '\n';
			cout << "сумма выданная под залог: " << clients[i].summaZalog << '\n';
			cout << "Дата сдачи: " << clients[i].dateSdachi << "\n";
			cout << "Срок хранения: " << clients[i].store << "\n\n\n";
		}
	}
	cout << "\n\n";
}

