// 1. � ���������� �������, ��������� �� � ������������ ���������, ��������� ������������ ����������-��� 
// ��������� ������� � ����� ������������� ��������� �������, ������������� �� ������������� ���-�����.

#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "ru");
	srand(time(0));
	int size, i = 0;
	float* A, p = 1, sum = 0, min = 0, count = 0;
	cout << "������ �������: ";
	cin >> size;
	A = new float[size];
	for (i = 0; i < size; i++)
	{
		A[i] = rand() % 10 - 4;
		cout << A[i] << " ";
		if (A[i] < 0)
		{
			p *= A[i];
		}
		if (A[i] > min)
		{
			min = A[i];
			count = i;
		}
	}
	cout << endl << "������������ ������� �� " << count << " �����" << endl;
	for (i = 0; i < count; i++)
	{
		if(A[i] > 0)
			sum += A[i];
	}
	cout << endl << "������������ �������������: " << p << "\n";
	cout << "����� ������������� �� �������������: " << sum << "\n";
}
