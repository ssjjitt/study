// ����������, ������� �� ����� ��� ����� a, b � c ���� �� ���� ���� ������ ����� ����� �����.
#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	int a, b, c;
	cout << "������� a = ";
	cin >> a;
	cout << "������� b = ";
	cin >> b;
	cout << "������� c = ";
	cin >> c;
	if ((a == b) || (a == c) || (b == c)) cout << "���� ���� ������ �����";
	else cout << "������ ����� ���";
	return 0;
}
