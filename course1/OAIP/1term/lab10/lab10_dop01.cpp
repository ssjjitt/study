#include <iostream>
#include <locale>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	const int maxSize = 1900;
	int n, i, max = 0, sum = 0, k, nedel, maxn = 0;
	int a[maxSize];
	srand((unsigned)time(NULL));
	cout << "введите количество дней" << endl;
	cin >> n;
	k = n / 7;
	cout << "количество недель: " << k << endl;
	cout << "количество осадков по неделям" << endl;
	for (int j = 0; j < k; j++)
	{
		for (i = 0; i < 7; i++)
		{
			a[i] = rand() & 1900;
			sum += a[i];
			cout << a[i] << " ";
		}
		cout << "sum = " << sum << endl;
		for (i = 0; i < n; i++)
		{
			if (sum > max)
				max = sum;
			    nedel = i;
		}
	}
	cout << "max = " << max << endl;
}
