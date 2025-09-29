#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;
struct Tree
{
	double  key;
	char text[20];
	int rate;
	Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);       //Создание дерева
Tree* list(double i, char* s, int rate);       //Создание нового элемента
Tree* insertElem(Tree* Root, double key, char* s, int rate);  //Добавление нового элемента
Tree* search(Tree* n, double key);   //Поиск элемента по ключу 
Tree* delet(Tree* Root, double key); //Удаление элемента по ключу
void view(Tree* t, int level);    //Вывод дерева 
void delAll(Tree* t);             //Очистка дерева
void check(int rate);
void outRate();
int r1, r2, r3;         // счетчики для тарифов
Tree* Root = NULL; 	//указатель корня
int R_num = 0;
float coun, sum;
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, ".1251");
	double key; int rate, choice, n;
	Tree* rc; char s[20], letter;
	for (;;)
	{
		cout << "1 - создание дерева\n";
		cout << "2 - добавление элемента\n";
		cout << "3 - поиск по телефону\n";
		cout << "4 - удаление элемента\n";
		cout << "5 - вывод дерева\n";
		cout << "6 - вывод самого популярного тарифа\n";
		cout << "7 - очистка дерева\n";
		cout << "8 - выход\n";
		cout << "Выберите, что сделать:\n";
		cin >> choice;
		cout << "\n";
		switch (choice)
		{
		case 1:  Root = makeTree(Root);	break;
		case 2:  cout << "\nВведите телефон: ";
			cin >> key;
			cout << "Введите фамилию: "; cin >> s;
			cout << "Введите тариф: "; cin >> rate;
			insertElem(Root, key, s, rate); break;
		case 3:  cout << "\nВведите телефон: ";  cin >> key;
			rc = search(Root, key);
			cout << "Владелец = ";
			puts(rc->text); break;
		case 4:  cout << "\nВведите удаляемый номер телефона: "; cin >> key;
			Root = delet(Root, key);  break;
		case 5:  if (Root->key >= 0)
		{
			cout << "Дерево повернуто на 90 градусов влево:" << endl;
			view(Root, 0);
		}
			  else cout << "Дерево пустое\n"; break;
		case 6:  outRate();  break;

		case 7:  delAll(Root); break;

			break;
		case 8:  exit(0);
		}
	}
}

Tree* makeTree(Tree* Root)    //Создание дерева
{
	double key, rate; char s[20];
	cout << "Для остановки ввода введите отрицательное число:\n\n";
	if (Root == NULL)	// если дерево не создано
	{
		cout << "Введите телефон: "; cin >> key;
		cout << "Введите Фамилию: "; cin >> s;
		cout << "Введите тариф (1,2,3): "; cin >> rate;
		check(rate);
		Root = list(key, s, rate);	// установка указателя на корень
	}
	while (1)                //добавление элементов
	{
		cout << "\nВведите телефон: ";
		cin >> key;
		if (key < 0) break;       //признак выхода (ключ < 0)   
		cout << "Введите фамилию: ";  cin >> s;
		cout << "Введите тариф: ";  cin >> rate;
		check(rate);
		insertElem(Root, key, s, rate);
	}
	return Root;
}

void check(int rate)
{

	if (rate == 1)
		r1++;
	if (rate == 2)
		r2++;
	if (rate == 3)
		r3++;
}

void outRate()
{
	int maximum = max(r1, max(r2, r3));
	if (maximum == r1)
		cout << "Наиболее популярным тарифом является 1, с количеством абонентов " << r1 << endl;
	if (maximum == r2)
		cout << "Наиболеепопулярным тарифом является 2, с количеством абонентов " << r2 << endl;
	if (maximum == r3)
		cout << "Наиболее популярным тарифом является 3, с количеством абонентов " << r3 << endl;
}

Tree* list(double i, char* s, int rate)     //Создание нового элемента
{
	Tree* t = new Tree[sizeof(Tree)];
	t->key = i;

	t->rate = rate;
	for (i = 0; i < 20; i++)
		*((t->text) + (int)i) = *(s + (int)i);
	t->Left = t->Right = NULL;
	return t;
}

Tree* insertElem(Tree* t, double key, char* s, int rate)  //Добавление нового элемента
{
	Tree* Prev = NULL;	     // Prev - элемент перед текущим
	int find = 0;        // признак поиска
	while (t && !find)
	{
		Prev = t;
		if (key == t->key)
			find = 1;	   //ключи должны быть уникальны
		else
			if (key < t->key) t = t->Left;
			else t = t->Right;
	}
	if (!find)              //найдено место с адресом Prev
	{
		t = list(key, s, rate);           //создается новый узел 
		if (key < Prev->key)  // и присоединяется либо 
			Prev->Left = t;    //переход на левую ветвь,
		else
			Prev->Right = t;   // либо на правую 
	}
	return t;
}



Tree* delet(Tree* Root, double key)  //Удаление элемента по ключу
{	// Del, Prev_Del - удаляемый элемент и его предыдущий ;
	// R, Prev_R - элемент, на который заменяется удаленный, и его родитель; 
	Tree* Del, * Prev_Del, * R, * Prev_R;
	Del = Root;
	Prev_Del = NULL;
	while (Del != NULL && Del->key != key)//поиск элемента и его родителя 
	{
		Prev_Del = Del;
		if (Del->key > key)
			Del = Del->Left;
		else
			Del = Del->Right;
	}
	if (Del == NULL)              // элемент не найден
	{
		puts("\nНет такого ключа");
		return Root;
	}
	if (Del->Right == NULL) // поиск элемента R для замены
		R = Del->Left;
	else
		if (Del->Left == NULL)
			R = Del->Right;
		else
		{
			Prev_R = Del; //поиск самого правого элемента в левом поддереве
			R = Del->Left;
			while (R->Right != NULL)
			{
				Prev_R = R;
				R = R->Right;
			}
			if (Prev_R == Del) // найден элемент для замены R и его родителя Prev_R 
				R->Right = Del->Right;
			else
			{
				R->Right = Del->Right;
				Prev_R->Right = R->Left;
				R->Left = Prev_R;
			}
		}
	if (Del == Root) Root = R;	//удаление корня и замена его на R
	else
		// поддерево R присоединяется к родителю удаляемого узла
		if (Del->key < Prev_Del->key)
			Prev_Del->Left = R; // на левую ветвь 
		else
			Prev_Del->Right = R;	// на правую ветвь
	double tmp = Del->key;
	cout << "\nУдален элемент с ключом " << tmp << endl;
	delete Del;
	return Root;
}

Tree* search(Tree* n, double key)  //Поиск элемента по ключу 
{
	Tree* rc = n;
	if (rc != NULL)
	{
		if (key < (key, n->key))
			rc = search(n->Left, key);
		else
			if (key > (key, n->key))
				rc = search(n->Right, key);
	}
	else
		cout << "Нет такого элемента\n";
	return rc;
}

void view(Tree* t, int level) //Вывод дерева 
{
	if (t)
	{
		view(t->Right, level + 1);	//вывод правого поддерева
		for (int i = 0; i < level; i++)
			cout << "   ";
		long long tm = long long(t->key);
		int tm1 = t->rate;
		cout << tm << ' ' << tm1 << ' ';
		puts(t->text);
		view(t->Left, level + 1);	//вывод левого поддерева
	}
}

void delAll(Tree* t) //Очистка дерева
{
	if (t != NULL)
	{
		delAll(t->Left);
		delAll(t->Right);
		delete t;
	}
}