/* ��� ������ A �� n ��������� � B �� m ���������.���������� �� ���������� ������� ������� A � ������� B*/
#include <iostream>
int main()
{
    using namespace std;
    setlocale(LC_CTYPE, "ru");
    srand((unsigned)time(NULL));
    const int n = 100, m = 100;
    int A[n], B[m], sizea, sizeb, maxA = 0, p = 0, * pArrA, * pArrB;

    cout << "������ A: ";
    cin >> sizea;
    cout << "������ A: ";
    for (pArrA = A; pArrA < A + sizea; pArrA++)
    {
        cin >> *pArrA;
    }
   
    cout << "������ B: ";
    cin >> sizeb;
    cout << "������ B: ";
    for (pArrB = B; pArrB < B + sizeb; pArrB++)
    {
        cin >> *pArrB;
    }

    for (pArrA = A; pArrA < A + sizea; pArrA++)
    {
        if (*pArrA > maxA)
            maxA = *pArrA;
    }
    cout << "������������ ������� � ������� � = " << maxA << endl;
    for (pArrB = B; pArrB < B + sizeb; pArrB++)
    {
        if (maxA == *pArrB)
            p++;
    }
    if (p > 0)
        cout << "����������";
    else
        cout << "�� ����������";
    return 0;
}