// �������� ���������, ����������� ��������� ��������� S1 ������ k � ������� ����� n �� ����-����� ������. 
#include <iostream>
#include <stdio.h>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	char string[256];
	int position, kolvo;
	cout << "������� ������: ";
	gets_s(string);

	cout << "������� �������, � ������� �������� ��������� ���������: ";
	cin >> position;

	cout << "������� ����� ���������: ";
	cin >> kolvo;

	cout << "���������: ";

	for (int i = position; i < position + kolvo; i++)
	{
		cout << string[i];
	}
}