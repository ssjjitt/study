#include <iostream>
int main() {
    setlocale(LC_CTYPE, "ru");
    using namespace std;
    float a, b, n, s, h, x;
    cout << "������� � = ";
    cin >> a;
    cout << "������� b = ";
    cin >> b;
    cout << "������� n = ";
    cin >> n;
    h = (b - a) / n;
    x = a;
    s = 0;
    do
    {
        s = s + h * (((exp(x) - 1 / x) + (exp(x + h) - 1 / (x + h))) / 2);
        x = x + h;
    } while (x < (b - h));
    cout << "S = " << s;
    return 0;
}