// 4. Пройдет ли шар радиуса r через ромбообразное отверстие с диагоналями p и q?
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int r, p, q, d;
	double h;
	cout << "введите радиус шара r = ";
	cin >> r;
	d = 2 * r;
	cout << "диаметр шара d = " << d << endl;
	cout << "введите первую диагональ p = ";
	cin >> p;
	cout << "введите вторую диагональ q = ";
	cin >> q;
	h = (p * q) / (sqrt(p * p + q * q));
	cout << "высота ромба h = " << h << endl;
	if ((h < d) || (h == d)) cout << "нельзя";
	else cout << "можно";
	return 0;
}