// 2. ��������� ����� m �� ��� �����, �������� ������� ����� 5.
#include <iostream>

int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int m, chast1, chast2, k = 5, c;
	cout << "������� ����� m = ";
	cin >> m;
	if (m % 2 != 0)
	{
		c = m - 5;
		chast1 = c / 2 + 5;
		chast2 = c / 2;
		k = chast1 - chast2;
		cout << "����� = " << m << endl;
		cout << "������ ����� = " << chast1 << endl;
		cout << "������ ����� = " << chast2 << endl;
	}
	else cout << "����� ������, �� �������� :(" << endl;
}
