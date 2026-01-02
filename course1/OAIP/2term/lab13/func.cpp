#include "Header.h"
#include <iostream>
#include <iomanip>
void AAA::print()
{
	std::cout << x;
}
int AAA::getPriority() const
{
	return x;
}
namespace heap
{
	Heap create(int maxsize, CMP(*f)(void*, void*))		// создание кучи
	{
		return *(new Heap(maxsize, f));		// выделение памяти
	}
	int Heap::left(int ix)
	{
		return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1); // если левый больше размера, то возвращаем -1, иначе возвращаем левого
	}
	int Heap::right(int ix)
	{
		return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2); // то же самое
	}
	int Heap::parent(int ix)
	{
		return (ix + 1) / 2 - 1;	// для каждого родителя
	}
	void Heap::swap(int i, int j)		// сортировка
	{
		void* buf = storage[i]; // вспомогательная переменная
		storage[i] = storage[j]; // обмен данными
		storage[j] = buf; 
	}
	void Heap::heapify(int ix) // записб кучи в виде дерева каждый дочерний меньше или равен родительскому
	{
		int l = left(ix), r = right(ix), irl = ix; // левый, правый дочерние и корень
		if (l > 0) 
		{
			if (isGreat(storage[l], storage[ix])) irl = l;
			if (r > 0 && isGreat(storage[r], storage[irl])) 	irl = r;
			if (irl != ix)
			{
				swap(ix, irl);
				heapify(irl);
			}
		}
	}
	void Heap::insert(void* x)	// добавление элемента
	{
		int i;
		if (!isFull())
		{
			storage[i = ++size - 1] = x;	
			while (i > 0 && isLess(storage[parent(i)], storage[i]))
			{
				swap(parent(i), i);
				i = parent(i);
			}
		}
	}
	void* Heap::extractMax()	// ищем максимальный и удаляем
	{
		void* rc = nullptr;
		if (!isEmpty())
		{
			rc = storage[0];
			storage[0] = storage[size - 1];
			size--;
			heapify(0);
		} return rc;
	}
	void Heap::scan(int i) const // вывод на экран
	{
		int probel = 20;
		std::cout << '\n';
		if (size == 0)
			std::cout << "Пусто";
		for (int u = 0, y = 0; u < size; u++)
		{
			std::cout << std::setw(probel + 10) << std::setfill(' ');
			((AAA*)storage[u])->print();
			if (u == y)
			{
				std::cout << '\n';
				if (y == 0)
					y = 2;
				else
					y += y * 2;
			}
			probel /= 2;
		}
		std::cout << '\n';
	}


	void* Heap::extractMin()	// ищем минимальный и удаляем
	{
		void* rc = nullptr;
		if (!isEmpty())
		{
			rc = storage[size - 1];
			storage[size - 1] = storage[0];
			size--;
			heapify(size - 1);
		} return rc;
	}

	void* Heap::extractI(int i)	// ищем i-й и удаляем
	{
		void* rc = nullptr;
		if (!isEmpty())
		{
			rc = storage[i];
			storage[i] = storage[size - 1];
			size--;
			heapify(i);
		} return rc;
	}
	void Heap::unionHeap(Heap* h2)	// объединение куч
	{
		void* rc = nullptr;
		for (int i = 0; i < h2->size; i++)
		{
			rc = h2->storage[i]; // перемещаем указатель
			insert(rc);	// и добавляем
		}
		heapify(0);
	}
}