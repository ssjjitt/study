// Бином Ньютона определяется как: Сnm = n! / (m!(n – m)!)
// Рекурсивно описать функцию  C(m, n), где 0 <= m <= n для биноминального коэффициента Сn.
// Сnm = n! / (m!(n – m)!)
#include <iostream>
using namespace std;

int factorial(int i)
{
	if (i == 0) return 1;
	else return (i * factorial(i - 1));
}

float C(int m, int n) {
	return ( (factorial(n)) / ( factorial(m) * factorial(n - m) ) );
}

int main() {
	setlocale(LC_ALL, "rus");
	int m, n;
	cout << "m = ";
	cin >> m;
	cout << "n = ";
	cin >> n;
	if (n >= m && m >= 0) cout << "Результат бином ньютона:" << C(m, n);
	else cout << "данные введены неправильно!";

}