// 5. ����� �� ������� �������� a � b � c ��������� � ������� �������� r � s � t? ������ ���������� ������.
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int a, b, c, r, s, t, V1, V2;
	cout << "������� ������ a = ";
	cin >> a;
	cout << "������� ����� b = ";
	cin >> b;
	cout << "������� ������ c = ";
	cin >> c;
	cout << "������� ������ r = ";
	cin >> r;
	cout << "������� ����� s = ";
	cin >> s;
	cout << "������� ������ t = ";
	cin >> t;
	if ((a > r) || (b > s) || (c > t))
		cout << "������";
	else cout << "�����";
	return 0;
}