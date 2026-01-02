//1. Введены с клавиатуры три числа. Найти сумму тех чисел, которые делятся на 5. Если таких чисел нет, то вывести текст «Error». Использовать только тернарные операторы.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	int a, b, c, d = 0;
	using namespace std;
	cout << "введите число а = ";
	cin >> a;
	cout << "введите число b = ";
	cin >> b;
	cout << "введите число c = ";
	cin >> c;
		a % 5 == 0 ? d = d + a : d = d + 0;
		b % 5 == 0 ? d = d + b : d = d + 0;
		c % 5 == 0 ? d = d + c : d = d + 0;
	if (d == 0) cout << "error";
	else cout << "сумма чисел, которые делятся на 5 = " << d;
	return 0;
}