/*Ќайти количество различных чисел среди элементов целочисленного массива Z, содержащего n элементов.*/
#include <iostream>
int main()
{
    setlocale(LC_CTYPE, "ru");
    using namespace std;
    srand((unsigned)time(NULL));
    const int N = 100;
    int Z[N], n, m = 0, a;
    cout << "размер массива Z: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        *(Z + i) = rand() % 10;
        cout << Z[i] << " ";
    }
    for (int i = 0; i < n; i++)
    {   
        for (int j = 0; j < n; j++)
        {
            if (Z[i] == Z[j])
                a = 1;
        }
        if (a == 1) m++;
    }
    cout << endl << m << " различных элементов";
    return 0;
}