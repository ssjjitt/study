#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>
using namespace std;

#define str_len 40                                
#define size 8
string A = "file2.txt"; // файл который будет использоваться
char str[512];

// структура
struct Trains
{
	char name[str_len];	// 
	int num;
	int time;
};

struct Trains list_of_trains[size], free_train, help_train;
int currsize = 0;

void enter_new_tr();
void del_tr(int d);
void out_tr();
void write_file_tr();
void sorting();
void read_file_tr();

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 1, d;

	while (choice != 0)
	{
		cout << " \n1. Новая запись\n2. Удалить запись\n3. Вывести запись в консоль\n4. Запись в файл\n5. Чтение из файла\n6. Сортировка\n0. Завершить работу\n(Введите выбор) ";
		cin >> choice;
		switch (choice)
		{
		case(1):
			enter_new_tr();
			break;

		case(2):
			cout << " Номер строки, которую надо удалить(для удаления всех строк введите -1): ";
			cin >> d;
			del_tr(d);
			break;

		case(3):
			out_tr();
			break;

		case(4):
			write_file_tr();
			break;

		case(5):
			read_file_tr();
			break;

		case(6):
			sorting();
			break;

		default:
			break;
		}
	}
}
// функция ввода
void enter_new_tr()
{
	int num;

	do
	{
		cout << "Введите количество поездов (не более " << size << "): ";
		cin >> num;
	} while (num < 1 || num > size);
	fflush(stdin);
	for (int i = 0; i < num; i++)
	{
		cout << "Запись №" << currsize + 1 << endl;
		cout << "Введите названия пункта назначения" << endl;
		cin >> list_of_trains[currsize].name;
		cout << "Введите номер поезда" << endl;
		cin >> list_of_trains[currsize].num;
		cout << "Введите время отправления в формате ЧЧММ" << endl;
		cin >> list_of_trains[currsize].time;
		currsize++;
	}

}
// для удаления
void del_tr(int d)
{
	if (d == -1)
	{
		for (int i = 0; i < size; i++)
		{
			list_of_trains[i] = free_train;
		}
		currsize = 0;
	}
	else
	{
		for (int i = d - 1; i < currsize; i++)
		{
			list_of_trains[i] = list_of_trains[i + 1];
		}
		currsize--;
	}
}
// функция вывода после введенного времени
void out_tr()
{
	int t, q = 0;
	cout << "Введите время: ";
	cin >> t;
	for (int i = 0; i < currsize; i++)
	{
		if (list_of_trains[i].time >= t)
		{
			cout << " Запись №" << i + 1 << " | название пункта назначения - " << list_of_trains[i].name << " | номер поезда - " << list_of_trains[i].num << " | время отправления - " << list_of_trains[i].time << endl;
			q++;
		}
	}
	if (q == 0) cout << "Таких поездов нет" << endl;
}
// запись в файл информации
void write_file_tr()
{
	ofstream fAout(A);
	if (fAout.is_open())
	{
		for (int i = 0; i < currsize; i++)
		{
			fAout << list_of_trains[i].name << endl;;
			fAout << list_of_trains[i].num << endl;;
			fAout << list_of_trains[i].time << endl;;
		}
	}
	else
	{
		cout << " Невозможно открыть файл!" << endl;
	}
	fAout.close();
}
// чтение файла
void read_file_tr()
{
	del_tr(-1);
	char str2[200], str3[200];
	ifstream fAin(A);
	if (fAin.is_open())
	{
		while (true)
		{
			fAin.getline(list_of_trains[currsize].name, sizeof(list_of_trains[currsize].name));
			fAin.getline(str2, sizeof(str2));
			fAin.getline(str3, sizeof(str3));
			if (fAin.eof() != 0) break;
			list_of_trains[currsize].num = atoi(str2);
			list_of_trains[currsize].time = atoi(str3);
			currsize++;
		}
	}
	else
	{
		cout << " Невозможно открыть файл!" << endl;
	}
	fAin.close();
}
// сортировка
void sorting()
{
	int q, i;
	for (i = 0; i < currsize - 1; i++)
	{
		q = (strlen(list_of_trains[i].name) > strlen(list_of_trains[i + 1].name)) ? strlen(list_of_trains[i + 1].name) : strlen(list_of_trains[i].name);
		for (int j = 0; j < q; j++)
		{
			if (list_of_trains[i].name[j] < list_of_trains[i + 1].name[j]) break;
			if (list_of_trains[i].name[j] > list_of_trains[i + 1].name[j])
			{
				help_train = list_of_trains[i + 1];
				list_of_trains[i + 1] = list_of_trains[i];
				list_of_trains[i] = help_train;
				i = -1;
				break;
			}
		}
	}
}