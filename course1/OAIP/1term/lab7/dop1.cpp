/*4. ��� �������� ���� ����������� ��������� ������ ��������� ��������. 
����� ���������� � �������������� ����� � ����� ��������� �� ��������. 
�� ��������� �������, ��� ����� ������� �� 2, �� 7 � �� 11, � ������ ������ 
��������� ������ ��� �����, ����� ���� ������ ����� 30. ��������� �������� � 
��������� ��� ����������� ������ ����������.*/
#include <iostream>
int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	int chislo1, chislo2, chislo3, chislo4; // ����� ������� �� ���� ����������� �����, ����� ������� = 30
	for (int nomer = 1000; nomer <= 9999; nomer++)
	{
		if (((nomer % 2 == 0) && (nomer % 7 == 0)) && (nomer % 11 == 0)) // ��� �������������� ������, ������� ������� �� 2, 7, 11
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
			cout << "������� �����:" << nomer << endl;
		}
	}
	//����� ���� ����� = 30


	return 0;
}



