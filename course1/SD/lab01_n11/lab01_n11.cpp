// 13. Написать программу, в которой нужно удалить все элементы односвязного списка и добавить n новых, с выводом на экран.
#include <iostream>
#include <forward_list>
using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    srand((unsigned)time(NULL));
    forward_list<int> newlist;
    int n;
    for (int i = 0; i < 10; i++)
    {
        newlist.push_front(rand() % 10);
    }
    cout << "первоначальный список: ";
    for (int n : newlist)
    {
        cout << n << " ";
    }
    newlist.clear();
   
    cout << endl << "введите n которое хотите добавить: " << endl;
    cin >> n;

    cout << "новый список: ";
    for (int i = 0; i < n; i++)
    {
        newlist.push_front(rand() % 10);
    }
    for (int n : newlist)
    {
        cout << n << " ";
    }
    return 0;
}