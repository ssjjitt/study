// 2. Разделить число m на две части, разность которых равна 5.
#include <iostream>

int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int m, chast1, chast2, k = 5, c;
	cout << "введите число m = ";
	cin >> m;
	if (m % 2 != 0)
	{
		c = m - 5;
		chast1 = c / 2 + 5;
		chast2 = c / 2;
		k = chast1 - chast2;
		cout << "число = " << m << endl;
		cout << "первая часть = " << chast1 << endl;
		cout << "вторая часть = " << chast2 << endl;
	}
	else cout << "число четное, не работает :(" << endl;
}
