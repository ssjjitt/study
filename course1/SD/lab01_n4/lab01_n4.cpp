// 7. Написать программу, в которой нужно найти максимальный элемент вектора и вывести на экран.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    srand((unsigned)time(NULL));
    vector<int> vect;
    for (int i = 0; i < 10; i++)
        vect.push_back(rand() % 20 - 5);        // заполняем вектор рандомными числами
    vector<int>::iterator beg = vect.begin();   // начало вектора
    vector<int>::iterator end = vect.end();     // конец вектора

    while (beg != end)
        cout << *(beg++) << "\t";

    int max = *max_element(vect.begin(), vect.end());   // ищем минимальный элемент от начала до конца
    int min = *min_element(vect.begin(), vect.end());   // ищем максимальный элемент от начала до конца

    cout << endl << "min = " << min << endl;
    cout << "max = " << max << endl;
    
    return 0;
}