// Список клиентов гостиницы. Паспортные данные,  даты приезда и отъезда, номер, тип размещения (люкс, одноместный, двухместный, трехместный, апартаменты). Поиск гостя по фамилии. 
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;
// объявляем структуру
struct HotelClients
{
	string fio;	// фамилия клиента гостиницы
	string passNumber;	// паспортные данные
	string dateIn; // дата приезда
	string dateOut; // дата отъезда
	string room; // номер 
	string typeRoom; // тип размещения
};
HotelClients clients[20];

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
		cout << "3.Поиск по фамилии\n";
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
		cout << "Введите количество клиентов гостиницы (не более 20)";
		cin >> num;
	} while (num < 1 || num > 20);

	fflush(stdin);
	
	ofstream file1("information.txt");
	
	for (int i = 0; i < num; i++)
	{
		cout << "\tКлиент №" << i + 1 << endl;
		cout << "\nВведите ФИО клиента:\n";
		cin >> clients[i].fio;
		file1 << "\tКлиент №" << i + 1 << "\n";
		file1 <<  clients[i].fio;
		file1 << "\n";
		cout << "\nВведите номер паспорта:\n";
		cin >> clients[i].passNumber;
		file1 << clients[i].passNumber;
		file1 << "\n";
		cout << "\nВведите дату приезда:\n";
		cin >> clients[i].dateIn;
		file1 << clients[i].dateIn;
		file1 << "\n";
		cout << "\nВведите дату отъезда:\n";
		cin >> clients[i].dateOut;
		file1 << clients[i].dateOut;
		file1 << "\n";
		cout << "\nВведите комнату:\n";
		cin >> clients[i].room;
		file1 << clients[i].room;
		file1 << "\n";
		cout << "\nВведите тип комнаты:\n";
		cin >> clients[i].typeRoom;
		file1 << clients[i].typeRoom;
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
	cout << "Паспорт: " << clients[i].passNumber << '\n';
	cout << "Дата приезда: " << clients[i].dateIn << '\n';
	cout << "Дата отъезда: " << clients[i].dateOut << '\n';
	cout << "Номер: " << clients[i].room << "\n";
	cout << "Тип номера: " << clients[i].typeRoom << "\n\n\n";
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
	clients[i].passNumber = ' ';
	clients[i].dateIn = ' ';
	clients[i].dateOut = ' ';
	clients[i].room = ' ';
	clients[i].typeRoom = ' ';
	cout << '\n';
}

// функция для поиска клиента

void find()
{
	string fioSearch;
	cout << "Введите фамилию искомого клиента:";
	cin >> fioSearch;
	for (int i = 0; i < 20; i++)
	{
		if (fioSearch == clients[i].fio)
		{
			cout << "\tКлиент №" << i + 1 << '\n';
			cout << "ФИО: " << clients[i].fio << '\n';
			cout << "Паспорт: " << clients[i].passNumber << '\n';
			cout << "Дата приезда: " << clients[i].dateIn << '\n';
			cout << "Дата отъезда: " << clients[i].dateOut << '\n';
			cout << "Номер: " << clients[i].room << "\n";
			cout << "Тип номера: " << clients[i].typeRoom << "\n\n\n";
		}
	}
	cout << "\n\n";
}

