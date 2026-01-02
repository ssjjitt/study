#include<iostream>
using namespace std;
struct Item
{
	float data;
	Item* next;
};
Item* head, * tail;

bool isNull(void)    //Проверка на пустоту
{
	return (head == NULL);
}
void deletFirst()   //Извлечение элемента из начала
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
	{
		Item* p = head;
		head = head->next;
		delete p;
	}
}
void getFromHead()  //Получение элемента из начала
{
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
		cout << "Начало = " << head->data << endl;
}
void insertToQueue(float x)  //Добавление элемента в очередь 
{
	Item* p = new Item;
	p->data = x;
	p->next = NULL;
	if (isNull())
		head = tail = p;
	else
	{
		tail->next = p;
		tail = p;
	}
}
void sortmax()
{
	Item* p = new Item;
	p = head;
	int count = 1, i = 1;
	float max = head->data;
	while (p != NULL)
	{
		if (max < p->data)
		{
			max = p->data;
			count = i;
		}
		i++;
		p = p->next;
	}
	tail->next = head;
	while ((count - 1))
	{
		head = head->next;
		tail = tail->next;
		count--;
	}
	tail->next = NULL;

}
void printQueue()             //Вывод очереди
{
	Item* p = new Item;
	if (isNull())
		cout << "Очередь пуста" << endl;
	else
	{
		cout << "Очередь = ";
		p = head;
		while (!isNull())
		{
			if (p != NULL)
			{
				cout << p->data << " "; cout << "-> ";
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
	int i = 1, choice = 1, z; head = NULL;  tail = NULL;
	while (choice != 0)
	{
		cout << "1 - добавить элемент" << endl;
		cout << "2 - получить элемент с начала" << endl;
		cout << "3 - извлечь элемент с начала" << endl;
		cout << "4 - вывести элементы" << endl;
		cout << "5 - Сдвиг до максимального" << endl;
		cout << "6 - очистить очередь" << endl;
		cout << "0 - выход" << endl;
		cout << "Выберите действие:\n";  cin >> choice;
		switch (choice)
		{
		case 1: cout << "Введите элемент: "; cin >> z;
			insertToQueue(z); printQueue();  break;
		case 2: getFromHead(); break;
		case 3: deletFirst();  break;
		case 4: printQueue();  break;
		case 5: sortmax();  break;
		case 6: clrQueue();    break;
		}
	}
	return 0;
}