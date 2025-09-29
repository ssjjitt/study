#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    const int n = 99;
    int a[n] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    int t, l;
    t = a[n - 1];
    cout << "sdvig: ";
    cin >> l;
    for (int k = 0; k < 6; k++) {
        int t;
        t = a[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            a[i + 1] = a[i];
        }
        a[0] = t;
    }
    for (int i = 0; i < n; i++)
    {

        cout << a[i] << " ";

    }

    return 0;

}