// Ввести массив А, в массив В перенести все элементы массива А, имеющие четный индекс, справа от которых расположены элементы с нечетным значением.
// Массив В отсортировать по убыванию, используя алгоритмы сортировок : сортировка выбором, сортировка Хоара.
#include <iostream>
using namespace std;

void selectSort(int A[], int size)
{
	int k, i, j;
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1, k = i; j < size; j++)
			if (A[j] > A[k])
				k = j;
		int c = A[k];
		A[k] = A[i];
		A[i] = c;
	}
}

int getHoarBorder(int A[], int sm, int em)
{
	int i = sm - 1, j = em + 1;
	int brd = A[sm];
	int buf;
	while (i < j)
	{
		while (A[--j] < brd);
		while (A[++i] > brd);
		if (i < j)
		{
			buf = A[j];
			A[j] = A[i];
			A[i] = buf;
		};
	}
	return j;
}
int* sortHoar(int A[], int sm, int em)
{
	if (sm < em)
	{
		int hb = getHoarBorder(A, sm, em);
		sortHoar(A, sm, hb);
		sortHoar(A, hb + 1, em);
	}
	return A;
};



int main() {
	setlocale(LC_ALL, "Rus");
	int size, i, j, sizeB = 0, ind = 0, ch = 3;
	int A[100], B[100];
	cout << "Количество элементов = ";
	cin >> size;
	cout << "Массив A: \n";
	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 100;
		cout << A[i] << " ";
		if (i % 10 == 0 && i > 0) cout << "\n";
	}

	for (i = 0; i < size; i++)
	{
		j = i + 1;
		if (i % 2 == 0 && A[j] % 2 != 0) {
			B[ind] = A[i];
			sizeB++;
			ind++;
		}
	}

	cout << "\nМассив B: ";
	for (int i = 0; i < sizeB; i++)
	{
		cout << B[i] << " ";
	}

	cout << "\nКак сортировать? 1 - выбором, 2 - Хоар\n";
	cin >> ch;

	switch (ch) {
	case 1:selectSort(B, sizeB); break;
	case 2: sortHoar(B, 0, sizeB - 1); break;
	}

	cout << "\nОтсортированный массив B: ";
	for (int i = 0; i < sizeB; i++)
	{
		cout << B[i] << " ";
	}
}