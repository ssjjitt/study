//1. ������� � ���������� ��� �����. ����� ����� ��� �����, ������� ������� �� 5. ���� ����� ����� ���, �� ������� ����� �Error�. ������������ ������ ��������� ���������.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	int a, b, c, d = 0;
	using namespace std;
	cout << "������� ����� � = ";
	cin >> a;
	cout << "������� ����� b = ";
	cin >> b;
	cout << "������� ����� c = ";
	cin >> c;
		a % 5 == 0 ? d = d + a : d = d + 0;
		b % 5 == 0 ? d = d + b : d = d + 0;
		c % 5 == 0 ? d = d + c : d = d + 0;
	if (d == 0) cout << "error";
	else cout << "����� �����, ������� ������� �� 5 = " << d;
	return 0;
}