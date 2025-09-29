// 5. �������� ���������, � ������� � ����� ������������ ������ ����������� n ��������� � ������� �� �����.
#include <iostream>
#include <forward_list>
using namespace std;

int numInput(int num) {         // � ������ ������ ����� ���� ��������� �� ����� ���������������
    cin >> num;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n�� ����� �� �����, ������� ��������!\n" << endl;
        numInput(num);
    }
    else return num;
}

int main()
{
    setlocale(LC_ALL, "rus");
    forward_list<int> newlist = { 6, 2, 8, 4, 5 };      // � ��� ��� ������������� ����������� ������, �� ������� ������ ��������� ��� ����
    int size = 0, num = 0;

    cout << "������� ����������, ������� ������ �������� = ";
    size = numInput(size);
    cout << "������� �����, ������� ������ �������� = ";
    num = numInput(num);
    cout << "�������������� ������: " << endl;

    for (int n : newlist)       // ������� ���������, ������� ����� ������������ ������ ����� for
    {
        cout << n << "\t";
        size++;
    }

    cout << endl << "�������� ������: " << endl;

    newlist.resize(size, num);     

    for (int n : newlist)
    {
        cout << n << "\t";
    }
}