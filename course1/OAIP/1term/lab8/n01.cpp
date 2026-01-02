#include <iostream>
int main()
{
	using namespace std;
	
	double y, k = 1, min = 100;

	for (int i = 1; i <= 5; i++)
	{
		cout << "y = ";
		cin >> y;
		if (y < min) min = y;
	}
	cout << "min y = " << min << endl;

	for (int i = 1; i <= 5; i++)
	{
		cout << "y = ";
		cin >> y;
		k *= y + min;
	}
	cout << "k = " << k;
	return 0;
}