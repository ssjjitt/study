#include <iostream>
using namespace std;
enum planets {// ������� ���� ������������
    mercury = 1,
    venus,
    earth,
    mars,
    jupiter,
    saturn,
    uran
};

int numInput(int num) {   // � ������ ������ ����� ���� ��������� �� ����� ���������������
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
    int number = 0;
    cout << "����� �� ������������ ������� �� ������?\n"
        << " 1 - ��������,\n 2 - ������,\n 3 - �����,\n 4 - ����,\n 5 - ������,\n 6 - ������,\n 7 - ����\n 0 - �����\n";
    do {
        number = numInput(number);
        switch (number)
        {
        case planets::mercury:
            cout << "��������\n";
            break;
        case planets::venus:
            cout << "������\n";
            break;
        case planets::earth:
            cout << "�����\n";
            break;
        case planets::mars:
            cout << "����\n";
            break;
        case planets::jupiter:
            cout << "������\n";
            break;
        case planets::saturn:
            cout << "������\n";
            break;
        case planets::uran:
            cout << "����\n";
            break;
        case 0:
            break;
        default:
            cout << "\n�������� ��������, ������� ��������!\n";
            break;
        }
    } while (number != 0);
}
