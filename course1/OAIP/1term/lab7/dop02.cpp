#include <iostream>
int main()
{
    using namespace std;
    for (int i = 10; i < 32; i++)
    {
        int chislo = i * i, second = chislo / 10 % 10;
        if (chislo % 10 > second && second > chislo / 100)
        cout << chislo << endl;
    }
}