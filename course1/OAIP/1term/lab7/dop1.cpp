/*4. Три приятеля были свидетелями нарушения правил дорожного движения. 
Номер автомобиля – четырехзначное число – никто полностью не запомнил. 
Из показаний следует, что номер делится на 2, на 7 и на 11, в записи номера 
участвуют только две цифры, сумма цифр номера равна 30. Составить алгоритм и 
программу для определения номера автомашины.*/
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int chislo1, chislo2, chislo3, chislo4; // номер состоит из двух двухзначных чисел, сумма которых = 30
	for (int nomer = 1000; nomer <= 9999; nomer++)
	{
		if (((nomer % 2 == 0) && (nomer % 7 == 0)) && (nomer % 11 == 0)) // все четырехзначные номера, которые делятся на 2, 7, 11
		{
			/*cout << nomer << endl;*/
			chislo1 = nomer / 1000;
			chislo2 = nomer / 100 % 10;
			chislo3 = nomer % 100 / 10;
			chislo4 = nomer % 10;
			/*cout << "chislo1 = " << chislo1 << endl;
			cout << "chislo2 = " << chislo2 << endl;
			cout << "chislo3 = " << chislo3 << endl;
			cout << "chislo4 = " << chislo4 << endl;*/
			if ((((chislo1 == chislo2) && (chislo3 == chislo4)) || ((chislo1 == chislo3) && (chislo2 == chislo4)) || ((chislo1 == chislo4) && (chislo2 == chislo3))) && ((chislo1 + chislo2 + chislo3 + chislo4 == 30)))
			cout << "Искомый номер:" << nomer << endl;
		}
	}
	//сумма двух чисел = 30


	return 0;
}



