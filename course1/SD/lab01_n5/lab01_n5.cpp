// 8. Написать программу, в которой нужно найти минимальный элемент дэки и добавить его в начало, с выводом на экран .
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int main()
{
    deque<int> num;
    setlocale(LC_ALL, "rus");
    cout << "очередь: " << endl;
    for (int i = 0; i < 10; i++)
    {
        num.push_back(rand() % 20 - 5);
        cout << num[i] << "\t";
    }
    cout << endl;

    int max = *max_element(num.begin(), num.end());   // ищем минимальный элемент от начала до конца
    int min = *min_element(num.begin(), num.end());

    cout << "max = " << max << endl;
    cout << "min = " << min;

    num.push_front(min);
    cout << endl << "очередь с минимальным элементом в начале: " << endl;
  
    for (int i = 0; i < num.size(); i++)
    {
        cout << num[i] << "\t";
    }
    return 0;
}