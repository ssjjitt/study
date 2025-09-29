#include <iostream>
#include <windows.h>
using namespace std;

const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
	char name[NAME_SIZE];	// информационное поле
	char city[CITY_SIZE];	// информационное поле
	Address* next;		// указатель на следующий
	Address* prev;		// указатель на предыдущий
};

// прототипы функций
void insert(Address* e, Address** phead, Address** plast);
Address* setElement();
void outputList(Address** phead, Address** plast);
void delet(char name[NAME_SIZE], Address** phead, Address** plast);
void find(char name[NAME_SIZE], Address** phead);
void writeToFile(Address** phead);
void readFromFile(Address** phead, Address** plast);
void deleteKFirst(Address** phead, Address** plast);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "Rus");
	Address* head = NULL;
	Address* last = NULL;
	short choose = 0;
	cout << "Выберите действие:\n1 — ввод элемента;\n2 — вывод списка;\n3 — удаление элемента;\n4 — поиск элемента;"
		"\n5 — запись в файл;\n6 — вывод из файла;\n7 — удаление первых k элементов;\n8 — выход из программы.\n";
	while (choose != 5)
	{
		char s[80];  int c;
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);

		switch (c)
		{
		case 1:
			insert(setElement(), &head, &last);
			break;
		case 2:
			outputList(&head, &last);
			break;
		case 3:
			char dname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			delet(dname, &head, &last);
			break;
		case 4:
			char fname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
			break;
		case 5:
			writeToFile(&head);
			break;
		case 6:
			readFromFile(&head, &last);
			break;
		case 7:
			deleteKFirst(&head, &last);
			break;
		case 8:
			cout << "До свидания!\n";
			exit(0);
		}
	}
}

void insert(Address* e, Address** phead, Address** plast) //Добавление в конец списка
{
	Address* p = *plast;	// указатель на последний
	if (*plast == NULL)		// если указывает на пустой элемент, то
	{
		e->next = NULL;
		e->prev = NULL;
		*plast = e;			// добавляем
		*phead = e;
		return;
	}
	else
	{
		p->next = e;
		e->next = NULL;
		e->prev = p;
		*plast = e;
	}
}

Address* setElement()      // Создание элемента и ввод его значений с клавиатуры 
{
	Address* temp = new  Address();
	if (!temp)
	{
		cerr << "Ошибка выделения памяти.\n";
		return NULL;
	}
	cout << "Введите имя: ";
	// функции для работы со строками для большей корректности
	cin.getline(temp->name, NAME_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "Введите город: ";
	cin.getline(temp->city, CITY_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	temp->next = NULL;
	temp->prev = NULL;
	return temp;
}

void outputList(Address** phead, Address** plast)      //Вывод списка на экран
{
	Address* t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast)  // Удаление имени 
{
	struct Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name))  break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено.\n" << endl;
	else
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)	
				(*phead)->prev = NULL;		// удаление из начала
			else
				*plast = NULL;
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
				t->next->prev = t->prev;
			else
				*plast = t->prev;
		}
		delete t;
		cout << "Элемент удален.\n" << endl;
	}
}

void find(char name[NAME_SIZE], Address** phead)    // Поиск имени в списке
{
	Address* t = *phead;		// начиная с заголовка
	while (t)		// пока не конец списка
	{
		if (!strcmp(name, t->name)) break;	// сравниваем строки
		t = t->next;		// нас следующий
	}
	if (!t)
		cerr << "Имя не найдено.\n" << endl;
	else
		cout << t->name << ' ' << t->city << endl;		// выводим найденный
}

void writeToFile(Address** phead)       //Запись в файл
{
	struct Address* t = *phead;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist.txt", "wb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	cout << "Сохранение в файл" << endl;
	while (t)
	{
		fwrite(t, sizeof(struct Address), 1, fp);
		t = t->next;
	}
	fclose(fp);
}

void readFromFile(Address** phead, Address** plast)          //Считывание из фай-ла
{
	struct Address* t;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist.txt", "rb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	while (*phead)
	{
		*plast = (*phead)->next;
		delete* phead;
		*phead = *plast;
	}
	*phead = *plast = NULL;
	cout << "Загрузка из файла" << endl;
	while (!feof(fp))
	{
		t = new Address();
		if (!t)
		{
			cerr << "Ошибка выделения памяти" << endl;
			return;
		}
		if (1 != fread(t, sizeof(struct Address), 1, fp)) break;
		insert(t, phead, plast);
	}
	fclose(fp);
}

void deleteKFirst(Address** phead, Address** plast)
{
	Address* t = *phead;
	short k, i = 0;
	cout << "Введите k:\n";
	cin >> k; // количество сиимволов, которые нужно удалить

	for (int i = 0; t; i++)	// цикл для удаления
	{
		if (k)	// пока true
		{
			if (t->next != NULL)		// если след не равен NULL
			{
				t = t->next;		// перемещаемся
				delet(t->prev->name, phead, plast);		// вызываем функцию delet для нашего элемента
			}
			else
			{
				delet(t->name, phead, plast);		// иначе удаляем 
				t = NULL;			// и ставим NULL
			}
			k--;		// уменьшеем количество сиимволов, которые нужно удалить
		}
		else t = t->next;
	}
}