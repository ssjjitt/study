#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
//3. ��������������� �������� �����������, ������ �� ���� ��� ����� � ��������� �������� � ������������� ����� � ������� ��������. 
void main()
{
    setlocale(LC_ALL, "ru");
    const int N = 100;
    char str[N];
    cout << "Enter string: ";
    cin.getline(str, N);
    for (int i = strlen(str) - 1; i >= 0; i--)
        {
            cout << str[i];
            if (str[i] == ' ')
                {
                  i--;
                  while (str[i] != ' ')
                    {
                        i--;
                     }
        }
    }
}