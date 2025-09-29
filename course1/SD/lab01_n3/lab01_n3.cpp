// 6. Написать программу, в которой в начало двусвязного списка добавляется n элементов и вывести на экран.
#include <iostream>
#include <list>

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
    list<int> newlist = { 6, 2, 8, 4, 5 };
    int size = 0, num = 0;

    cout << "введите количество, которое хотите добавить = ";
    size = numInput(size);
    cout << "введите число, которое хотите добавить = ";
    num = numInput(num);

    for (int i = 0; i < size; i++)
    {
        newlist.push_front(num);
    }

    cout << endl << "конечный список: " << endl;
    
    for (int n : newlist)
    {
        
        cout << n << "\t";
    }
}
