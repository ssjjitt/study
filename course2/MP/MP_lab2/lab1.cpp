// Main      
#include <stdio.h>
#include <iostream>
#include <iomanip> 
#include "Combi.h"
#include "knapsack.h"
#include <ctime>
#define N (sizeof(AA)/2)
#define M 3
#define NN 18
using namespace std;

int main()
{
    // ������� 1.  ��������� � ����������� ��������� ����������� ��������� ���������. 
    setlocale(LC_ALL, "rus");
    char  AA[][2] = { "A", "B", "C", "D" };
    cout << endl << " - ��������� ��������� ���� ����������� -" << endl << "�������� ���������: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "��������� ���� �����������  ";
    combi::subset s1(sizeof(AA) / 2);         // �������� ����������   
    int  n = s1.getfirst();                // ������ (������) ������������    
    while (n >= 0)                          // ���� ���� ������������ 
    {
        cout << endl << "{ ";
        for (int i = 0; i < n; i++)
            cout << AA[s1.ntx(i)] << ((i < n - 1) ? ", " : " ");
        cout << "}";
        n = s1.getnext();                   // c�������� ������������ 
    };
    cout << endl << "�����: " << s1.count() << endl;



    // ������� 2.  ��������� � ����������� ��������� ���������. 
    cout << endl << " --- ��������� ��������� ---" << endl << "�������� ���������: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "��������� ��������� ";
    combi::xcombination xc(sizeof(AA) / 2, 3);
    cout << "�� " << xc.n << " �� " << xc.m;
    int  n1 = xc.getfirst();
    while (n1 >= 0)
    {
        cout << endl << xc.nc << ": { ";
        for (int i = 0; i < n1; i++)
            cout << AA[xc.ntx(i)] << ((i < n1 - 1) ? ", " : " ");
        cout << "}";
        n1 = xc.getnext();
    };
    cout << endl << "�����: " << xc.count() << endl;



    // ������� 3.  ��������� � ����������� ��������� ������������.
    cout << endl << " --- ��������� ������������ ---" << endl << "�������� ���������: " << "{ ";
    for (int i = 0; i < sizeof(AA) / 2; i++)
        cout << AA[i] << ((i < sizeof(AA) / 2 - 1) ? ", " : " ");
    cout << "}" << endl << "��������� ������������ ";
    combi::permutation p(sizeof(AA) / 2);
    __int64  n2 = p.getfirst();
    while (n2 >= 0)
    {
        cout << endl << setw(4) << p.np << ": { ";
        for (int i = 0; i < p.n; i++)
            cout << AA[p.ntx(i)] << ((i < p.n - 1) ? ", " : " ");
        cout << "}";
        n2 = p.getnext();
    };
    cout << endl << "�����: " << p.count() << endl;



    // ������� 4.  ��������� � ����������� ��������� ����������
    cout << endl << " --- ��������� ���������� ---" << endl << "�������� ���������: " << "{ ";
    for (int i = 0; i < N; i++)
        cout << AA[i] << ((i < N - 1) ? ", " : " ");
    cout << "}" << endl << "��������� ����������  ��  " << N << " �� " << M;
    combi::accomodation s(N, M);
    int  n3 = s.getfirst();
    while (n3 >= 0)
    {
        cout << endl << setw(2) << s.na << ": { ";
        for (int i = 0; i < 3; i++)
            cout << AA[s.ntx(i)] << ((i < n3 - 1) ? ", " : " ");
        cout << "}";
        n3 = s.getnext();
    };
    cout << endl << "�����: " << s.count() << endl;


    // ������� 5. ������
    int V = 300,                // ����������� �������              
        v[] = { 10, 15, 5, 95, 35, 40, 145, 20, 210, 15, 100, 35, 10, 25, 230, 100, 150, 170 },     // ������ �������� ������� ����  
        c[] = { 10, 25, 30, 45, 50, 40, 25, 10, 20, 30, 55, 5, 45, 50, 10, 20, 25, 5 };     // ��������� �������� ������� ���� 
    short m[NN];                // ���������� ��������� ������� ����  {0,1}   
    int maxcc = knapsack_s(
        V,   // [in]  ����������� ������� 
        NN,  // [in]  ���������� ����� ��������� 
        v,   // [in]  ������ �������� ������� ����  
        c,   // [in]  ��������� �������� ������� ����     
        m    // [out] ���������� ��������� ������� ����  
    );
   
    clock_t t1, t2;
    t1 = clock();
    cout << endl << "-------- ������ � ������� --------- " << endl << "- ���������� ��������� : " << NN << endl << "- ����������� �������  : " << V << endl << "- ������� ���������    : ";
    for (int i = 0; i < NN; i++) 
        cout << v[i] << " ";
    cout << endl << "- ��������� ���������  : ";
    for (int i = 0; i < NN; i++)  
        cout << v[i] * c[i] << " ";
    cout << endl << "- ����������� ��������� �������: " << maxcc << endl << "- ��� �������: ";
    int sb = 0;
    for (int i = 0; i < NN; i++)
        sb += m[i] * v[i];
    cout << sb << endl << "- ������� ��������: ";
    for (int i = 0; i < NN; i++)  
        cout << " " << m[i] << "(���: " << v[i] * c[i] << ")";
    t2 = clock();
    cout << endl << endl;
    cout << "�����: " << t2 - t1 << endl;
  system("pause");
    return 0;
}
// 12 - 14
// 13 - 15
// 14 - 16
// 15 - 16
// 16 - 17
// 17 - 19
// 18 - 21
// 19 - 21
// 20 - 23