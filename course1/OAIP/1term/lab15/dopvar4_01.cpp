/*
1. В одномерном массиве, состоящем из n вещественных элементов, вычислить номер минимального элемента массива и сумму элементов массива, расположенных между первым и вторым отрицательными элементами.
*/
#include <malloc.h>
#include <iostream>

int main()
{
    setlocale(LC_ALL, "rus");
    using namespace std;
    int* a = 0;
    int n, min = 100, count = 0, k = 0, kk = 0;
    cout << "количество элементов: ";
    cin >> n;

    a = (int*)malloc(n * sizeof(int));                 

    cout << "a[i] = " << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0) {              
            k = i;
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0) {
            kk = i;                     
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = k + 1; j < kk; j++)               
        {
            if (a[j] < min) min = a[j];
        }
    }

    cout << "min: " << min;

    free(a);
    return 0;

}