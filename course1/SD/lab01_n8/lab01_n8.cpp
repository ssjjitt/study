// 11. Написать программу, в которой удалить n элемент из двусвязного списка и добавить такой же в начало, с выводом на экран.
#include <list>
#include <iterator>
#include <iostream>
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

int main() {
    setlocale(LC_ALL, "RUS");
    list <int> ilist;
    list<int>::iterator pos_begin, i, elem;
    cout << "список: " << endl;
    for (int j = 0; j < 10; j++)
        ilist.push_back(j);
    for (i = ilist.begin(); i != ilist.end(); i++)
        cout << *i << " ";
    int n = 0, t = 1;
    cout << endl << "n = ";
    n = numInput(n);
    pos_begin = ilist.begin();
    n++;
    while(t != n)
    {
        ++pos_begin;
        ++t;
        
    }
    elem = pos_begin;
    cout << "удаленный элемент = " << *elem << endl;
    ilist.push_front(*elem);
    ilist.erase(pos_begin);                               
    cout << "список с удаленным элементом и добавленным в начало: " << endl;
    for (i = ilist.begin(); i != ilist.end(); i++)
        cout << *i << " ";
    return 0;
}