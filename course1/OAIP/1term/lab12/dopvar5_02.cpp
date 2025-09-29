// ƒаны два массива x и y.Ќайти количество одинаковых элементов в массивах A и B, т.е.количество пар a[i] = b[j] дл€ некоторых i и j.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;

	const int N = 100;
	int X[N], Y[N], size, m = 0;
	int *pArrX = X, *pArrY = Y;
	cout << "количество элементов в массивах: ";
	cin >> size;
	srand((unsigned)time(NULL));

	cout << "X[i]: ";
	for (pArrX = X; pArrX < X + size; pArrX++)
	{
		*pArrX = rand() % 5;
		cout << *pArrX << " ";
	}

	cout << endl << "Y[i]: ";
	for (pArrY = Y; pArrY < Y + size; pArrY++)
	{
		*pArrY = rand() % 5;
		cout << *pArrY << " ";
	}

	for (int i = 0; i < size; i++)
	{
		if (X[i] == Y[i]) m++;
	}
	cout << endl << "количество одинаковых элементов: " << m;
}