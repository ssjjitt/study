// 1.	� �������� ������������������ ���� ����� ��� �����, ������� �������� ���������.
#include <iostream>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	cout << "������������������ �� 4 ����" << endl;

	char str1[256], str2[256], str3[256], str4[256];
	
	gets_s(str1);
	gets_s(str2);
	gets_s(str3);
	gets_s(str4);
	cout << "������� ���������" << endl;
	char end;
	cin >> end;

	if (str1[(strlen(str1) - 1)] == end)
	{
		cout << "����� � ����������: " << str1 << endl;
	}
	if (str2[(strlen(str2) - 1)] == end)
	{
		cout << "����� � ����������: " << str2 << endl;
	}
	if (str3[(strlen(str3) - 1)] == end)
	{
		cout << "����� � ����������: " << str3 << endl;
	}
	if (str4[(strlen(str4) - 1)] == end)
	{
		cout << "����� � ����������: " << str4 << endl;
	}
	return 0;
}