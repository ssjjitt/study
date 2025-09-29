/*
1. ������ ������������� ������ A[n, n] � ������� �� ������ ������ ����������. �� ������ ������ ��-����� ��������� ������. ������������ ������ �������.
2. ���� ������. ����� � ����������� ��������� ����� ��� ����������� ���������. ����� ����� �����-��� ������ �� ���� ��� ����. ����� ����� �����, �������� � ������.
*/

#include <iostream>
#include <Windows.h>
#include <ctime>
void dop1_1();
void dop2();
void dop1(int& n, int& m, int** arr);

using namespace std;

void dop1_1()
{
    int n = 0;
    cout << "stroki: " << endl;
    cin >> n;
    int m = 0;
    cout << "stolbsy: " << endl;
    cin >> m;
    int** arr = new int* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[m];
    }

    dop1(n, m, arr);
}

void dop1(int& n, int& m, int** arr)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = rand() % 10 + 1;
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    for (int j = 0; j < m; j++)
    {
        arr[0][j] = arr[0][j] - arr[n - 1][j];
    }
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] -= arr[i + 1][j];
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void dop2()
{
    char* str;
    int len = 0;
    int sum = 0;
    cout << "������� ����� ������: ";
    cin.clear();
    cin >> len;
    str = new char[len];
    cout << "������� ������: ";
    cin.clear();
    cin.ignore();
    cin.getline(str, len);

    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            if ((str[i] >= '0') && (str[i] <= '9'))
            {
                char* tmp = &str[i];
                sum += atoi(tmp);
            }
        }
    }

    cout << sum << endl;
}

int main()
{
    int index = 0;
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "�������: ";
    cin >> index;
    do
    {
        switch (index)
        {
        case 1:
            dop1_1();
            break;
        case 2:
            dop2();
            break;
        }
        index++;
    } while (index != 3);

}
