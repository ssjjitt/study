// Даны два массива С и В, каждый из m элементов. Подсчитать количество таких чисел k, для которых: 
// C[k] > D[k] и C[k] < D[k], С[k] = D[k].
#include <iostream>
int main()
{
	using namespace std;
	const int N = 100;
	int C[N], D[N], m, k = 0, j = 0, l = 0;
	int *pArrC = C, *pArrD = D;
	cout << "m = ";
	cin >> m;
	srand((unsigned)time(NULL));
	cout << "C[i]: ";
	for (pArrC = C; pArrC < C + m; pArrC++)
	{
		*pArrC = rand() % 10;
		cout << *pArrC << " ";
	}
	cout << endl << "D[i]: ";
	for (pArrD = D; pArrD < D + m; pArrD++)
	{
		*pArrD = rand() % 10;
		cout << *pArrD << " ";
	}
	cout << endl;
	for (int i = 0; i < m; i++)
	{
		if (C[i] > D[i]) k++;
		else if (C[i] < D[i]) j++;
		else l++;
	}
	cout << "C[k] > D[k]: " << k << endl;
	cout << "C[k] < D[k]: " << j << endl;
	cout << "C[k] = C[k]: " << l;

}