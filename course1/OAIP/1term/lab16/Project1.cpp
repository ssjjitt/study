// 2. Задан массив из k символов. Удалить из него повторные вхождения каждого символа
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    const int n = 100;
    int a[n], size;
    cout << "size = ";
    cin >> size;
    for (int i = 0; i < size; ++i) {
        cin >> a[i];
    }

    cout << "отсортированный массив: " << endl;
    for (int i = 1; i < size; ++i) {
        sort(a, a + size);
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 1; i < size; ++i) {
        if (a[i] == 1) cout << a[i] << " ";
        if(a[i] != a[i - 1])
        {
            cout << a[i] << " ";
        }
    }

}