#include "Header.h"
#include <iostream>
int HashFunction(int key, int size, int p)    // Хеш-функция
{
	double key2 = 5 * ((0.6180339887499 * key) - int((0.6180339887499 * key)));	// алгоритм хеш-функции
	return (p + key) % size;
}

int Next_hash(int hash, int size, int p) // для след
{
	return (hash + 5 * p + 3 * p * p) % size;
}
//-------------------------------
int universal(int key, int size, int p)	// обеспечивает равномерное хеширование: для очередного ключа вероятности помещения его в любую ячейку совпадают
{
	int h = 0, a = 314445, b = 37542;
	h = (a * h + key) % size;
	return (h < 0) ? (h + size) : h;
}
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey)); // выделение памяти
}
//-------------------------------
Object::Object(int size, int(*getkey)(void*))
{
	N = 0;
	this->size = size;
	this->getKey = getkey;
	this->data = new void* [size];
	for (int i = 0; i < size; ++i)
		data[i] = NULL;
}
//-------------------------------
bool Object::insert(void* d) // добавление элементов
{
	bool b = false;
	if (N != size)
		for (int i = 0, t = getKey(d), j = universal(t, size, 0);
			i != size && !b;  j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d; // заполняем поля
				N++;
				b = true;
			}
	return b;
}
//-------------------------------
int Object::searchInd(int key) // функция для поиска по ключу
{
	int t = -1;
	bool b = false; // переменная для поиска
	if (N != 0)
		// поиск будет происходить, пока не найдем элемент и b не станет равно true
		for (int i = 0, j = universal(key, size, 0); data[j] != NULL && i != size && !b; j = universal(key, size, ++i))
			if (data[j] != DEL)
				if (getKey(data[j]) == key)
				{
					t = j; b = true;
				}
	return t;
}
//-------------------------------
void* Object::search(int key) // вывод результата поиска
{
	int t = searchInd(key);
	return(t >= 0) ? (data[t]) : (NULL);
}
//-------------------------------
void* Object::deleteByKey(int key) // функция для удаления
{
	int i = searchInd(key); // ищем элемент
	void* t = data[i]; // присваиваем указатель на этот элемент
	if (t != NULL)
	{
		data[i] = DEL; // удаляем
		N--;
	}
	return t;
}
//-------------------------------
bool Object::deleteByValue(void* d)
{
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
void Object::scan(void(*f)(void*)) // вывод элементов
{
	for (int i = 0; i < this->size; i++) // перебираем с помощью цикла
	{
		std::cout << " Элемент " << i; // и выводим
		if ((this->data)[i] == NULL)
			std::cout << "  Пусто!" << std::endl;
		else
			if ((this->data)[i] == DEL)
				std::cout << "  Удален" << std::endl;
			else
				f((this->data)[i]);
	}
}