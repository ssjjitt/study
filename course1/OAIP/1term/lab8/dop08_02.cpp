/* 2. В последовательности из n целых чисел найти и вывести порядковый номер последнего отрицательного элемен-та. */
#include <iostream>

int main() {
    int n, chislo, max;
    using namespace std;
    cout << "n = ";
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cout << "chislo = ";
        cin >> chislo;
        if (chislo < 0)
        {
            max = i;
        }
    }
    cout << max << endl;
    return 0;
}