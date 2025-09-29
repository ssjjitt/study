/* Дан массив A из n элементов и B из m элементов.Содержится ли наибольший элемент массива A в массиве B*/
#include <iostream>
int main()
{
    using namespace std;
    setlocale(LC_CTYPE, "ru");
    srand((unsigned)time(NULL));
    const int n = 100, m = 100;
    int A[n], B[m], sizea, sizeb, maxA = 0, p = 0, * pArrA, * pArrB;

    cout << "размер A: ";
    cin >> sizea;
    cout << "массив A: ";
    for (pArrA = A; pArrA < A + sizea; pArrA++)
    {
        cin >> *pArrA;
    }
   
    cout << "размер B: ";
    cin >> sizeb;
    cout << "массив B: ";
    for (pArrB = B; pArrB < B + sizeb; pArrB++)
    {
        cin >> *pArrB;
    }

    for (pArrA = A; pArrA < A + sizea; pArrA++)
    {
        if (*pArrA > maxA)
            maxA = *pArrA;
    }
    cout << "максимальный элемент в массиве А = " << maxA << endl;
    for (pArrB = B; pArrB < B + sizeb; pArrB++)
    {
        if (maxA == *pArrB)
            p++;
    }
    if (p > 0)
        cout << "содержится";
    else
        cout << "не содержится";
    return 0;
}