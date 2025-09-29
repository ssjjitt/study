// 2. ƒана строка символов, состо€ща€ из произвольного текста, слова разделены пробелами. 
// Ќайти пор€дковый номер слова максимальной длины и номер позиции в строке, с которой оно начинаетс€. 

#include <iostream>

int main()
{
	setlocale(LC_ALL, "rus");
	using namespace std;

	char string[256];
	int count, max = 0, index;
	char* ps;
	int position, kolvo;
	cout << "введите строку: ";
	gets_s(string);

	for (count = 0, ps = string; *ps != 0; ps++)
	{
		if (*ps != ' ')
		{
			count++;
		}
		else
		{
			count = 0;
		}
		cout << "count = " << count << endl;
		cout << "index = " << index;
	}
	
}