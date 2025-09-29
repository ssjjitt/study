#include "stdafx.h"

int min3(int x1, int x2, int x3)
{
	return std::min(std::min(x1, x2), x3);
}

int levenshtein(int lx, const char x[], int ly, const char y[])
{
	int** matr;
	int w, left, top, left_top;
	matr = new int* [lx];
	for (int i = 0; i < lx; i++)
		matr[i] = new  int[ly];
	matr[0][0] = 0;

	for (int i = 1; i < lx; i++)
		matr[i][0] = i;
	for (int j = 1; j < ly; j++)
		matr[0][j] = j;

	for (int i = 1; i < lx; i++)
		for (int j = 1; j < ly; j++)
		{
			w = x[i - 1] == y[j - 1] ? 0 : 1;
			top = matr[i - 1][j];
			left = matr[i][j - 1];
			left_top = matr[i - 1][j - 1];
			matr[i][j] = std::min(left_top + w, std::min(top + 1, left + 1));
		}
	return matr[lx - 1][ly - 1];
}

int levenshtein_r(int lx, const char x[],
	int ly, const char y[])
{
	int rc = 0;
	if (lx == 0) rc = ly;
	else  if (ly == 0) rc = lx;
	else  if (lx == 1 && ly == 1 && x[0] == y[0]) rc = 0;
	else  if (lx == 1 && ly == 1 && x[0] != y[0]) rc = 1;
	else  rc = min3(
		levenshtein_r(lx - 1, x, ly, y) + 1,
		levenshtein_r(lx, x, ly - 1, y) + 1,
		levenshtein_r(lx - 1, x, ly - 1, y) + (x[lx - 1] == y[ly - 1] ? 0 : 1)
	);
	return rc;
};
