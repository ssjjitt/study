//1. ��� ��������� ������, ��������� �� N ����� � � ��������, � ����� ����� number. ���������, ��������� �� ��� �����  �� ������� ���������.
//2. �������� ���������, ������� ������ ��� ����� ������ � ������� �� �� ���, ������� ���������� � ����� �b�.
#include <iostream>
using namespace std;
void findnumb(int** matrix, int n);
void matrix();
void stroka();
int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	int choice;
	do
	{
		cout << "�������� ������� ������" << endl;
		cout << "1 - � ��������� ��������" << endl;
		cout << "2 - �� ��������" << endl;
		cout << "3 - �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			matrix();
			break;
		case 2:
			stroka();
			break;
		case 3:
			break;
		}
	} while (choice != 3);
}
void matrix()
{
	int n, z;
	cout << "������� ������ ������� ";
	cin >> n;

	int** array = new int* [n];

	for (int i = 0; i < n; i++)
	{
		array[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "������� �� �������:" << endl;
			cin >> array[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl;


	findnumb(array, n);

	for (int i = 0; i < n; i++)
	{
		delete[] array[i];

	}

	delete[] array;

}

void findnumb(int** matrix, int l)
{
	int number = 0;

	cout << "������� �����(number)" << endl;
	cin >> number;

	for (int i = 0; i < l; i++)
	{
		if (matrix[i][i] == number)
		{
			cout << "�������� ����� ��������� �� ������� ��������� �� ������� " << i << i << endl;
		}
		else
		{
			cout << "�������� ����� �� ��������� �� ������� ��������� �� ������� " << i << i << endl;
		}
	}

}
void stroka()
{
	int amount;
	cout << "������� ���������� �����: " << endl;
	cin >> amount;
	char str[256];
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int k = 0; k < amount; k++)
	{

		cout << "������� ������" << endl;

		cin.getline(str, 256, '\n');


		if (str[0] == 'b')
		{
			cout << str << endl;
		}

		else
		{
			cout << "������ �� ���������� � ������� 'b' " << endl;
		}


	}
}

