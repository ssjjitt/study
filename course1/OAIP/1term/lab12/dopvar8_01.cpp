/*
1. Дан массив X, содержащий k элементов, и массив Y, содержащий n элементов.Найти их «пересечение», т.е.массив Z, содержащий их общие элементы.
*/
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	const int N = 100;
	int X[N], Y[N], k, n;
	cout << "k = ";
	cin >> k;
	cout << "n = ";
	cin >> n;

	cout << "массив X: ";
	for (int i = 0; i < k; i++)
	{
		X[i] = rand() % 9;
		cout << X[i] << " ";
	}

	cout << "массив Y: ";
	for (int i = 0; i < n; n++)
	{
		Y[i] = rand() % 9;
		cout << Y[i] << " ";
	}
	for (int i = 0; i < )
	{
		
	}
}