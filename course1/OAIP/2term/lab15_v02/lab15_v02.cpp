// Список электронных адресов. Создать хеш-таблицу со следующими полями: адрес, фамилия абонента, год создания. Ключ – год создания.

#include "Hash_Twin_Chain.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <time.h>

using namespace std;

const char* NML[15] = { "Яглинская", "Пивоваров", "Лупинка", "Петрович", "Полторан",
						"Михедов", "Дубина", "Кашков", "Щипер", "Зданевич",
						"Никитенко", "Жигадло", "Курило", "Нестерова", "Дайтбегова" };

const char* ADR[15] = { "Пушкина 32", "Строителей 3", "Ленина 52", "Революционная 161", "Октябрьская 11",
						"Фрунзе 21", "Пушкина 55", "Студенческая 50", "Кирова 10", "Хоружей 55",
						"Советская 1", "Интернациональная 67", "Пролетарская 11", "Мира 8", "Юности 5"

};

struct AAA
{
	int key;
	const char* mas;
	const char* adr;
	AAA(int k, const char* z, const char* l)
	{
		key = k;
		mas = z;
		adr = l;
	}
	AAA()
	{
		key = 0;
		mas = NULL;
		adr = NULL;
	}
};
//-------------------------------
int hf(void* d)                                                                         //Функция создания указателя как информационного элемента списка
{
	AAA* f = (AAA*)d;
	return f->key;
}
//-------------------------------
void AAA_print(listx::Element* e)
{
	std::cout << ((AAA*)e->data)->key << '\t' << ((AAA*)e->data)->mas << "\t" << ((AAA*)e->data)->adr << " / ";
}
//-------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");                                                            //Установление кодировки
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(0));
	clock_t start, end;	// для времени
	double searching_time;
	int current_size = 0;
	//Переменная, определяющая размер таблицы                                                    
	cout << "Введите размер хеш-таблицы: ";                             //Сообщение о вводе размера таблицы
	cin >> current_size;                                                                 //Ввод пользователем размера таблицы
	hashTC::Object H = hashTC::create(current_size, hf);
	int choice;
	int k;
	for (;;)																			//Меню
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "5 - заполнение хэш-таблицы" << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:  exit(0);
		case 1: H.Scan();
			break;
		case 2: {	  AAA* a = new AAA;                                            //Создание нового элемента списка. Список - элемент таблицы
			char* str = new char[100];                                              //Создание новой строки как данных, хранящихся в поле элемента списка
			char* str2 = new char[100];
			cout << "Введите год(начало c 0): ";
			cin >> k;
			k = k;//Ввод ключа, хранящегося в поле элемента списка
			a->key = k;                                                            //Присваивание полю "ключ" списка вводимый ключ
			cout << "Введите фамилию: ";
			cin.ignore();
			cin.getline(str, 100);
			a->mas = str;                                                          //Присваивание полю "строка" списка вводимую строку
			cout << "Введите адрес: ";
			cin.ignore();
			cin.getline(str2, 100);
			a->adr = str2;
			H.insert(a);                                                           //Вставка элемента в объкт-таблицу
		}
			  break;
		case 3: {	  AAA* b = new AAA;
			cout << "Введите год: ";
			cin >> k;
			b->key = k;
			H.deleteByData(b);
		}
			  break;
		case 4: {AAA* c = new AAA;
			cout << "Введите год: ";
			cin >> k;
			c->key = k;
			start = clock();
			if (H.search(c) == NULL)
				cout << "Элемент не найден" << endl;
			else
			{
				cout << "Первый элемент с данным годом: ";
				AAA_print(H.search(c));
				cout << endl;
			}
			end = clock();
			searching_time = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "время поиска: " << searching_time << endl;
		}
			  break;
		case 5:
		{
			for (int i = 0; i < H.sizeO; i++)
			{
				AAA* a = new AAA;
				k = 0 + rand() % H.sizeO;
				a->key = k;
				a->mas = NML[0 + rand() % 13];
				a->adr = ADR[0 + rand() % 13];
				H.insert(a);
			}
		}
		break;
		}
	}
	return 0;
}