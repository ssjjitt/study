// �������� ���������, ����������� ��������� ��������� S1 ������ k � ������� ����� n �� ����-����� ������. 
#include <iostream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	string s;
	int n, k, i;
	cout << "������� ������: ";
	cin >> s;
	cout << "���������� ��������: ";
	cin >> k;
	cout << "�������: ";
	cin >> n;
	cout << "���������: " << s.substr(n, k) << endl;
}
