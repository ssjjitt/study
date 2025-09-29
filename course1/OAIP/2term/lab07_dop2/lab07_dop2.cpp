#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

struct Stack
{
	int data;				// целочисленное информационное поле      
	Stack* head;		 
	Stack* next;
};


void dop2(Stack* MyStk);


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	Stack* MyStk = new Stack; //выделение памяти для стека
	MyStk->head = NULL;
	dop2(MyStk);
}
void dop2(Stack* MyStk)
{
	ifstream file("text.txt");
	string str;
	short counter = 1, seqNum = 1, min = SHRT_MAX, minData;
	int* Array = new int[10];

	while (getline(file, str))
	{
		Stack* e = new Stack;			// выделение памяти
		e->data = str.length();		// заполняем целочисленное поле
		if (e->data <= min)		// поиск мин строки
		{
			min = e->data;
			minData = min;			    // для мин длины
			seqNum = counter;			// для номера строки
		}
		e->next = MyStk->head;
		MyStk->head = e;
		counter++;
	}

	cout << "Длины строк: \n"; // с конца файла, тк LIFO
	while (MyStk->head)
	{
		cout << MyStk->head->data << "\t";
		MyStk->head = MyStk->head->next;
	}

	cout << "\nCамая короткая строка номер " << seqNum << " длина " << minData << ".\n";
}
