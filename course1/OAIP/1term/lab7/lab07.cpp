#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	double b = -0.05, a = 1.72, d, z, i = -5;
	do
	{
		i = i + 2;
		if (i > 3 * b)
		{
			d = a + b * i;
			
		}
		if (i <= 3 * b)
		{
			d = tan(b) - a * i;
			
		}
		cout << "d =" << d << endl;
		z = (d * a / 4) / (3 * a * b - (exp(1 + d) / 100));
		cout << "z = " << z << endl;
	} while (i < 5);
	
	return 0;
}