// -- вычисления длины LCS 
#include "pch.h"
#include <ctime>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <locale>
#include "LCS.h"
using namespace std;

#define _rand(min, max) ( rand() % ((max) - (min) + 1) + (min) )


int main()
{
	setlocale(LC_ALL, "rus");
	clock_t t1 = 0;
	clock_t t2 = 0;
	clock_t t3 = 0;
	clock_t t4 = 0;

	char Z[100] = "";
	char X[] = "ABCDFGI";
	char Y[] = "EATUFI";

	t1 = clock();
	int s = lcs(sizeof(X) - 1, X, sizeof(Y) - 1, Y);
	t2 = clock();

	t3 = clock();
	int l = lcsd(X, Y, Z);
	t4 = clock();

	cout << "\n-- вычисление длины LCS для X и Y";
	cout << "\n-- последовательность X: " << X;
	cout << "\n-- последовательность Y: " << Y;
	cout << "\n-- LCS:                  " << Z;

	cout << "\n-- длина LCS: (рекурсия) " << s;
	cout << "\n-- длина LCS: (дин.пр.)  " << l << "\n";

	cout << "\nВремя вычисления LCS:\n";
	cout << "рекурсия:  " << (t2 - t1);
	cout << "\nдин.про.:  " << (t4 - t3) << "\n";

	//-------------------------------------------------------

	srand(time(NULL));
	char abc[25]; // алфавит
	char s1[300];
	char s2[250];

	// заполняем массив
	for (int i = 97, n = 0; i <= 122; ++i, ++n)
	{
		abc[n] = (char)i;
	}
	for (int i = 0; i < 301; i++)
	{
		s1[i] = abc[_rand(0, 25)];
	}
	for (int i = 0; i < 251; i++)
	{
		s2[i] = abc[_rand(0, 25)];
	}

	int lx = sizeof(s1);
	int ly = sizeof(s2);

	int S1_size[]{ 12,15,20,30,60,150,300 };
	int S2_size[]{ 10,13,17,25,50,125,250 };

	clock_t t11, t22;
	for (int i = 0; i < 3; i++)
	{
		t11 = clock();
		int s = lcs(S1_size[i], s1, S2_size[i], s2);
		t22 = clock();
		cout << S1_size[i] << "/" << S2_size[i]
			<< ":            " << (t22 - t11) << "\n";
	}

	system("pause");
	return 0;
}
