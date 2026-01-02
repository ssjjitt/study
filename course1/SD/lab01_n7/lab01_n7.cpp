// 10. Написать программу, в которой нужно найти сумму всех элементов вектора и вывести ее на экран.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    srand((unsigned)time(NULL));
    vector<int> vect;
    for (int i = 0; i < 10; i++)
    {
        vect.push_back(rand() % 20 - 5);        // заполняем вектор рандомными числами
        cout << vect.at(i) << " ";
    }

    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += vect.at(i);
        
    }

    cout << endl << "sum = " << sum;
    return 0;
}