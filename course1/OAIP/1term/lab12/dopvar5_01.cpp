//��������� ������ �� ��� �����, �������� � ������ ��������, ������� �������� ��������������� �� �����, � �� ������ - �������.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	const int N = 100;
	int A[N], size, sum = 0;
	int* pArrA = A;
	cout << "size: ";
	cin >> size;
	srand((unsigned)time(NULL));
	cout << "A[i]: ";
	for (pArrA = A; pArrA < A + size; pArrA++)
	{
		*pArrA = rand() % 20;
		cout << *pArrA << " ";
		sum += *pArrA;
	}
	cout << endl <<  "����� = " << sum << endl;
	cout << "������� ��������������: " << sum / size << endl;
	cout << endl << "������ �������� ���������������: ";
	for (pArrA = A; pArrA < A + size; pArrA++)
	{
		if (*pArrA > sum / size) cout << *pArrA << " ";
	}
	cout << endl << "������ �������� ���������������: ";
	for (pArrA = A; pArrA < A + size; pArrA++)
	{
		if (*pArrA < sum / size) cout << *pArrA << " ";
	}
}