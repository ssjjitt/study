#include "Header.h"
#include <iostream>
using namespace std;
using namespace heap;
heap::CMP cmpAAA(void* a1, void* a2)  //Функция сравнения
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
	heap::CMP
		rc = heap::EQUAL;
	if (A1->x > A2->x)
		rc = heap::GREAT;
	else
		if (A2->x > A1->x)
			rc = heap::LESS;
	return rc;
#undef A2
#undef A1 
}

int main()
{
	setlocale(LC_ALL, "rus");
	int k = 1, choice;
	heap::Heap h1 = heap::create(30, cmpAAA);
	heap::Heap h2 = heap::create(30, cmpAAA);
	Heap* ph2 = &h2;
	for (;;)
	{
		cout << "1 - Вывод кучи на экран" << endl;
		cout << "2 - Добавить элемент" << endl;
		cout << "3 - Удалить максимальный элемент" << endl;
		cout << "4 - Удалить минимальный элемент" << endl;
		cout << "5 - Удалить i-ый элемент" << endl;
		cout << "6 - Объединение двух бинарных куч" << endl;
		cout << "0 - Выход" << endl;
		cout << "Cделайте выбор:" << endl;  cin >> choice;
		switch (choice)
		{
		case 0:  exit(0);
		case 1:  h1.scan(0);
			break;
		case 2: 
			while (k > 0)
			{
				AAA* a = new AAA;
				cout << "Введите ключ:" << endl; 	
				cin >> k;
				if (k > 0)
				{
					a->x = k;
					h1.insert(a);
				}
			}
			  break;
		case 3:   h1.extractMax();
			break;
		case 4:   h1.extractMin();
			break;
		case 5:
			int i;
			cout << "Введите i:\n";
			cin >> i;
			h1.extractI(i);
			break;
		case 6:
			int j = 1;
			cout << "Введите вторую кучу:\n";
			while (j > 0)
			{
				AAA* b = new AAA;
				cout << "Введите ключ:" << endl; 	cin >> j;
				if (j > 0)
				{
					b->x = j;
					h2.insert(b);
				}
			}
			h1.unionHeap(ph2);
			break;
		}
	} return 0;
}