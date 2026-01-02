#include <iostream>
using namespace std;

void insertionSort(int arr[], int n) {   //сортировка простой вставкой
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];   //сохранить
		j = i - 1;      //уменьшение размера унупорядоченной части
		while (j >= 0 && arr[j] > key) {  //поиск места вставки
			arr[j + 1] = arr[j];   //сдвиг элемента
			j = j - 1;
		}
		arr[j + 1] = key;    //вставка очередного на место первого большего его
	}
}

void main() {
	setlocale(LC_ALL, "rus");
	int A[10], B[4], maxB = 0;
	srand(time(NULL));
	cout << "Изначальный массив: ";
	for (int i = 0; i < 10; i++)
	{
		A[i] = 10 + rand() % 40;
		cout << A[i] << " ";
	}
	insertionSort(A, 4);
	cout << "\nПервые 4 элемента по возрастанию: ";
	for (int i = 0; i < 10; i++)
	{
		cout << A[i] << " ";

	}
	cout << endl;
	for (int i = 9, k = 0; i > 5; i--, k++)
	{
		B[k] = A[i];


	}
	insertionSort(B, 4);

	cout << "Последние 4 элемента по убыванию: ";
	for (int i = 9, k = 0; i > 5; i--, k++)
	{
		A[i] = B[k];
	}
	for (int i = 0; i < 10; i++)
	{
		cout << A[i] << " ";

	}
	cout << endl;
}