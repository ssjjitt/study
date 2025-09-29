// 1. Нарисовать шестиугольник по центру консольного окна, закрашенный введенным символом.

#include <iostream>
#include <iomanip> 
int main()
{
	setlocale(LC_CTYPE, "Russian");
	using namespace std;
	char c, probel; probel = ' ';
	cout << "Введите символ "; cin >> c;
	cout << setw(55) << setfill(probel) << probel;
	cout << setw(10) << setfill(c) << c << endl;
	cout << setw(54) << setfill(probel) << probel;
	cout << setw(12) << setfill(c) << c << endl;
	cout << setw(53) << setfill(probel) << probel;
	cout << setw(14) << setfill(c) << c << endl;
	cout << setw(52) << setfill(probel) << probel;
	cout << setw(16) << setfill(c) << c << endl;

	cout << setw(53) << setfill(probel) << probel;
	cout << setw(14) << setfill(c) << c << endl;
	cout << setw(54) << setfill(probel) << probel;
	cout << setw(12) << setfill(c) << c << endl;
	cout << setw(55) << setfill(probel) << probel;
	cout << setw(10) << setfill(c) << c << endl;
	cout << setw(55) << setfill(probel) << probel;
}
