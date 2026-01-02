#include "Header.h"
#include "Lists.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <fstream>

using namespace std;

const char* NML[15] = { "Яглинская", "Пивоваров", "Лупинка", "Петрович", "Полторан",
						"Михедов", "Дубина", "Кашков", "Щипер", "Зданевич",
						"Никитенко", "Жигадло", "Курило", "Нестерова", "Дайтбегова" };

struct AAA
{
	int key;
	char mas[50];
	AAA(int k, char* z)
	{
		key = k;
		strcpy_s(mas, 50, z);
	}
	AAA()
	{
		key = 0;
		strcpy_s(mas, 50, "\0");
	}
};
//-------------------------------
int hf(void* d)
{
	AAA* f = (AAA*)d;
	return f->key;
}
//-------------------------------
void AAA_print(listx::Element* e)
{
	std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / ";
}
//-------------------------------
void foutF(ofstream& f, char* name);

int _tmain(int argc, _TCHAR* argv[])
{
	ofstream input;
	ifstream output;
	setlocale(LC_ALL, "rus");                                                            //Óñòàíîâëåíèå êîäèðîâêè
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	int current_size = 0;                                                                //Переменная, определяющая размер таблицы                                                    
	cout << "Введите размер хеш-таблицы: ";                                       //Сообщение о вводе размера таблицы
	cin >> current_size;                                                                 //Ввод пользователем размера таблицы
	hashTC::Object H = hashTC::create(current_size, hf);
	int choice;
	int k;
	for (;;)
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "5 - заполнение хэш-таблицы из файла" << endl;
		cout << "6 - заполнение файла словами" << endl;
		cout << "0 - выход" << endl;
		cout << "Сделайте выбор" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  exit(0);
			break;
		case 1: H.Scan();
			break;
		case 2: {	  AAA* a = new AAA;                                            //Создание нового элемента списка. Список - элемент таблицы
			char* str = new char[100];                                              //Создание новой строки как данных, хранящихся в поле элемента списка
			cout << "Введите ключи: ";
			cin >> k;                                                              //Ввод ключа, хранящегося в поле элемента списка
			a->key = k;                                                            //Присваивание полю "ключ" списка вводимый ключ
			cout << "Введите слово: ";
			cin.ignore();
			cin.getline(str, 100);
			strcpy_s(a->mas, 50, str);//Присваивание полю "строка" списка вводимую строку
			H.insert(a);                                                           //Вставка элемента в объкт-таблицу
		}
		case 3: {	  AAA* b = new AAA;
			char letter[1];
			cout << "Введите букву:";
			cin.ignore();
			cin.getline(letter, 2);
			strcpy_s(b->mas, 2, letter);
			H.deleteByData(b);
		}
			  break;
		case 4: {AAA* c = new AAA;
			char only[50];
			cout << "Введите слово: ";
			cin.ignore();
			cin.getline(only, 50);
			strcpy_s(c->mas, 50, only);
			H.Scan1(c);
		}
			  break;
		case 5:
		{
			char* str = new char[100];
			char words[14][50];
			char buf[25];
			cout << "Введите имя файла для чтения: ";
			cin.ignore();
			cin.getline(str, 100);
			output.open(str);
			if (!output.is_open())
				cout << "Файл не может быть открыт!\n";
			else
			{
				int i = 0;
				output.getline(buf, 25);
				do
				{
					strcpy_s(*(words + i), 50, buf);
					i++;
				} while (output.getline(buf, 50));
				for (int i = 0; i < H.sizeO - 1; i++)
				{
					AAA* a = new AAA;
					k = 0 + rand() % H.sizeO;
					a->key = k;
					strcpy_s(a->mas, 50, *(words + (0 + rand() % 14)));
					H.insert(a);
				}
				output.close();
			}
		}
		break;
		case 6:
		{
			char* str = new char[100];
			cout << "Введите имя файла для записи: ";
			cin.ignore();
			cin.getline(str, 100);
			foutF(input, str);
		}
		break;
		}
	}
	return 0;
}

void foutF(ofstream& f, char* name)
{
	f.open(name);
	for (int i = 0; i < 14; i++)
	{
		f << NML[i] << endl;
	}
	f.close();
}