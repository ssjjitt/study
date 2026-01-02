// Определить, имеется ли среди трёх чисел a, b и c хотя бы одна пара равных между собой чисел.
#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	int a, b, c;
	cout << "введите a = ";
	cin >> a;
	cout << "введите b = ";
	cin >> b;
	cout << "введите c = ";
	cin >> c;
	if ((a == b) || (a == c) || (b == c)) cout << "есть пара равных чисел";
	else cout << "равных чисел нет";
	return 0;
}
