#include <iostream>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
void matrix();
void for2_1(int** matr, int n, int m, int& tmp);
void str();
using namespace std;
/*
1. Ввести вещественные числа в массив А[n, m](n, m > 0) и ко всем числам каждой строки  прибавить единицу.Если первый элемент строки нулевой, ничего не делать.
2. Дана строка.Все русские буквы привести к верхнему регистру, латинские  заменить символом « ? ».Вывести результат на экран.
*/
// Привет World == 13
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_CTYPE, "Russian");
    int choice;
    do
    {
        cout << "вариант работы" << endl;
        cout << "1 - с двумерным массивом" << endl;
        cout << "2 - со строками" << endl;
        cout << "3 - выход" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            matrix();
            break;
        case 2:
            str();
            break;
        case 3:
            break;
        }
    } while (choice != 3);
}
void matrix()
{
    int str, stlb;
    cout << "строки ";
    cin >> str;
    cout << "столбцы ";
    cin >> stlb;
    int** arr = new int* [str];

    for (int i = 0; i < str; i++)
    {
        arr[i] = new int[str];
    }


    cout << "эл матрицы:" << endl;
    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < stlb; j++)
        {
            cin >> arr[i][j];
        }
    }

    int tmp = arr[0][0];

    cout << "массив: " << endl;
    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < stlb; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;

    for2_1(arr, str, stlb, tmp);

    for (int i = 0; i < str; i++)
    {
        for (int j = 0; j < stlb; j++)
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    for (int i = 0; i < str; i++)
    {
        delete[] arr[i];

    }

    delete[] arr;
}
void for2_1(int** matr, int n, int m, int& tmp)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matr[i][0] != 0) {
                    matr[i][j] += 1;
            }
        }
    }
}




void str()
{
    char* str;
    int len = 0;
    cout << "длина строки: ";
    cin.clear();
    cin.ignore();
    cin >> len;
    str = new char[len];
    cout << "строка: ";
    cin.clear();
    cin.ignore();
    cin.getline(str, len);
    
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ')
        {
            if ((str[i] >= 'a') && (str[i] <= 'z') )
            {
                str[i] = '?';
            }
            else if ((str[i] >= 'A') && (str[i] <= 'Z'))
            {
                str[i] = '?';
            }

            else if ((str[i] >= 'а') && (str[i] <= 'я'))
            {
                str[i] = toupper(str[i]);
               
            }  
        }
    }

    cout << str << endl;
   
    delete[] str;

}