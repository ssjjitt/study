// 5. Можно ли коробку размером a х b х c упаковать в посылку размером r х s х t? «Углом» укладывать нельзя.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int a, b, c, r, s, t, V1, V2;
	cout << "введите ширину a = ";
	cin >> a;
	cout << "введите длину b = ";
	cin >> b;
	cout << "введите высоту c = ";
	cin >> c;
	cout << "введите ширину r = ";
	cin >> r;
	cout << "введите длину s = ";
	cin >> s;
	cout << "введите высоту t = ";
	cin >> t;
	if ((a > r) || (b > s) || (c > t))
		cout << "нельзя";
	else cout << "можно";
	return 0;
}