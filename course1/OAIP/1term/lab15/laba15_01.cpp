//1. Задан массив A из n элементов. Проверить, есть ли в нём отрицательные элементы. Если есть, то найти наибольшее значение k, при котором A[k] < 0.
#include <malloc.h>
#include <iostream>

int main()
{
    setlocale(LC_ALL, "rus");
    using namespace std;
    int* a = 0;
    int i, n, max = 0, count = 0, k = 0;
    cout << "количество элементов: ";
    cin >> n;

    a = (int*)malloc(n * sizeof(int));

    cout << "a[i] = ";
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            cout << "отриц элемент: " << a[i] << " под номером: " << i << endl;
            k = i;
            if (k > max)
            {
                max = k;
            }
        }

    }

    cout << "наибольшее значение k, при котором A[k] < 0: " << max;

    free(a);
    return 0;

}