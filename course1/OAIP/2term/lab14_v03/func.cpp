#include "Header.h"
#include <iostream>

// При мультипликативном методе (multiplicative method) используется случайное действительное число f в 
// диапазоне от 0<f<1. Дробная часть произведения f * key лежит в диапазоне от 0 до 1. Если это произведение 
// умножить на n (размер хеш-таблицы), то целая часть полученного произведения даст значение хеш-функции в диапазоне 0...n-1.
int Multiplicative(int key, int size, int p)
{
	int A;
	double buf;
	A = (sqrt(5) - 1) / 2;
	int key2 = size * (modf(key * A, &buf));
	return (key2 + p) % size;
}
//-------------------------------
int Next_hash(int hash, int size, int p) // для след
{
	return (hash + 5 * p + 3 * p * p) % size;
}
//-------------------------------
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));// выделение памяти
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
bool Object::insert(void* d)// добавление элементов
{
	bool b = false;
	if (N != size)
		for (int i = 0, t = getKey(d), j = Multiplicative(t, size, 0);
			i != size && !b;  j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d;// заполняем поля
				N++;
				b = true;
			}
	return b;
}
//-------------------------------
int Object::searchInd(int key)// функция для поиска по ключу
{
	int t = -1;
	bool b = false;// переменная для поиска
	if (N != 0)
		// поиск будет происходить, пока не найдем элемент и b не станет равно true
		for (int i = 0, j = Multiplicative(key, size, 0); data[j] != NULL && i != size && !b; j = Multiplicative(key, size, ++i))
			if (data[j] != DEL)
				if (getKey(data[j]) == key)
				{
					t = j; b = true;
				}
	return t;
}
//-------------------------------
void* Object::search(int key)// вывод результата поиска
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