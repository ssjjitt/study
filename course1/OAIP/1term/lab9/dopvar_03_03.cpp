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
	// x^3 + 2x Ц 1;
	do
	{
		x = (a + b) / 2;
		if ((pow(x, 3) + 2 * x - 1) * (pow(a, 3) + 2 * a - 1) <= 0)
			b = x;
		else
			a = x;
	} while (abs(a - b) > 2 * e);
	cout << "x = " << x;
	return 0;
}