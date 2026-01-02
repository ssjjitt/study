// 1. В каждой строке заданной матрицы A(n, m) вычислить сумму, количество и среднее арифметическое положительных элементов.
#include <iostream>
int main()
{
	using namespace std;

	const int m = 100, n = 100;
	int A[m][n];
	int column, row, sum = 0, kolvo = 0;
	double arifm;
	cout << "column = ";
	cin >> column;
	cout << "row = ";
	cin >> row;

	srand((unsigned)time(NULL));

	for (int i = 0; i < row; i++)
	{
		cout << "\n";
		for (int j = 0; j < column; j++)
		{
			A[i][j] = rand() % 19 - 9;
			if (A[i][j] >= 0) cout << A[i][j] << " |";
			if (A[i][j] < 0) cout << A[i][j] << "|";
			if (A[i][j] > 0)
			{
				sum += A[i][j];
				kolvo++;
			}
		}
	}
	cout << "\n";
	arifm = (double)sum / (double)kolvo;
	cout << endl << "summa = " << sum;
	cout << endl << "kolvo = " << kolvo;
	cout << endl << "arifm = " << arifm;
}