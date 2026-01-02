// Ввести массивы А и В.В массив С перенести те элементы массива А, которые больше максимального элемента массива В.
// Массив С отсортировать по убыванию, используя алгоритмы сортировок : «пузырек», в сортировка простой вставкой.

#include <iostream>
using namespace std;

void bubbleSort(int a[], int n)
{
	int i, j, t;
	for (i = 1; i < n; i++)
		for (j = n - 1; j >= i; j--)
			if (a[j - 1] < a[j])
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
}

void insertSort(int* A, int size)
{
	int t, i, j;
	for (i = 1; i < size; i++)
	{
		t = A[i];
		for (j = i - 1; j >= 0 && A[j] < t; j--)
			A[j + 1] = A[j];
		A[j + 1] = t;
	}
}


int main() {
	setlocale(LC_ALL, "Rus");
	int size, i, j, sizeC = 0, ind = 0, max = 0, ch = 3;
	int A[100], B[100], C[100];
	cout << "Количество элементов = ";
	cin >> size;

	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 20;
		B[i] = rand() % 10;
		if (B[i] > max) max = B[i];
	}
	for (i = 0; i < size; i++)
	{
		if (A[i] > max) {
			C[ind] = A[i];
			ind++;
			sizeC++;
		}
	}
	cout << "Массив A: ";
	for (i = 0; i < size; i++) cout << A[i] << " ";
	cout << "\nМассив B: ";
	for (i = 0; i < size; i++) cout << B[i] << " ";
	cout << "\nМаксимальный в B: " << max;
	cout << "\nМассив C: ";
	for (i = 0; i < sizeC; i++) cout << C[i] << " ";

	cout << "\nКак сортировать? 1 - пузырьком, 2 - вставками\n";
	cin >> ch;

	switch (ch) {
	case 1: bubbleSort(C, sizeC); break;
	case 2: insertSort(C, sizeC); break;
	}
	cout << "\nОтсортированный массив C: ";
	for (i = 0; i < sizeC; i++) cout << C[i] << " ";
}