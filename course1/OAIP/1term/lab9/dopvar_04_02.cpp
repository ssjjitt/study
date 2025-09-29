#include <iostream>
int main() {
    setlocale(LC_CTYPE, "ru");
    using namespace std;
    float a, b, e, x;
    cout << "¬ведите а = ";
    cin >> a;
    cout << "¬ведите b = ";
    cin >> b;
    cout << "¬ведите e = ";
    cin >> e;
    do
    {
        x = (a + b) / 2;
        if ((exp(x) - 3 - 1 / x) * (exp(a) - 3 - 1 / a) <= 0)
            b = x;
        else
            a = x;
    } while (abs(a - b) > 2 * e);
    cout << "x = " << x;
    return 0;
}