#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
// объявляем структуру
struct Camp {
	string CampName;
	string CampPlace;
	string CampType;
	int voucher;
};

bool comp1(Camp lhs, Camp rhs)
{
	return lhs.CampName < rhs.CampName;
}

bool comp(Camp lhs, Camp rhs)
{
	return lhs.CampType < rhs.CampType;
}

void showInfo(Camp* lagger, int SIZE) {
	sort(lagger, lagger + SIZE, comp);
	int index1 = 0;
	int index2 = 0;

	for (int i = 0; i < SIZE; i++)
	{
		if (lagger[i].CampType == lagger[i + 1].CampType)
		{
			index1 = i;
			break;
		}
	}

	for (int i = SIZE; i > 0; i--)
	{
		if (lagger[i].CampType == lagger[i - 1].CampType)
		{
			index2 = i;
			break;
		}
	}

	sort(lagger + index1, lagger + index2 + 1, comp1);


	for (int i = 0; i < SIZE; ++i) {
		cout << "Название лагеря: " << lagger[i].CampName << "\t";
		cout << "Место лагеря: " << lagger[i].CampPlace << "\t";
		cout << "Профиль лечения: " << lagger[i].CampType << "\t\t";
		cout << "Количество путевок: " << lagger[i].voucher << "\t" << endl;
		cout << "==============================================================================================================" << endl;
	}

}

void ifileCamp(Camp* lagger, int SIZE)
{

	ifstream fin("lagggerInfo.txt");

	if (!fin.is_open()) {
		cout << "Не удаётся открыть файл для чтения " << endl;
		exit(EXIT_FAILURE);
	}

	vector<string> fileinfo;
	string line, word;
	stringstream x;
	for (int i = 0; i < SIZE; ++i) {
		fin >> lagger[i].voucher;
		getline(fin, line);
		x << line;
		while (x >> word)
		{
			fileinfo.push_back(word);
		}
		for (int k = 0; k < fileinfo.size(); k++)
		{
			if (k == 0) { lagger[i].CampName = fileinfo[k]; }
			if (k == 1) { lagger[i].CampPlace = fileinfo[k]; }
			if (k == 2) { lagger[i].CampType = fileinfo[k]; }
		}
		x.clear();
		line.clear();
		word.clear();
		fileinfo.clear();
	}
	cout << "\nИнформация считана из файла lagggerInfo.txt\n\n";
}


void main()
{

	setlocale(LC_CTYPE, "ru");
	const int SIZE = 5;
	Camp lager[SIZE];
	short choose;
	do {
		cout << "Выберите, что сделать:\n1 — вывести информацию из файла;\n2 — вывести в консоль информацию о путёвках;\n3 — завершение работы.\n";
		cin >> choose;
		switch (choose)
		{
		case 1: ifileCamp(lager, SIZE); break;
		case 2: showInfo(lager, SIZE); break;
		case 3: exit(0); break;
		}
	} while (choose != 3);
}