// 1. В массиве из целых чисел найти в процентах частоту появления каждого из k наиболее часто встре-тившихся чисел (k – натуральное число, не превосходящее числа элементов массива). 
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	srand((unsigned)time(NULL));

	const int N = 10;
	int A[N][N], rows, columns;

	cout << "количество колонок: ";
	cin >> rows;
	cout << "количество столбцов: ";
	cin >> columns;

	for (int i = 0; i < rows; i++)
	{
		cout << endl;
		for (int j = 0; j < columns; j++)
		{
			A[i][j] = rand() % 10;
			cout << A[i][j] << " ";
		}
	}

	int k = 1, max = 0;

	for (int i = 0; i < rows; i++)
	{
		cout << endl;
		for (int j = 0; j < columns; j++)
		{
			k = 1;
			int tmp = A[0][0];
			if (A[i][j] == tmp)
			{
				tmp = A[i - 1][j - 1];
				k++;
				if (k > max)
				{
					max = k;
				}
			}
		}
	}
	cout << endl << "k = " << k;


}