// 1. ���� ������� A � B, ��������� �� n ���������. ��������� ������ S, ������ ������� �������� ����� ����� ��������������� ��������� �������� A � B.
#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	const int N = 100;
	int A[N], B[N], S[N], n, *pArrA, *pArrB, *pArrS;
	cout << "������� n = ";
	cin >> n;
	srand((unsigned)time(NULL));

	cout << endl << "������ A: ";
	for (pArrA = A; pArrA < A + n; pArrA++)
	{
		*pArrA = rand() % 5;
		cout << *pArrA << " ";
	}

	cout << endl << "������ B: ";
	for (pArrB = B; pArrB < B + n; pArrB++)
	{
		*pArrB = rand() % 5;
		cout << *pArrB << " ";
	}

	cout << endl << "������ C: ";
	for (int i = 0; i < n; i++)
	{
		S[i] = A[i] + B[i];
		cout << S[i] << " ";
	}
}