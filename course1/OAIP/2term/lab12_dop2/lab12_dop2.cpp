#include <iostream>
#include <algorithm>

using namespace std;
struct Tree
{
	int value;
	Tree* left;
	Tree* right;
};

int* create();
Tree* makeTree(Tree* Root, int key);
Tree* list(int i);
Tree* insertElem(Tree* t, int key);
void view(Tree* t, int level);
int N;

int main()
{
	setlocale(LC_ALL, "rus");
	int* delta = create();
	Tree* Root = new Tree;
	Root = makeTree(Root, delta[0]);
	for (int i = 1; i < N; i++)
	{
		insertElem(Root, delta[i]);
	}
	view(Root, 0);
	system("pause");
	return 0;
}

int* create()
{
	cout << "Введите количество элементов: "; cin >> N;
	int* mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		cout << "Введите новый элемент массива: "; cin >> mass[i];
	}
	std::sort(mass, mass + N);
	for (int i = 1; i < N; i += 2)
	{
		int t = mass[i - 1];
		mass[i - 1] = mass[i];
		mass[i] = t;
	}
	for (int i = 0; i < N; i++)
	{
		cout << "Элементы массива: "; cout << mass[i] << endl;
	}
	return mass;
}
Tree* list(int i)     //Создание нового элемента
{
	Tree* t = new Tree[sizeof(Tree)];
	t->value = i;
	t->left = t->right = NULL;
	return t;
}
Tree* makeTree(Tree* Root, int key)    //Создание дерева
{
	Root = list(key);	// установка указателя на корень
	return Root;
}
Tree* insertElem(Tree* t, int key)  //Добавление нового элемента
{
	Tree* Prev = NULL;	     // Prev - элемент перед текущим
	int find = 0;        // признак поиска
	while (t && !find)
	{
		Prev = t;
		if (key == t->value)
			find = 1;	   //ключи должны быть уникальны
		else
			if (key < t->value) t = t->left;
			else t = t->right;
	}
	if (!find)              //найдено место с адресом Prev
	{
		t = list(key);           //создается новый узел 
		if (key < Prev->value)  // и присоединяется либо 
			Prev->left = t;    //переход на левую ветвь,
		else
			Prev->right = t;   // либо на правую 
	}
	return t;
}

void view(Tree* t, int level) //Вывод дерева 
{
	if (t)
	{
		view(t->right, level + 1);	//вывод правого поддерева
		for (int i = 0; i < level; i++)
			cout << "   ";
		int tm = t->value;
		cout << tm << endl;
		view(t->left, level + 1);	//вывод левого поддерева
	}
}