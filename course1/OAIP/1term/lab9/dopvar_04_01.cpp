#include <iostream>
int main() {
    setlocale(LC_CTYPE, "ru");
    using namespace std;
    float a, b, n, s1, s2, s, i, h, x;
    cout << "¬ведите а = ";
    cin >> a;
    cout << "¬ведите b = ";
    cin >> b;
    cout << "¬ведите n = ";
    cin >> n;
    h = (b - a) / (2 * n);
    x = a + 2 * h;
    s1 = 0;
    s2 = 0;
    i = 1;
    do
    {
        s2 = s2 + (exp(x) - 1 / x);
        x = x + h;
        i = i + 1;
    } while (i < n);
    s = h / 3 * ((exp(a) - 1 / a) + 4 * (exp(a + b) - 1 / (a + b) + 4 * s1 + 2 * s2 + (exp(b) - 1 / b)));
    cout << "S = " << s;
    return 0;
}