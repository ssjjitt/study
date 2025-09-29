#include <iostream>

using namespace std;
void matrix();
void strng();
void for1(int** matr, int k, int z);
int getlen(char* arr);
int getwords(char* arr, int len);
//1. ��� ��������� ������, ��������� �� N ����� � � ��������. ����� ���������� �������������, ������������� � ������� ��������� �������.  
//2. �������� ���������, ������� ������ ��������� ���� ������ � ���������� ����� ���������� ����. ����� ��������� ���������

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int choice;
	do
	{
		cout << "�������� ������� ������" << endl;
		cout << "1 - � ��������� ��������" << endl;
		cout << "2 - �� �������" << endl;
		cout << "3 - �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			matrix();
			break;
		case 2:
			strng();

			break;
		case 3:  break;
		}
	} while (choice != 3);
}
void matrix()
{
	int str, stlb;
	cout << "������� ������ �������(������) ";
	cin >> str;
	cout << "������� ������ �������(��) ";
	cin >> stlb;
	int** arr = new int* [str];

	for (int i = 0; i < str; i++)
	{
		arr[i] = new int[str];
	}


	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < stlb; j++)
		{
			cout << "������� �� �������:" << endl;
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < str; i++)
	{
		for (int j = 0; j < stlb; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}



	for1(arr, str, stlb);

	cout << endl;

	for (int i = 0; i < str; i++)
	{
		delete[] arr[i];

	}

	delete[] arr;
}
void for1(int** matr, int k, int z)
{
	int count1 = 0, count2 = 0, count3 = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < z; j++)
		{
			if (matr[i][j] > 0)
			{
				count1++;
			}
			else if (matr[i][j] < 0)
			{
				count2++;
			}
			else if (matr[i][j] == 0)
			{
				count3++;
			}

		}
	}
	cout << "���������� ���������, ������� ����: " << count1 << " ������� ����: " << count2 << " ������ ����: " << count3;
}
void strng()
{
	char strn[256];

	cout << "������� ������" << endl;
	cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cin.getline(strn, 256, '\n');

	int len = getlen(strn);

	int word = getwords(strn, len);

	cout << "���������� ����: " << word << endl;

}
int getlen(char* arr)
{
	int len = 0;

	for (int i = 0; arr[i] != '\0'; i++)
	{
		++len;
	}

	return len;
}

int getwords(char* arr, int len)
{
	int words = 0;
	for (int i = 0; i <= len; i++)
	{
		if (arr[i] == ' ' || arr[i] == '\0')
		{
			++words;
		}

	}

	return words;
}



