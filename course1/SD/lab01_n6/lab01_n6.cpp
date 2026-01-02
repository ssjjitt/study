// 9. Написать программу, в которой нужно найти сумму минимального и максимального элементов массива, с выводом на экран.

#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<int, 10> arr = { };
    int max = arr[0], min = arr[0];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 20 - 5;
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
        cout << arr[i] << " ";
    }
    cout << endl << "max = " << max << endl;
    cout << "min = " << min << endl;
    cout << "sum = " << max + min << endl;
}
