/*
���������� ���������� ����������� �����, ������������� � ������������������ �� n ����������� ��-���.
*/
#include <iostream>
int main()
{
    setlocale(LC_ALL, "rus");
    using namespace std;
    const int N = 10;
    int A[N], c, * pArrA = A, n, min = 10;
    int B[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << "������� ���������� ������������� �����: ";
    cin >> c;
    n = N - c;
    cout << endl << "������� " << n << " ��������� �������" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> *pArrA;
        if (*pArrA != B[i])
        {
            if (*pArrA < min)
            {
                min = *pArrA - 1;
            }
        }
        
    }
    cout << "����������� �������: " << min;
}