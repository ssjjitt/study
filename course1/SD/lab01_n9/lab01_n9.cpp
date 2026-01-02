// 12. Написать программу, в которой нужно найти произведение всех элементов деки и вывести его на экран.
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int main()
{
    deque<int> num;
    setlocale(LC_ALL, "rus");
    cout << "очередь: " << endl;
    int p = 1;
    for (int i = 0; i < 10; i++)
    {
        num.push_back(rand() % 20 - 5);
        cout << num[i] << "\t";
        p *= num[i];
    }

    cout << endl << "произведение: " << p;
    return 0;
}