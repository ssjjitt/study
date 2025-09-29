// чтение и вывод из файла, добавление элементов в массив
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
# define str_len 40                               
# define size 40 

using namespace std;

struct Initial {
	char fio[str_len];
	char telephone[str_len];
	char email[str_len];
	char product[str_len];
	int numProduct;
	char dateSale[str_len];
	char dateDelivery[str_len];
};

struct Initial list_of_clients[size];
struct Initial bad;
int current_size = 0;

void ReadingData(Initial* (&d), string fileName)
{
	ifstream reading(fileName);
	int n;
	char ch[20];
	cout << "---------------------------------------" << endl;
	for (int i = 0; i < current_size; i++)
	{
		if (list_of_clients[i].numProduct == 0) 
			break;
		else {
			cout << "Фамилия ";
			reading >> list_of_clients[i].fio;
			cout << list_of_clients[i].fio << endl;
			cout << "Телефон ";
			reading >> list_of_clients[i].telephone;
			cout << list_of_clients[i].telephone << endl;
			cout << "Почта ";
			reading >> list_of_clients[i].email;
			cout << list_of_clients[i].email << endl;
			cout << "Товар ";
			reading >> list_of_clients[i].product;
			cout << list_of_clients[i].product << endl;
			cout << "Количество товаров ";
			reading >> list_of_clients[i].numProduct;
			cout << list_of_clients[i].numProduct << endl;
			cout << "Дата продажи ";
			reading >> list_of_clients[i].dateSale;
			cout << list_of_clients[i].dateSale << endl;
			cout << "Дата доставки ";
			reading >> list_of_clients[i].dateDelivery;
			cout << list_of_clients[i].dateDelivery << endl;
			cout << "---------------------------------------" << endl;
		}
	}
	reading.close();
}

void ReadFromFile(Initial* (&d), int readsize, string fileName) {
	ifstream read(fileName);
	if (read) {
		for (int i = 0; i < readsize; i++) {
			if (current_size < size)
			{
				read >> list_of_clients[current_size].fio;
				read >> list_of_clients[current_size].telephone;
				read >> list_of_clients[current_size].email;
				read >> list_of_clients[current_size].product;
				read >> list_of_clients[current_size].numProduct;
				read >> list_of_clients[current_size].dateSale;
				read >> list_of_clients[current_size].dateDelivery;
				current_size++;
			}
		}
	}
	else
		cout << "Ошибка открытия файла!" << endl;
	read.close();
}

void SavingData(Initial* d, string fileName)
{
	ofstream record(fileName, ios::app);
	if (record) {
		cout << "Ввод информации" << endl;
		if (current_size < size)
		{
			cout << "Строка номер ";
			cout << current_size + 1;
			cout << endl << "Фамилия клиента: " << endl;
			cin >> list_of_clients[current_size].fio;
			record << list_of_clients[current_size].fio << "\n";
			cout << "Номер телефона: " << endl;
			cin >> list_of_clients[current_size].telephone;
			record << list_of_clients[current_size].telephone << "\n";
			cout << "Электронная почта: " << endl;
			cin >> list_of_clients[current_size].email;
			record << list_of_clients[current_size].email << "\n";
			cout << "Товар: " << endl;
			cin >> list_of_clients[current_size].product;
			record << list_of_clients[current_size].product << "\n";
			cout << "Количество товаров: " << endl;
			cin >> list_of_clients[current_size].numProduct;
			record << list_of_clients[current_size].numProduct << "\n";
			cout << "Дата продажи: " << endl;
			cin >> list_of_clients[current_size].dateSale;
			record << list_of_clients[current_size].dateSale << "\n";
			cout << "Дата доставки: " << endl;
			cin >> list_of_clients[current_size].dateDelivery;
			record << list_of_clients[current_size].dateDelivery << "\n";
			current_size++;
		}
		else
			cout << "Введено максимальное кол-во строк";
	}
	else
		cout << "Ошибка открытия файла!" << endl;
	record.close();
}

void delInFile(Initial* (&d), string fileName) {
	ofstream file(fileName, ios_base::trunc);
}

void DeleteData(int arrsize)
{
	int d;
	cout << "\nНомер строки, которую надо удалить: ";
	cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < size; de1++)
		{
			list_of_clients[de1] = list_of_clients[de1 + 1];
		}
		arrsize--;



	}
	if (d == 99)
	{
		for (int i = 0; i < size; i++)
			list_of_clients[i] = bad;
		arrsize = 0;

	}
}

void DataChange(Initial* (&d))

{
	int k;
	cout << "введите номер клиента, информацию о котором нужно изменить";
	cin >> k;
	cout << endl << "Фамилия клиента: " << endl;
	cin >> list_of_clients[k].fio;
	cout << "Номер телефона: " << endl;
	cin >> list_of_clients[k].telephone;
	cout << "Электронная почта: " << endl;
	cin >> list_of_clients[k].email;
	cout << "Товар: " << endl;
	cin >> list_of_clients[k].product;
	cout << "Количество товаров: " << endl;
	cin >> list_of_clients[k].numProduct;
	cout << "Дата продажи: " << endl;
	cin >> list_of_clients[k].dateSale;
	cout << "Дата доставки: " << endl;
	cin >> list_of_clients[k].dateDelivery;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	int filevar = NULL, var = NULL, isize1 = 0, isize2 = 0;
	string fileName;
	Initial* arr = new Initial[size];
	do {

		cout << "ФАЙЛ: \n 1-ваше имя файла\n 2-по стандарту\n 0 - выход\n";
		cin >> filevar;
		system("cls");
		switch (filevar)
		{
		case 1:
		{
			cout << "введите ваше имя файла\n";
			cin >> fileName;
			do {
				cout << "1-вывод в консоль" << endl;
				cout << "2-для ввода новой записи и записи её в файл" << endl;
				cout << "3-изменение информации" << endl;
				cout << "4-чтение из файла" << endl;
				cout << "5-удаление всего содержимого файла" << endl;
				cout << "6-частичное удаление информации" << endl;
				cout << "0-для выхода" << endl;
				cin >> var;
				switch (var)
				{
				case 1: ReadingData(arr, fileName); break;
				case 2: {
					SavingData(arr, fileName);
					isize1++;
					break;
				}
				case 3: DataChange(arr); break;
				case 4: ReadFromFile(arr, size, fileName); break;
				case 5: delInFile(arr, fileName); break;
				case 6: DeleteData(isize1); break;
				default:
					break;
				}
			} while (var != 0);
		}
		case 2:
		{
			do
			{
				cout << "1-вывод в консоль" << endl;
				cout << "2-для ввода новой записи и записи её в файл" << endl;
				cout << "3-изменение ифнормации" << endl;
				cout << "4-чтение из файла" << endl;
				cout << "5-удаление всего содержимого файла" << endl;
				cout << "6-частичное удаление информации" << endl;
				cout << "0-для выхода" << endl;
				cin >> var;
				switch (var)
				{
				case 1: ReadingData(arr, "Output.txt"); break;
				case 2: {
					SavingData(arr, "Output.txt");
					isize2++;
					break;
				}
				case 3: DataChange(arr);  break;
				case 4: ReadFromFile(arr, size, "Output.txt"); break;
				case 5: delInFile(arr, "Output.txt"); break;
				case 6: DeleteData(isize2); break;
				default:
					break;
				}
			} while (var != 0);
		}
		default:
			break;
		}
	} while (filevar != 0);
}
	
