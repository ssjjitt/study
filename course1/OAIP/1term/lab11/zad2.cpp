//2.	Установить в 1в числе Аn битов вправо от позиции p.
// 128 для наглядности
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "Russian");
    int A, position, n, razn;
    char tmp[33];
    cout << "введите A ";
    cin >> A;
    _itoa_s(A, tmp, 2);                                             // перевод в двоичную
    cout << "представление числа в двоичном коде: " << tmp << endl;
    cout << "введите начальную позицию ";
    cin >> position;
    cout << "введите число битов ";
    cin >> n;
    razn = position - n;
    while (position > razn)
    {
        A |= 1 << position;                                     // сложение с присваиванием и сдвиг влево с помощью цикла
        _itoa_s(A, tmp, 2);
        position--;
    }
    cout << tmp << endl;
}