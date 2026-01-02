#include <stdlib.h>
#include <iostream>
using namespace std;

template <class T>
void swapEl(T* arr, int i) // функция для свапа элементов
{
	T buff;
	buff = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = buff;
}
template <class T>
T Shaker(T* arr, int size)
{
	int leftMark = 1; // левая граница
	int rightMark = size - 1; // правая граница
	while (leftMark <= rightMark) // пока не пройдем
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (arr[i - 1] > arr[i]) swapEl(arr, i); // свапаем
		leftMark++; // смещаем границу


		for (int i = leftMark; i <= rightMark; i++)
			if (arr[i - 1] > arr[i]) swapEl(arr, i); // тоже свапаем
		rightMark--; // смещаем границу
	}
	return 1;
}

template <class T>
T heapify(T arr[], int n, int root)// функция heapify для нагромождения дерева
{
	int largest = root; // корень - самый большой элемент
	int l = 2 * root + 1; // слева = 2*корень + 1
	int r = 2 * root + 2; // справа = 2*корень + 2
	if (l < n && arr[l] > arr[largest])// Если левый дочерний элемент больше корневого
		largest = l;
	if (r < n && arr[r] > arr[largest])// Если правый дочерний элемент больше, чем самый большой на данный момент
		largest = r;
	if (largest != root)// Если самый большой не является корневым
	{
		swap(arr[root], arr[largest]);//поменять местами корневой и самый большой
		heapify(arr, n, largest);// Рекурсивное нагромождение поддерева
	}
	return 1;
}

template <class T>
T heapSort(T arr[], int n)// реализация сортировки кучи
{
	for (int i = n / 2 - 1; i >= 0; i--)// создать кучу
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--)// извлечение элементов из кучи один за другим
	{
		swap(arr[0], arr[i]);// Переместить текущий корень в конец
		heapify(arr, i, 0);// снова вызовите max heapify для уменьшенной кучи
	}
	return 1;
}

template <class T>
T insOrd(T m[], int sm, int em, int e)
{
	T buf;
	int i = sm;
	while (i <= em && m[i] < e) // пока не конец
	{
		if (i - 1 >= sm)
			m[i - 1] = m[i];
		i++;
	}  m[i - 1] = e;
	return 1;
}

template <class T>
T* merge(T m[], int sm, int cm, int em)
{
	for (int i = 0; i <= sm; i++)
	{
		if (m[i] > m[cm + 1])
		{
			T buf = m[i];
			m[i] = m[cm + 1];
			insOrd(m, cm + 1, em, buf);
		}
	}
	return m;
}

template <class T>
T* sortMerge(T m[], int lm, int sm = 0)//рекурсивная процедура сортировки
{
	if (lm > 1)
	{
		sortMerge(m, lm / 2, sm);//сортировка левой части
		sortMerge(m, lm - lm / 2, sm + lm / 2); //сортировка правой части
		merge(m, sm, sm + lm / 2 - 1, sm + lm - 1);//слияние двух частей
	};
	return m;
}

template <class T>
void bubleSort(T a[], int n)
{
	// boolean variable to check that
	// whether it is sorted or not
	bool b = true;
	while (b) {
		b = false;
		for (size_t i = 0; i < n - 1; i++) {

			// swapping the variable
			// for sorting order
			if (a[i] > a[i + 1]) {
				T temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				b = true;
			}
		}
	}
}

int GetRandKey(int reg = 0)
{
	if (reg > 0) srand((unsigned)time(NULL));
	int rmin = 0;
	int rmax = 100000;
	return (int)(((int)rand() / (int)RAND_MAX) * (rmax - rmin) + rmin);
}
int main()
{
	setlocale(LC_CTYPE, "rus");
	const int N = 50000;
	int k[N], f[N];
	clock_t t1, t2;
	GetRandKey(1);
	for (int i = 0; i < N; i++) f[i] = GetRandKey(0);
	for (int n = 10000; n <= N; n += 10000)
	{
		cout << "n = " << n << endl;
		cout << "Шейкер: ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		Shaker(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "Слиянием: ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		sortMerge(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "Пирамидальная: ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		heapSort(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "Пузырьком: ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();
		bubleSort(k, n);
		t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl << endl;
	}
	return 0;

}