#include <iostream>
#include <Windows.h>
#include <ctime>
void var2_1();
void var2_2();


using namespace std;

void var2_1()
{
        srand(time(NULL));
        cout << "задание 1: " << endl;
        int n = 10, m = 10, buf;
        int* a = new int[n];
        int* k = new int[n];
        int* b = new int[n];
        for (int i = 0; i < n; i++)
        {
            k[i] = rand() % 10 + 1;
            cout << k[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (k[i] > k[j])
                {
                    swap(k[i], k[j]);
                }
            }

        }

        for (int i = 0; i < n; i++)
        {
            cout << k[i] << " ";
        }
        cout << endl;

        int tek = k[0], sum = 0, iter = 0;
        for (int i = 0; i < n; i++)
        {
            if (k[i] == tek)
            {
                sum++;
            }
            else
            {
                a[iter] = tek;
                b[iter] = sum;
                tek = k[i];
                iter++;
                sum = 0;
            }
        }

        a[iter - 1] = tek;
        b[iter - 1] = sum;

        for (int i = 0; i < iter - 1; i++)
        {
            for (int j = i + 1; j < iter; j++)
            {
                if (a[i] < a[j])
                {
                    swap(a[i], a[j]);
                    swap(b[i], b[j]);
                }
            }

        }

        for (int i = 0; i < iter; i++)
        {
            if (i == iter - 1)
            {
                cout << a[i] << ' ' << (double(b[i]) / double(n)) * 100 << "%" << endl;
            }
            else
            {
                cout << a[i] << ' ' << (double(b[i]) / double(n) + 0.1) * 100 << "%" << endl;
            }
        }
    }

void var2_2()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "задание 2: " << endl;
    int n; cout << "колво строк "; cin >> n;
    int m = 0; cout << "колво столбцов "; cin >> m;
    int index = 0;
    int** doubleArray = new int* [n];
    for (int i = 0; i < n; i++)
    {
        doubleArray[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            doubleArray[i][j] = rand() % 9;
            cout << doubleArray[i][j] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (doubleArray[i][j] == 0)
            {
                index++;
                break;
            }
        }
    }
    cout << endl << "колво строк с 0: " << index;
}

int main()
{
    int index = 0;
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    do
    {
        cout << "номер задания: ";
        cin >> index;
        switch (index)
        {
        case 1:
        {
            var2_1();
            break;
        }
        case 2:
        {
            var2_2();
            break;
        }
        }
        index++;
    } while (index != 3);

}