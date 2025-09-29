/*
Определить наименьшее натуральное число, отсутствующее в последовательности из n натуральных чи-сел.
*/
#include <iostream>
int main()
{
    setlocale(LC_ALL, "rus");
    using namespace std;
    const int N = 10;
    int A[N], c, * pArrA = A, n, min = 10;
    int B[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    cout << "введите количество отсутствующих чисел: ";
    cin >> c;
    n = N - c;
    cout << endl << "введите " << n << " элементов массива" << endl;
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
    cout << "минимальный элемент: " << min;
}