// 1. Даны массивы A и B, состоящие из n элементов. Построить массив S, каждый элемент которого равен сумме соответствующих элементов массивов A и B.
#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	const int N = 100;
	int A[N], B[N], S[N], n, *pArrA, *pArrB, *pArrS;
	cout << "введите n = ";
	cin >> n;
	srand((unsigned)time(NULL));

	cout << endl << "массив A: ";
	for (pArrA = A; pArrA < A + n; pArrA++)
	{
		*pArrA = rand() % 5;
		cout << *pArrA << " ";
	}

	cout << endl << "массив B: ";
	for (pArrB = B; pArrB < B + n; pArrB++)
	{
		*pArrB = rand() % 5;
		cout << *pArrB << " ";
	}

	cout << endl << "массив C: ";
	for (int i = 0; i < n; i++)
	{
		S[i] = A[i] + B[i];
		cout << S[i] << " ";
	}
}