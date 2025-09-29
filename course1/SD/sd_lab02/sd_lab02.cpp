#include <iostream>                    
# define str_len 40                               
# define size 40 
using namespace std;
void del();
void enter_new();
void change();
void out();
struct Client
{
	char fio[str_len];
	char telephone[str_len];
	char email[str_len];
	char product[str_len];
	int numProduct;
	char dateSale[str_len];
	char dateDelivery[str_len];
};
struct Client list_of_clients[size];
struct Client bad;
int current_size = 0; int choice;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
	do
	{
		switch (choice)
		{
		case 1:  del();	break;
		case 2:  enter_new();  break;
		case 3:  change();  break;
		case 4:  out();	break;
		}
	} while (choice != 5);
}
void enter_new()
{
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Фамилия клиента: " << endl;
		cin >> list_of_clients[current_size].fio;
		cout << "Номер телефона: " << endl;
		cin >> list_of_clients[current_size].telephone;
		cout << "Электронная почта: " << endl;
		cin >> list_of_clients[current_size].email;
		cout << "Товар: " << endl;
		cin >> list_of_clients[current_size].product;
		cout << "Количество товаров: " << endl;
		cin >> list_of_clients[current_size].numProduct;
		cout << "Дата продажи: " << endl;
		cin >> list_of_clients[current_size].dateSale;
		cout << "Дата доставки: " << endl;
		cin >> list_of_clients[current_size].dateDelivery;
		current_size++;
	}
	else
		cout << "Введено максимальное кол-во строк";
	cout << endl << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
}
void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++)
			list_of_clients[de1] = list_of_clients[de1 + 1];
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++)
			list_of_clients[i] = bad;
	cout << endl << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
}
void change()
{
	int n, per;
	cout << "\nВведите номер строки" << endl; 	cin >> n;
	do
	{
		cout << "Введите: " << endl;
		cout << "1-для изменения фамилии" << endl;
		cout << "2-для изменения номера телефона" << endl;
		cout << "3-для изменения номера почты" << endl;
		cout << "4-для изменения номера товара" << endl;
		cout << "5-для изменения количества товаров" << endl;
		cout << "6-для изменения даты продажи" << endl;
		cout << "7-для изменения даты доставки" << endl;
		cout << "0-конец\n";
		cin >> per;
		switch (per)
		{
		case 1: cout << "Новая фамилия";
			cin >> list_of_clients[n - 1].fio;   break;
		case 2: cout << "Новый номер телефона";
			cin >> list_of_clients[n - 1].telephone; break;
		case 3: cout << "Новая почта";
			cin >> list_of_clients[n - 1].email; break;
		case 4: cout << "Новый товар";
			cin >> list_of_clients[n - 1].product; break;
		case 5: cout << "Новое количество товаров";
			cin >> list_of_clients[n - 1].numProduct; break;
		case 6: cout << "Новая дата продажи";
			cin >> list_of_clients[n - 1].dateSale; break;
		case 7: cout << "Новая дата доставки";
			cin >> list_of_clients[n - 1].dateDelivery; break;
		}

	} while (per != 0);
	cout << endl << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
}
void out()
{
	int sw, n;
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "Номер выводимой строки " << endl;   cin >> n;  cout << endl;
		cout << "Фамилия ";
		cout << list_of_clients[n - 1].fio << endl;
		cout << "Телефон ";
		cout << list_of_clients[n - 1].telephone << endl;
		cout << "Почта ";
		cout << list_of_clients[n - 1].email << endl;
		cout << "Товар ";
		cout << list_of_clients[n - 1].product << endl;
		cout << "Количество товаров ";
		cout << list_of_clients[n - 1].numProduct << endl;
		cout << "Дата продажи ";
		cout << list_of_clients[n - 1].dateSale << endl;
		cout << "Дата доставки ";
		cout << list_of_clients[n - 1].dateDelivery << endl;
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "Фамилия ";
			cout << list_of_clients[i].fio << endl;
			cout << "Телефон ";
			cout << list_of_clients[i].telephone << endl;
			cout << "Почта ";
			cout << list_of_clients[i].email << endl;
			cout << "Товар ";
			cout << list_of_clients[i].product << endl;
			cout << "Количество товаров ";
			cout << list_of_clients[i].numProduct << endl;
			cout << "Дата продажи ";
			cout << list_of_clients[i].dateSale << endl;
			cout << "Дата доставки ";
			cout << list_of_clients[i].dateDelivery << endl;
		}
	}
	cout << endl << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choice;
}