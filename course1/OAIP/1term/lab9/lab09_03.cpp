#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	float a, b, e, x;
	cout << "введите a = ";
	cin >> a;
	cout << "введите b = ";
	cin >> b;
	cout << "введите e = ";
	cin >> e;
	// cos(x) + x - 7;
	do
	{
		x = (a + b) / 2;
		if ((cos(x) + x - 7) * (cos(a) + a - 7) <= 0)
			b = x;
		else
			a = x;
	} while (abs(a - b) > 2 * e);
	cout << "x = " << x;
	return 0;
}