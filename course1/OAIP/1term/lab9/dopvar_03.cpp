#include <iostream>
int main()
{
	//1 +x^3
	// a = 1
	// b = 6
	using namespace std;
	setlocale(LC_ALL, "rus");
	double a, b, n, s, h, x;
	cout << "������� a = ";
	cin >> a;
	cout << "������� b = ";
	cin >> b;
	cout << "������� n = ";
	cin >> n;
	h = (b - a) / n;
	x = a;
	s = 0;
	cout << "h = " << h << endl;
	do
	{
		s += h * ((pow(x, 3) + 1) + (pow((x + h), 3) + 1)) / 2;
		x = x + h;
	} while (x < (b - h));
	cout << "S = " << s;
	return 0;
}