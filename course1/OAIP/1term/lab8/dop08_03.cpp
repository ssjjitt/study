/* 4. В последовательности найти число чередований знака, т. е. число переходов с минуса на плюс или с плюса на минус.
Пример: в последовательности целых чисел 0, 2, 0, 10, 2, 1, 0, 0, 3, 2, 3 четыре чередования (как известно, нуль не имеет знака).*/
#include <iostream>
int main()
{
    using namespace std;
    setlocale(LC_ALL, "rus");
    int chislo, chislo1, n, max = 0;
    cout << "введите количество чисел в последовательности: " << endl;
    cin >> n;
    cout << "число: " << endl;
    cin >> chislo;
    for (int i = 1; i < n; i++)
    {
        chislo1 = chislo;
        cin >> chislo;
        if (((chislo > 0) && (chislo1 < 0)) || ((chislo < 0) && (chislo1 > 0)))
            max++;
    }
    cout << "знак меняется " << max << " раз";
    return 0;
}