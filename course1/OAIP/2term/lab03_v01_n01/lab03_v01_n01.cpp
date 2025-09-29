// вариант 1 задание 1 
// Скопировать в файл FILE2 только четные строки из FILE1. Подсчитать размер файлов FILE1 и FILE2 (в байтах).
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "ru");
	int k, num = 1, counter = 0;

	string str;
	ifstream file1("f1.txt");
	ofstream file2("f2.txt");
	while (getline(file1, str))
	{

		if (num % 2 == 0)
		{
			file2 << str << '\n';
		}
		num++;
	}
	cout << "Размер файлов FILE1 " << sizeof(file1) << " Размер файлов FILE2  " << sizeof(file2) << endl;
}