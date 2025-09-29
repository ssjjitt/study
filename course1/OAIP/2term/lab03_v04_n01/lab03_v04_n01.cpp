// 4 вариант 1 задание
// Скопировать из файла FILE1 в файл FILE2 все строки, которые не содержат цифры.Подсчитать количество строк, которые начинаются на букву «А» в файле FILE2.
#include <stdio.h>  
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	using namespace std;
	int count = 0; FILE* file1;
	fopen_s(&file1, "FILE1.txt", "rt");
	fstream file2("FILE2.txt");
	char s[256];
	while (!feof(file1))
	{
		fgets(s, 256, file1);
		for (int i = 0; i < strlen(s); i++)
			if (s[i] > '9' || s[i] < '0')
			{
				file2 << s[i];	
			}
			else
				break;
	}

	fclose(file1);
	file2.close();

	file2.getline(s, 256);
	if (s[0] == 'a' || s[0] == 'A') {
		count++;
	}

	cout << "count = " << count;



	return 0;
}