//2.	���������� � 1� ����� �n ����� ������ �� ������� p.
// 128 ��� �����������
#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_CTYPE, "Russian");
    int A, position, n, razn;
    char tmp[33];
    cout << "������� A ";
    cin >> A;
    _itoa_s(A, tmp, 2);                                             // ������� � ��������
    cout << "������������� ����� � �������� ����: " << tmp << endl;
    cout << "������� ��������� ������� ";
    cin >> position;
    cout << "������� ����� ����� ";
    cin >> n;
    razn = position - n;
    while (position > razn)
    {
        A |= 1 << position;                                     // �������� � ������������� � ����� ����� � ������� �����
        _itoa_s(A, tmp, 2);
        position--;
    }
    cout << tmp << endl;
}