// 1. Заданы два массива А и В.Подсчитать в них количество элементов, меньших значения t, и первым на печать вывести массив, имеющий наибольшее их количество.
#include <iostream>
int main()
{
	using namespace std;
	const int N = 100;
	int A[N], B[N], *pArrA = A, *pArrB = B, t, size, k = 0, m = 0;
	cout << "size: ";
	cin >> size;
	cout << "t = ";
	cin >> t;
	cout << endl;
	srand((unsigned)time(NULL));
	cout << "A[i]: ";
	for (pArrA = A; pArrA < A + size; pArrA++)
	{
		*pArrA = rand() % 20;
		
		if (*pArrA < t) m++;
		cout << *pArrA << " ";
	}
	cout << endl << "m = " << m << endl << "B[i]: ";
	for (pArrB = B; pArrB < B + size; pArrB++)
	{
		*pArrB = rand() % 20;
		if (*pArrB < t) k++;
		cout << *pArrB << " ";
	}
	cout << endl << "k = " << k << endl;
	cout << "=================================================================" << endl;
	if (k < m) {
		cout << "k < m" << endl;
		cout << "B[i]: ";
		for (pArrB = B; pArrB < B + size; pArrB++)
			cout << *pArrB << " ";
	}
	else if (k > m) {
		cout << "m > k" << endl;
		cout << "A[i]: ";
		for (pArrA = A; pArrA < A + size; pArrA++)
			cout << *pArrA << " ";
	}
	else cout << "m = k";
}