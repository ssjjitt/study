/*
1. ��� ������ �������� �������������� ������� K(n) ��������� � ������ L(n), � �������� � � ������ �(n). ���������� ���������� ��� � ������.
*/
#include <iostream>
#include <locale>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	const int n = 99, x = 0, c = 0;
	int i, j = 0, h = 0;
	int K[n], L[n], M[n];
	srand((unsigned)time(NULL));
	for (i = 0; i < n; i++)
	{
		K[i] = rand() % 99;
		if (i % 2 == 0)
		{
			j++;
			L[x] = K[i];
			cout << "L[n]: " << L[x] << endl;
		}
		else
		{
			h++;
			M[c] = K[i];
			cout << "M[n]: " << M[c] << endl;
		}
	}
	cout << "���������� ������: " << j << endl;
	cout << "���������� ��������: " << h << endl;
	return 0;
}