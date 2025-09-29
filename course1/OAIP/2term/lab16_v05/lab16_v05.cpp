// Ввести массивы А и В. В массив С перенести элементы массива А с четным значением и элементы массива В с нечетным значением. 
// Массив С отсортировать по возрастанию, используя алгоритмы сортировок: «пузырек», сортировка выбором.
#include <iostream>
using namespace std;

void selectSort(int A[], int size)
{
	int k, i, j;
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1, k = i; j < size; j++)
			if (A[j] < A[k])
				k = j;
		int c = A[k];
		A[k] = A[i];
		A[i] = c;
	}
}

void bubbleSort(int a[], int n)
{
	int i, j, t;
	for (i = 1; i < n; i++)
		for (j = n - 1; j >= i; j--)
			if (a[j - 1] > a[j])
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
}

int main() {
	setlocale(LC_ALL, "Rus");
	int size, i, j, sizeC = 0, ind = 0, ch = 3;
	int A[100], B[100], C[100];
	cout << "Количество элементов = ";
	cin >> size;

	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 20;
		if (A[i] % 2 == 0) {
			C[ind] = A[i];
			ind++;
			sizeC++;
		}
		B[i] = rand() % 40;
		if (B[i] % 2 != 0)
		{
			C[ind] = B[i];
			ind++;
			sizeC++;
		}
	}
	cout << endl << endl;
	cout << "Массив A: ";
	for (i = 0; i < size; i++) cout << A[i] << " ";
	cout << "\nМассив B: ";
	for (i = 0; i < size; i++) cout << B[i] << " ";
	cout << "\nМассив C: ";
	for (i = 0; i < sizeC; i++) cout << C[i] << " ";

	cout << "\nКак сортировать? 1 - выбором, 2 - пузырьком\n";
	cin >> ch;

	switch (ch) {
	case 1:selectSort(C, sizeC); break;
	case 2: bubbleSort(C, sizeC); break;
	}
	cout << "\nОтсортированный массив C: ";
	for (i = 0; i < sizeC; i++) cout << C[i] << " ";
}