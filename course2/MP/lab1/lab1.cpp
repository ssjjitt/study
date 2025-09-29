#include <stdio.h>
#include "Auxil.h"                           // ��������������� �������  
#include <iostream>
#include <ctime>
#include <locale>
#include "Factorial.h"

#define  CYCLE 2000000                    // ���������� ������    
#define MAX 500

using namespace std;

int main()
{
    double  av1 = 0, av2 = 0;
    clock_t  t1 = 0, t2 = 0;

    setlocale(LC_ALL, "rus");

    auxil::start();                          // ����� ��������� 
    t1 = clock();                            // �������� ������� 
    for (int i = 0; i < CYCLE; i++)
    {
        av1 += (double)auxil::iget(-100, 100); // ����� ��������� ����� 
        av2 += auxil::dget(-100, 100);         // ����� ��������� ����� 
    }
    t2 = clock();                            // �������� ������� 

    cout << endl << "���������� ������:         " << CYCLE;
    cout << endl << "������� �������� (int):    " << av1 / CYCLE;
    cout << endl << "������� �������� (double): " << av2 / CYCLE;
    cout << endl << "����������������� (�.�):   " << (t2 - t1);
    cout << endl << "                  (���):   " << ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
    cout << endl;

    clock_t t3 = 0, t4 = 0;
    t3 = clock();
    fact::factorial(130); // 20 - ������
    t4 = clock();
    cout << endl << "����������������� (�.�):   " << (t4 - t3);
    cout << endl << "                  (���):   " << ((double)(t4 - t3)) / ((double)CLOCKS_PER_SEC);
    cout << endl;
    return 0;
}