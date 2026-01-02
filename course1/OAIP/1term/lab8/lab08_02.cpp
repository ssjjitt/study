#include <iostream>
int main()
{
	using namespace std;
	float t = 9999, q = 1, y;
 
	for (int i = 1; i <= 5; i++)
	{	
		cout << "y = ";
		cin >> y;
			if (y < t)
			{
				t = y;
			}
			q *= (y + t);
	}
	cout << "t = " << t << endl;
	cout << "q = " << q;
	return 0;
}
