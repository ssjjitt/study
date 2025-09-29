// 5. Написать программу, в которой в конец односвязного списка добавляется n элементов и вывести на экран.
#include <iostream>
#include <forward_list>
using namespace std;

int numInput(int num) {         // в случае ошибки ввода наша программа не будет останавливаться
    cin >> num;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nВы ввели не число, введите повторно!\n" << endl;
        numInput(num);
    }
    else return num;
}

int main()
{
    setlocale(LC_ALL, "rus");
    forward_list<int> newlist = { 6, 2, 8, 4, 5 };      // у нас дан певоначальный односвязный список, по желанию можете заполнить его сами
    int size = 0, num = 0;

    cout << "введите количество, которое хотите добавить = ";
    size = numInput(size);
    cout << "введите число, которое хотите добавить = ";
    num = numInput(num);
    cout << "первоначальный список: " << endl;

    for (int n : newlist)       // удобный синтаксис, который можно использовать вместо цикла for
    {
        cout << n << "\t";
        size++;
    }

    cout << endl << "конечный список: " << endl;

    newlist.resize(size, num);     

    for (int n : newlist)
    {
        cout << n << "\t";
    }
}