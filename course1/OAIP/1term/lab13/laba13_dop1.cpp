// 1.	В заданной последовательности слов найти все слова, имеющие заданное окончание.
#include <iostream>
#include <string>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	cout << "последовательность из 4 слов" << endl;

	char str1[256], str2[256], str3[256], str4[256];
	
	gets_s(str1);
	gets_s(str2);
	gets_s(str3);
	gets_s(str4);
	cout << "введите окончание" << endl;
	char end;
	cin >> end;

	if (str1[(strlen(str1) - 1)] == end)
	{
		cout << "слово с окончанием: " << str1 << endl;
	}
	if (str2[(strlen(str2) - 1)] == end)
	{
		cout << "слово с окончанием: " << str2 << endl;
	}
	if (str3[(strlen(str3) - 1)] == end)
	{
		cout << "слово с окончанием: " << str3 << endl;
	}
	if (str4[(strlen(str4) - 1)] == end)
	{
		cout << "слово с окончанием: " << str4 << endl;
	}
	return 0;
}