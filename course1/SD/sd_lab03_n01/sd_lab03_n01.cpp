/*
Написать функции :
1.	Создание и запись данных в файл, название которого вводится с клавиатуры;
2.	Чтение файла(название файла не нужно вводить с клавиатуры);
3.	Удаление содержимого в файле;
4.	Удаление файла.
*/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;

void create(string fileName);
void read(string fileName);
void delInFile(string fileName);
void delFile();

int main() {
	int nswitch;
	setlocale(LC_ALL, ".1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string fileName;		
	cout << "введите имя файла, с которым будут происходить действия: ";
	cin >> fileName;
	do {
		cout << "\nвыберите действие: \n";
		cout << "1 - создание и запись в файл\n";
		cout << "2 - чтение файла\n";
		cout << "3 - удаление содержимого файла\n";
		cout << "4 - удаление файла\n";
		cout << "0 - выход\n";
		cin >> nswitch;
		switch (nswitch) {
		case 1: create(fileName); break;
		case 2: read(fileName); break;
		case 3: delInFile(fileName); break;
		case 4: delFile(); break;
		}
	} while (nswitch != 0);
}

void create(string fileName) {
	string strFile;
	ofstream file(fileName);
	if (!file.is_open()) 
		cout << "Файл не может быть открыт!\n";
	else {
		cout << "введите строку, которую хотите напечать в файл: ";
		cin >> strFile;
		file << strFile;
		getline(cin, strFile);
		file << strFile;
		file.close();
		cout << "\nданные записаны в файл\n";
	}
}

void read(string fileName) {
	string strFile2;
	ifstream file(fileName);
	if (!file.is_open())
		cout << "Файл не может быть открыт!\n";
	else {
		file >> strFile2;
		cout << strFile2;
		getline(file, strFile2);
		file >> strFile2;
		cout << strFile2;
		if (strFile2 == "\0")
			cout << "\nфайл пуст\n";
		else
			cout << "\nданные выведены\n";
		file.close();
	}
}

void delInFile(string fileName) {
	ofstream file(fileName, ios_base::trunc);
	if (!file.is_open())
		cout << "Файл не может быть открыт!\n";
	else {
		cout << "\nсодержимое файла было успешно удалено\n";
		file.close();
	}
}

void delFile() {
	remove("text.txt");
	cout << "\nфайл text.txt был удален\n";
}

