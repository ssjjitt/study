// 6. �������� ���������, � ������� � ������ ����������� ������ ����������� n ��������� � ������� �� �����.
#include <iostream>
#include <list>

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
    list<int> newlist = { 6, 2, 8, 4, 5 };
    int size = 0, num = 0;

    cout << "������� ����������, ������� ������ �������� = ";
    size = numInput(size);
    cout << "������� �����, ������� ������ �������� = ";
    num = numInput(num);

    for (int i = 0; i < size; i++)
    {
        newlist.push_front(num);
    }

    cout << endl << "�������� ������: " << endl;
    
    for (int n : newlist)
    {
        
        cout << n << "\t";
    }
}
