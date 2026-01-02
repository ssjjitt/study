// Ввести массивы А и В. В массив С перенести элементы массива А с нечетным значением и элементы массива В с четным значением. 
// Массив С отсортировать по возрастанию, используя алгоритмы сортировок: сортировка Шелла, сортировка Хоара.

#include <iostream>
using namespace std;

void ShellSort(int mass[], int n)
{
	int i, j, step;
	int tmp;
	for (step = n / 2; step > 0; step /= 2)
		for (i = step; i < n; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
}


int getHoarBorder(int A[], int sm, int em)
{
	int i = sm - 1, j = em + 1;
	int brd = A[sm];
	int buf;
	while (i < j)
	{
		while (A[--j] > brd);
		while (A[++i] < brd);
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
	int size, i, j, sizeC = 0, ind = 0, ch = 3;
	int A[100], B[100], C[100];
	cout << "Количество элементов = ";
	cin >> size;

	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 20;
		if (A[i] % 2 != 0) {
			C[ind] = A[i];
			ind++;
			sizeC++;
		}
		B[i] = rand() % 40;
		if (B[i] % 2 == 0)
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

	cout << "\nКак сортировать? 1 - Шелла, 2 - Хоар\n";
	cin >> ch;

	switch (ch) {
	case 1: ShellSort(C, sizeC); break;
	case 2: sortHoar(C, 0, sizeC - 1); break;
	}
	cout << "\nОтсортированный массив C: ";
	for (i = 0; i < sizeC; i++) cout << C[i] << " ";
}