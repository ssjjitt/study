    /*� ������������������ �� n ����� ����� ����� � ������� �������� ����� ������ ���������.*/
#include <iostream>
    int main()
    {
        setlocale(LC_CTYPE, "ru");
        using namespace std;
        int n, sum = 0;
        cout << "������������������ ����� ��: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
                sum += i;
        }
        cout << "����� ������: " << sum;
        return 0;
    }