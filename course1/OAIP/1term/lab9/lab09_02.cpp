#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	double a, b, n, h, x, s1, s2, s;
	int i;
	cout << "введите a = ";
	cin >> a;
	cout << "введите b = ";
	cin >> b;
	cout << "введите n = ";
	cin >> n;
	h = (b - a) / (2 * n);
	x = a + 2 * h;
	s1 = 0;
	s2 = 0;
	i = 1;
	do
	{
		s2 = s2 + pow(cos(x), 3);
		x = x + h;
		s1 = s1 + pow(cos(x), 3);
		x = x + h;
		i = i + 1;
	} while (i < n);
	s = (h / 3) * (   pow(cos(a), 3) + 4 * pow(cos(a + h), 3) + 4 * s1 + 2 * s2 + pow(cos(b), 3)     );
	cout << "s = " << s;
	return 0;
}