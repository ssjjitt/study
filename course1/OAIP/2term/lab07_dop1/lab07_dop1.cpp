#include <iostream>
#include <windows.h>
using namespace std;

struct Stack
{
	char str;
	Stack* head;
	Stack* next;
};


void dop1(Stack* MyStk);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	Stack* MyStk = new Stack; //выделение памяти для стека
	MyStk->head = NULL;
	dop1(MyStk);
}

void dop1(Stack* MyStk)
{
	string a;
	short i = 0;
	cout << "Введите вашу строку:\n";
	cin >> a;
	short length = a.length();

	for (i = 0; i < (length / 2); i++)		// цикл для вывода первой части слова, тк стек работает по принципу LIFO мы сможем вывести первым последний элемент
	{
		Stack* e = new Stack;    //выделение памяти для нового элемента
		e->str = a[i];           //запись элемента в поле  
		e->next = MyStk->head;   //перенос вершины на следующий элемент 
		MyStk->head = e;         //сдвиг вершины на позицию вперед
	}

	while (MyStk->head)			
	{
		cout << MyStk->head->str;		// выводим букву в конце
		MyStk->head = MyStk->head->next;		// перенос вершины на след
	}

	for (i = (length / 2); i < length; i++)			// цикл для вывода второй части
	{
		Stack* e = new Stack;    //выделение памяти для нового элемента
		e->str = a[i];           //запись элемента в поле 
		e->next = MyStk->head;   //перенос вершины на следующий элемент 
		MyStk->head = e;         //сдвиг вершины на позицию вперед
	}

	while (MyStk->head)
	{
		cout << MyStk->head->str;
		MyStk->head = MyStk->head->next;
	}

	cout << '\n';
}