// 4. ������� �� ��� ������� r ����� ������������� ��������� � ����������� p � q?
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int r, p, q, d;
	double h;
	cout << "������� ������ ���� r = ";
	cin >> r;
	d = 2 * r;
	cout << "������� ���� d = " << d << endl;
	cout << "������� ������ ��������� p = ";
	cin >> p;
	cout << "������� ������ ��������� q = ";
	cin >> q;
	h = (p * q) / (sqrt(p * p + q * q));
	cout << "������ ����� h = " << h << endl;
	if ((h < d) || (h == d)) cout << "������";
	else cout << "�����";
	return 0;
}