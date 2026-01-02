// 1. В приложении 1 приведен проект, в котором реализована очередь на основе односвязного списка с приоритет-ным включением. 
// На основе данного проекта разработать функции, которые предлагается создать в данном приложе-нии.

#include <iostream>
using namespace std;
struct Item
{
	int data;
	Item* next;
};
Item* head, * tail;

bool isNull(void)    //Проверка на пустоту
{
	return (head == nullptr);
}
void deletFirst()   //Извлечение элемента из начала
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
	{
		Item* p = head;		// адрес элемента
		head = head->next;		// перемещаемся дальше
		delete p;		// удаляем
	}
}
void deletlast()   //Извлечение элемента из начала
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
	{
		Item* p;
		tail->data = NULL;			

	}
}
void getFromHead()  // элемент из начала
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
		cout << "Начало = " << head->data << endl;		// выводим элемент в начале
}
void getFromTail()  // элемент из конца
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
		cout << "Конец = " << tail->data << endl;		// выводим элемент в конце
}
void insertToQueue(int x)  //Добавление элемента в очередь 
{
	Item* p = new Item;      //новый указатель 
	p->data = x;			// заполняем поле переменной x
	p->next = nullptr;		
	Item* v = new Item;      //указатель для нового числа
	Item* p1 = new Item;	
	Item* p2 = new Item;
	int i = 0;               //флажок 
	if (isNull())
		head = tail = p;
	else
	{
		p2 = head; p1 = head; // !!!Чтобы реализовать ввод LIFO необходимо чтобы указатель p2 был сзади, а FIFO наоборот
		while (p1 != nullptr)  //пока очередь не закончится
		{
			if (i == 1) //ТАКЖЕ НЕОБХОДИМЫ ДЛЯ РЕАЛИЗАЦИИ LIFO
			{
				if (i == 1)
				{
					if (x > p1->data)  //число больше, чем в очереди
					{
						v->data = x;
						v->next = p1;
						p2->next = v;
						return;
					}
					if (x == p1->data)
					{
						v->data = x;
						v->next = p1->next;
						p1->next = v;
						return;
					}
					p2 = p2->next;
				}
				if (x > p1->data)
				{
					v->data = x;
					v->next = p1;
					head = v;
					return;
				}
				if (p1->next == nullptr)
				{
					v->data = x;
					v->next = nullptr;
					tail->next = v;
					tail = v;
					return;
				}
				i = 1;

				p1 = p1->next;      // следующее число
			}
			else // else необходимое для реализации вставки LiFo
			{
				if (x >= p1->data)
				{
					v->data = x;
					v->next = p2;
					head = v;
					return;
				}
			}
			p1 = p1->next; //ТАКЖЕ НЕОБХОДИМЫ ДЛЯ РЕАЛИЗАЦИИ LiFo
			i = 1;
		}
		if (p1 == NULL) // Выражение ДЛЯ РЕАЛИЗЦИИ LiFo
		{
			v->data = x;
			v->next = tail;
			p2->next = v;
		}
	}
}

void printQueue()             //Вывод очереди
{
	int g;
	Item* p = new Item;
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
	{
		cout << "Очередь = ";
		p = head;
		while (!isNull())
		{
			if (p != nullptr)
			{
				g = p->data;
				if (g == 0) {

				}
				else { cout << p->data << " "; cout << "-> "; }
				p = p->next;
			}
			else
			{
				cout << "NULL" << endl;
				return;
			}
		}
	}
}

void clrQueue()           //Очистка очереди
{
	while (!isNull()) deletFirst();
}
int main()
{
	setlocale(LC_CTYPE, "Russian");
	int i = 1, choice = 1, z; head = nullptr;  tail = nullptr;
	while (choice != 0)
	{
		cout << "1 - добавить элемент" << endl;
		cout << "2 - получить элемент с начала" << endl;
		cout << "3 - извлечь элемент с начала" << endl;
		cout << "4 - вывести элементы" << endl;
		cout << "5 - очистить очередь" << endl;
		cout << "6 - получить элемент с конца" << endl;
		cout << "0 - выход" << endl;
		cout << "Выберите действие:\n";  cin >> choice;
		switch (choice)
		{
		case 1: cout << "Введите элемент: "; cin >> z;
			insertToQueue(z); printQueue();  break;
		case 2: getFromHead(); break;
		case 3: deletFirst();  break;
		case 4: printQueue();  break;
		case 5: clrQueue();    break;
		case 6: getFromTail(); break;
		case 7: deletlast(); break;
		}
	}
	return 0;
}