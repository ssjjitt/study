#include <iostream>
int main()
{
	using namespace std;
	setlocale(LC_ALL, "rus");
	int max = 9999, y, min = -9999, n, min_i = -9999, max_i = 9999, min_y = -9999, max_y = 9999;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cout << "y = ";
		cin >> y;
		if (y < max)
		{
			min = y;
			min_i = i;
		}
		else if (y > min_y)
		{
			max_y = y;
			max_i = i;
		}
	}
	cout << "разность = " << max_i - min_i;
	return 0;
}
